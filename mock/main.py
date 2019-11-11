from multiprocessing import Process
import logging
from simulators import MockRouter, MockNode, MockSensor
from sys import argv, exit
import yaml

from api import run_flask


logging.getLogger().setLevel('INFO')


def make_environment(conf):
    router = MockRouter(
        **conf['router']
    )
    # Start by creating the mock router in the config
    for node in conf['nodes']:
        mnode = MockNode(node['node_id'], node['node_addr'])
        for sensor in node.get('sensors', []):
            msensor = MockSensor(sensor['sensor_type'], sensor['sensor_addr'])
            for entry in sensor.get('entries', []):
                msensor.add_entry(**entry)
            mnode.add_sensor(msensor)
        router.add_node(mnode)
    return router


def main(conf_path):
    with open(conf_path) as f:
        conf = yaml.load(f)
        router = make_environment(conf)
    logging.info('YAML Config loaded.')
    logging.info('Starting HTTP API')
    http = Process(target=run_flask)
    http.start()
    try:
        logging.info('Initializing router..')
        with router:
            logging.info('Router now running')
            while True:
                router.update()
    except KeyboardInterrupt:
        pass


if __name__ == "__main__":
    if len(argv) <= 1:
        print('You must specify a valid config YAML.')
        exit(1)
    main(argv[1])
