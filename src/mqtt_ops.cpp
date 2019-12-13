#include "mqtt_ops.h"
#include "config.h"
#include "crypto_ops.h"

PubSubClient mqclient;

uint32_t buf[128] = {};
uint32_t mqtt_timer;
uint8_t mqtt_on = 0;
String mqtt_broker_address;
String mqtt_username;
String mqtt_password;
String mqi_token;

String esp_chip_id(getRouterID(), HEX);
String base_topic = String("ingest/telemetry/")+esp_chip_id;
String node_name = String("DEV-") + esp_chip_id;

mesh_status_t mesh_status_pkt;


/**
 * HELPER: Generates the topic string
 */
String generate_topic(const char *msg_type, String topic) {
    topic += msg_type;
    topic += "/";
    topic += esp_chip_id;
    return topic;
}

/**
 * WRAPPER: setup() for mqtt
 */
void mqtt_init() {
    mqtt_timer = millis();
    mqtt_broker_address = param::get_mqtt_address();
    mqtt_username = param::get_mqtt_username();
    mqtt_password = param::get_mqtt_password();
    mqi_token = param::get_mqtt_mqi_token();
    uint32_t mac = ESP.getChipId();
    // We no longer fill the mac address onto the mesh status packet
    // Prefill the invariant info on the pkt.
    // for (int8_t i = 5; i >= 0; i--) {
    //     mesh_status_pkt.mac[i] = mac & 0xff;6    //     mac >>= 8;
    // }
}

/**
 * WRAPPER: loop() for mqtt, always called
 */
void mqtt_loop() {
    // Just mark the client as offline if mqtt client cannot loop
    if (mqtt_on && !mqclient.loop()) mqtt_on = 0;
    if (mqtt_on && !mqclient.connected()) mqtt_on = 0;
    // If unconnected, every five seconds we reconnect
    if (((long)millis() - mqtt_timer) > 5000) {
        if (!mqtt_on) mqtt_connect();
    }
}

void mqtt_connect() {
    // EARLY EXIT: If wifi isn't connected, just wait
    if (WiFi.status() != WL_CONNECTED) return;
    mqtt_on = 1;
    mqclient = PubSubClient(mqtt_broker_address.c_str(), 1883, mqtt_callback, wclient);
    uint8_t conn_result;
    
    // STEP 1: If we have MQI token pending, try redeem that token
    if (param::get_mqtt_mqi_token().length()) {
        retrieve_mqi_token();
    }
    
    // STEP 2A: If we have a MQTT username, log in with that
    if (mqtt_username.length()) {
        Serial.println(F("[MQTT] Logging in with MQTT custom username..."));
        conn_result = mqclient.connect(
            node_name.c_str(),
            mqtt_username.c_str(),
            mqtt_password.c_str()
        );
    // STEP 2B: Otherwise, attempt logging in insecurely
    } else {
        Serial.println(F("[MQTT] Logging in insecured..."));
        conn_result = mqclient.connect(node_name.c_str());
    }
    
    if (conn_result) {
        Serial.print(F("[MQTT] Connected to "));
        Serial.println(mqtt_broker_address);
        Serial.print(F("Base topic: "));
        String message = "{\"msg\": \"connected\"}";
        mqclient.publish(generate_topic("router_legacy").c_str(), message.c_str());
        mqclient.subscribe(generate_topic("command").c_str());
    } else {
        Serial.print(F("[MQTT] Connection failed: "));
        Serial.println(mqclient.state());
        mqtt_on = 0;
    }
}


void retrieve_mqi_token() {
    HTTPClient http;
    String mqtt_token = param::get_mqtt_mqi_token();
    Serial.print("Requesting MQI access code for token");
	Serial.println(mqtt_token);
	String iam_endpoint = param::get_iam_address() + "/mqi/redeem/device?device_id=";
	iam_endpoint += esp_chip_id;
	iam_endpoint += "&token=";
	iam_endpoint += mqtt_token;
	if (http.begin(iam_endpoint)) {
		int http_code = http.GET();
		if (http_code == HTTP_CODE_OK) {
			String response = http.getString();
			decrypt_mqi_store(response);
			// param::set_mqtt_mqi_token(http.getString());
			http.end();
			Serial.print("[HTTP] Successfully obtained MQI Token ");
			Serial.println(param::get_mqtt_mqi_token());
			server.send(200, "application/json", "{\"status\": \"success\"}");
			mqtt_init();
		}
		http.end();
	}
}


void mqtt_send_telemetry() {
    if (!mqtt_on) return;
    // Size = header 15 + nodes(uint16) 4 + trfc 4 + rssi(int32) 6 = 29
    const size_t bufsize = 29;
    uint8_t buffer[bufsize] = { 0 };
    // Fill the header of the packet (router ID)
    uint32_t routerID = getRouterID();
    uint32_t sensorTypeID = TELEMETRY_TYPE;
    memcpy(buffer, &routerID, sizeof(routerID));
    memcpy(buffer+9, &sensorTypeID, sizeof(sensorTypeID));
    buffer[14] = 3;
    // Fill the status pkt with actual data
    buffer[15] = 0;  // Entry 0: Num of Nodes
    buffer[16] = 2;  //          type uint16
    uint16_t numNodes = mesh.addrListTop;
    memcpy(buffer+17, &numNodes, sizeof(numNodes));
    
    buffer[19] = 1;  // Entry 1: Num of Nodes
    buffer[20] = 2;  //          type uint16
    memcpy(buffer+21, &trfc_counter, sizeof(trfc_counter));
    
    buffer[15] = 23;  // Entry 2: Num of Nodes
    buffer[16] = 24;  //          type uint16
    int32_t rssi = WiFi.RSSI();
    memcpy(buffer+25, &rssi, sizeof(rssi));

    // Publish
    mqclient.publish(generate_topic("telemtry").c_str(), buffer, bufsize);
}

void print_mqtt_info() {
    // If wifi isn't connected, wait for it to finish
    if (WiFi.status() != WL_CONNECTED) return;
    // Then decide which part of the screen to print
    if (mqtt_on) {
        lcd.set_state(UI_CONNECTED);
    } else {
        lcd.set_state(UI_CONN_CLOUD);
    }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    Serial.print(F("[MQTT] Received message on MQTT, topic "));
    String t(topic);
    uint32_t nodeID = *(uint32_t*) payload;
    Serial.print(nodeID);
    Serial.print(", size ");
    Serial.println(length);
    handleCmdPkt(payload, length);
}
