from flask import jsonify, request, Flask
import paho.mqtt.client as mqtt
import logging

app = Flask(__name__)

client = mqtt.Client(client_id='api')
DUT_TOPIC = 'dut/http_api'


def on_connected(ch, userdata, flags, rc):
    ch.publish('api/status', 'api connected')
    logging.info('Mgmt interface connected from api, rc={}'.format(rc))


def ok():
    return jsonify(status='success')


def bad():
    return jsonify(status='error')


@app.route('/api/meta/info')
def api_device_info():
    return jsonify(
        type='wn-router.2.1',
        device_id='DEADBF'
    )


@app.route('/api/meta/build')
def api_device_build():
    return jsonify(
        major=1,
        minor=2,
        build=4
    )


@app.route('/api/addr/iam')
def api_set_iam_addr():
    return ok()


@app.route('/api/addr/broker')
def api_set_broker_addr():
    return ok()


@app.route('/api/wifi/scan')
def api_list_wifi_networks():
    # FIXME: List mock Wifi names
    return ok()


@app.route('/wifi/sta')
def api_switch_wifi_sta():

    client.publish(DUT_TOPIC, 'inet up')
    return ok()


@app.route('/wifi/ap')
def api_switch_wifi_ap():
    client.publish(DUT_TOPIC, 'inet down')
    return ok()


@app.route('/api/mqtt/login_mqi')
def api_set_mqi_token():
    # TODO: Send mqi token to broker
    if 'token' not in request.args:
        return bad()
    token = request.args['token']
    client.publish(DUT_TOPIC, 'mqi '+token)
    return ok()


@app.route('/api/mqtt/login')
def api_set_mqtt_credential():
    # TODO: Support this
    return ok()


def run_flask():
    client.on_connect = on_connected
    client.connect_async('localhost', 1884, 60)
    client.loop_start()
    app.run(port=2900)
