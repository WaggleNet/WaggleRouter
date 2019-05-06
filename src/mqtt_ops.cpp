#include "mqtt_ops.h"
#include "config.h"

PubSubClient mqclient;

uint32_t buf[128] = {};
uint8_t mqtt_on = 0;
String mqtt_broker_address;
String mqtt_username;
String mqtt_password;
String mqi_token;

String esp_chip_id(getRouterID(), HEX);
String base_topic = String("ingest/telemetry/")+esp_chip_id;
String node_name = String("DEV-") + esp_chip_id;

mesh_status_t mesh_status_pkt;

String generate_topic(char *msg_type) {
    String topic = "ingest/";
    topic += msg_type;
    topic += "/";
    topic += esp_chip_id;
    return topic;
}

boolean process_connection() {
    if (mqtt_username.length()) {
        Serial.println(F("[MQTT] Logging in with MQTT custom username..."));
        return mqclient.connect(
            node_name.c_str(),
            mqtt_username.c_str(),
            mqtt_password.c_str()
        );
    } else if (mqi_token.length()) {
        Serial.println(F("[MQTT] Logging in with MQI Token..."));
        return mqclient.connect(node_name.c_str(), mqi_token.c_str(), "password");
    } else {
        Serial.println(F("[MQTT] Logging in insecured..."));
        return mqclient.connect(node_name.c_str());
    }
}

void mqtt_init() {
    // TODO: Query IAM if MQI token unparsed
    mqtt_broker_address = param::get_mqtt_address();
    mqtt_username = param::get_mqtt_username();
    mqtt_password = param::get_mqtt_password();
    mqi_token = param::get_mqtt_mqi_token();
    uint32_t mac = ESP.getChipId();
    // Prefill the invariant info on the pkt.
    for (int8_t i = 5; i >= 0; i--) {
        mesh_status_pkt.mac[i] = mac & 0xff;
        mac >>= 8;
    }
}

void mqtt_refresh_state() {
    if (!mqtt_on) {
        mqtt_on = 1;
        mqclient = PubSubClient(mqtt_broker_address.c_str(), 1883, mqtt_callback, wclient);
        if (process_connection()) {
            Serial.print(F("[MQTT] Connected to "));
            Serial.println(mqtt_broker_address);
            Serial.print("Base topic: ");
            String message = "{\"msg\": \"connected\"}";
            mqclient.publish(generate_topic("router_legacy").c_str(), message.c_str());
            mqclient.subscribe(generate_topic("command").c_str());
        } else {
            Serial.print(F("[MQTT] Connection failed: "));
            Serial.println(mqclient.state());
            mqtt_on = 0;
        }
    }
    if (mqtt_on && !mqclient.connected()) mqtt_on = 0;
}

void mqtt_send_telemetry() {
    uint8_t buffer[15 + sizeof(mesh_status_t)] = { 0 };
    buffer[14] = 1;
    // Fill the status pkt with actual data
    mesh_status_pkt.node_counter = mesh.addrListTop;
    mesh_status_pkt.trfc_counter = trfc_counter;
    // Save this to the buffer
    memcpy(buffer+15, &mesh_status_pkt, sizeof(mesh_status_t));
    // Publish
    mqclient.publish(generate_topic("telemtry").c_str(), buffer, sizeof(buffer));
}

void print_mqtt_info() {
    lcd_mqtt(1, mqtt_on, mqtt_broker_address);
}

void mqtt_loop() {
    if (mqtt_on)
        if (!mqclient.loop()) mqtt_on = 0;
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print(F("[MQTT] Received message on MQTT, node#"));
    String t(topic);
    uint32_t nodeID = *(uint32_t*) payload;
    Serial.print(nodeID);
    Serial.print(", size ");
    Serial.println(length);
    mesh.write(payload, 121, length, nodeID);
}
