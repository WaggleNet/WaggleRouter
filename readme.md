# WaggleRouter

This is the firmware for the WaggleRouter, a device that acts as the master of a WaggleNetNet Network (mouthful lol), collects telemtry data from each WaggleNode on the network, and transmits the data over to the WaggleNet Cloud or any compatible MQTT broker. Files in this repository describe the **business logic**, i.e. the operating behavior of the router, information to be displayed on the screen, debug data dumped over serial, and the interaction with the user on its WebUI and HTTP API.

This code do **not** concern the following (even though these still get linked in during compilation):

- Mesh addressing and address allocation over WaggleNetNet: Submodule lib/WaggleNetNet
- Mesh data-link layer operations: Submodule lib/RF24Network
- Low-level radio operations: Submodule lib/RF24

Please note that files in those submodules are tracked on other repositories, and you should NEVER commit file changes directly under WaggleNode. For more info, learn about Git Submodules.

## Quick start

To run this, you need compatible hardware:

- WaggleRouter M Version 1.0
- WaggleRouter Version 1.2, 1.3, 1.4

All hardware models run ESP8266 at its core. Double check `platformio.ini` for your programming configuration, and use one of the following environments:

- `development` for development and debug messages over the serial port
- `production` for compiling a firmware version used for actual production.

In both cases, please check the [how-to document](https://wagglenet.atlassian.net/wiki/spaces/SPORT/pages/54493246/How-to) on preflight check items and how to operate the tools. Before you can use the device, you should also configure a few items in the `/data` folder. The contents of each file should be a **one-liner** without a newline character.

- `/wifi/ap_psk` if you're running WaggleRouter as an AP and you need to secure it.
- `/conf/broker_addr` if you need to connect WaggleRouter into a specific broker. Otherwise it defaults to `broker.wagglenet.org`.
- `/conf/iam_addr` if you need to connect WaggleRouter into a specific IAM instance. Otherwise it defaults to `iam.wagglenet.org`.
- `/conf/key` for a pre-burnt encryption key. You'll need this for authentication against the IAM.

Now you're ready for takeoff. Note that it's a two-step process:

1. First you burn the firmware. That is, `pio run -t upload` or "Upload" button.
2. Second you burn the preset filesystem image. That is, `pio run -t uploadfs` or "Upload File System Image".

## Device Behavior

The WaggleRouter starts up in the AP mode. You need to connect to its WiFi, use the IP address displayed on the screen to access the Web UI, and follow the instruction to connect the device to your WiFi. You should also be able to run all the servers on your own computer and connect in that fashion, but the best way is still connecting to the internet.

If you're debugging against WaggleNet's phone app, you should expect a fully automatic process. The only direct interaction with the device is that pressing GPIO2 button causes the device to switch into "configuration mode" (AP mode). We'll also make sure that if this button is invoked in a production setup, the device's custom user data is also wiped. (TODO!)

WaggleRouter's web UI also has an advanced section, allowing users to detach the router from WaggleNet Cloud and connect it to any MQTT broker. Note that this action will blow a fuse (TODO) and in order to reconnect with WaggleNet Cloud, the user has to reset the device completely.

So far, the Nokia 5110 screen on the WaggleRouter displays device's IP address, Wifi network name, MQTT broker address, number of nodes registered and current traffic.

## Major TODO items that can change this guide

- More differentiation will be added to affect user-mode and developer-mode operations (compile-time), especially LCD display content.
- MQI-based MQTT login implementation.
- User-mode fuse for MQTT customization.
- Compatibility with WaggleRouter M, the OLED-based variant.
- Internal initialization script; may help eliminate a second-pass of uploading the FS.

