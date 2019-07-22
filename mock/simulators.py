from struct import pack
import paho.mqtt.client as mqtt
import time
import logging

logging.getLogger().setLevel('INFO')


class MockRouter:
    def __init__(self,
                 router_id,
                 secret_key,
                 iam_addr,
                 mgmt_broker,
                 test_broker,
                 report_interval=5):
        self.router_id = router_id
        self.router_id_num = int(router_id, 16)
        if isinstance(secret_key, str):
            self.secret_key = bytes.fromhex(secret_key)
        else:
            self.secret_key = secret_key
        self.iam_addr = iam_addr
        self.mgmt_broker = mgmt_broker
        self.test_broker = test_broker
        self.nodes = {}  # addr: MockNode
        self.mqi_token = ''
        self.mqi = ''
        self.internet_access = False
        self.test_broker_connected = False
        self.last_telemetry = time.time()
        self.report_interval = report_interval

        self.mgmt_conn = mqtt.Client(client_id='dut')
        self.test_conn = mqtt.Client(client_id='DEV-%s' % router_id)

    def add_node(self, node: 'MockNode'):
        self.nodes[node.node_id] = node

    def request_mqi_token(self):
        from Crypto.Cipher import AES
        from base64 import b64decode
        import requests
        key = AES.new(self.secret_key, mode=AES.MODE_ECB)
        # Call /mqi/redeem/device?device_id=...&token=...
        resp = requests.get(
            '{}/mqi/redeem/device?device_id={}&token={}'
            .format(self.iam_addr, self.router_id_num, self.mqi_token))
        resp.raise_for_status()
        logging.info('MQI token transported')
        # Use secret key to do AES decryption
        encrypted_mqi = b64decode(resp.content)
        mqi = key.decrypt(encrypted_mqi)
        # Then store the result in self.mqi
        if isinstance(mqi, bytes):
            mqi = mqi.decode()
        self.mqi = mqi
        logging.info('MQI token successfully installed')

    def on_mgmt_broker_connect(self, ch, userdata, flags, rc):
        logging.info('Mgmt interface connected, rc={}'.format(rc))
        ch.subscribe('dut/http_api')
        ch.message_callback_add('dut/http_api', self.on_mgmt_broker_receive)

    def on_mgmt_broker_receive(self, ch, userdata, msg):
        payload = msg.payload
        if isinstance(payload, bytes):
            payload = payload.decode()
        logging.info('Received API RC message: %s', payload)
        payload = payload.split(' ')
        if payload[0] == 'inet':
            logging.info('Internet is now ' + payload[1])
            self.internet_access = payload[1] == 'up'
        elif payload[0] == 'mqi':
            logging.info('Setting MQI token ' + payload[1])
            self.mqi_token = payload[1]

    def on_test_broker_connect(self, ch, userdata, flags, rc):
        logging.info('Test Interface connected, rc={}'.format(rc))
        ch.subscribe('ingest/command/{}'.format(self.router_id))
        self.test_broker_connected = True
        ch.publish(
            'ingest/router_legacy/{}'.format(self.router_id),
            '{"msg": "connected"}')

    def connect_broker(self):
        parts = self.test_broker.split(':')
        if len(parts) == 1:
            host = parts[0]
            port = 1883
        else:
            host, port = parts
            port = int(port)
        self.test_conn.on_connect = self.on_test_broker_connect
        self.test_conn.username_pw_set(self.mqi)
        self.test_conn.connect(host, port)
        logging.info('Connecting to broker on %s:%s', host, port)
        self.test_conn.loop_start()
        self.test_broker_connected = True

    def disconnect_broker(self):
        self.test_conn.loop_stop()
        self.test_conn.disconnect()
        self.test_broker_connected = False

    def report_telemetry_mgmt(self):
        pass

    def report_telemetry_test(self):
        logging.info('Reporting telemetry..')
        # Collect packets from nodes
        for node in self.nodes.values():
            for message in node.update():
                self.test_conn.publish(
                    'ingest/telemetry/{}'.format(self.router_id))

    def update(self):
        if self.internet_access and not self.test_broker_connected:
            if not self.mqi and self.mqi_token:
                self.request_mqi_token()
            if self.mqi:
                self.connect_broker()
        if self.test_broker_connected and not self.internet_access:
            self.disconnect_broker()
        if time.time() - self.last_telemetry > self.report_interval:
            self.report_telemetry_mgmt()
            if self.test_broker_connected:
                self.report_telemetry_test()
            self.last_telemetry = time.time()

    def __enter__(self):
        self.mgmt_conn.on_connect = self.on_mgmt_broker_connect
        self.mgmt_conn.connect_async('localhost', 1884, 60)
        self.mgmt_conn.loop_start()
        logging.info('Simulator context entered')

    def __exit__(self, type, value, traceback):
        self.disconnect_broker()
        self.mgmt_conn.loop_stop()
        self.mgmt_conn.disconnect()
        logging.info('Simulator context exited')


class MockNode:
    def __init__(self,
                 node_id,
                 node_addr,
                 ):
        if isinstance(node_id, str):
            self.node_id = int(node_id, 16)
        else:
            self.node_id = node_id
        self.node_addr = node_addr
        self.report_interval = 10
        self.sensors = []
        self._inbox = []

    def add_sensor(self, sensor):
        self.sensors.append(sensor)

    def send_msg(self, msg):
        self._inbox.append(msg)

    def update(self):
        # Update telemetry packets
        outbox = []
        node_header = pack('<Ix', self.node_id)
        for i in self.sensors:
            pkt = i.update()
            if not i:
                continue
            outbox.append(node_header + pkt)
        return outbox


class MockSensor:
    def __init__(self,
                 sensor_type,
                 sensor_addr
                 ):
        self.sensor_type = sensor_type
        self.sensor_addr = sensor_addr
        self.entries = []

    def add_entry(self, format, size, value=None):
        self.entries.append((format, size, value))
        return len(self.entries) - 1

    def update(self):
        """
        Update sensor data, and return a serialized binary
        """
        pkt = pack(
            'IIxB',
            self.sensor_addr,
            self.sensor_type,
            len(self.entries))
        counter = 0
        for fmt, size, val in self.entries:
            pkt += pack('<BB'+fmt, counter, size, val)
        return pkt
