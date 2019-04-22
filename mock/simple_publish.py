import asyncio
import random
from struct import pack

from hbmqtt.client import MQTTClient, ClientException
from hbmqtt.mqtt.constants import QOS_1, QOS_2

CLIENTID = 'DEADBEEF'
NODE_ID = 0xDEADBEEF

SENSOR_TEMP_HUMIDITY = 0x1001
# SENSOR_NODE_BATTERY = 0x2122


def get_header(sensor_id, sensor_type, num_payload):
    return pack('<IxIIxB', NODE_ID, sensor_id, sensor_type, num_payload)


def get_payload(entry_id, size, data, data_format):
    return pack('<BB'+data_format, entry_id, size, data)


def create_packet(sensor_id, sensor_type, *payloads):
    header = get_header(sensor_id, sensor_type, len(payloads))
    return header + b''.join(payloads)


async def publish_temp_humidity(client):
    while True:
        await asyncio.sleep(5)
        temperature = random.random() * 6 - 3 + 50
        humidity = random.random() * 40 + 30
        pkt = create_packet(
            0x60, SENSOR_TEMP_HUMIDITY,
            get_payload(0, 4, temperature, 'f'),
            get_payload(1, 4, humidity, 'f')
        )
        print('Publishing packet: Temperature {}'.format(temperature))
        await client.publish('ingest/telemetry/{}'.format(CLIENTID), pkt)


async def main():
    mqtt = MQTTClient()
    await mqtt.connect('mqtt://localhost')
    await mqtt.subscribe([
        ('ingest/command/{}'.format(CLIENTID), QOS_1)
    ])
    asyncio.ensure_future(publish_temp_humidity(mqtt))
    while True:
        await asyncio.sleep(10)


if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(main())
    except KeyboardInterrupt:
        print('Interrupt!')
    finally:
        print('Done!')
