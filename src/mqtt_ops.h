#pragma once

#include "PubSubClient.h"

#include "rf_ops.h"
#include "wifi_ops.h"
#include "config.h"
#include "lcd_ops.h"
#include "spiffs_params.h"

extern PubSubClient mqclient;
extern String base_topic;
extern String esp_chip_id;
extern uint8_t mqtt_on;

extern String mqtt_broker_address;
extern String mqtt_username;
extern String mqtt_password;

void retrieve_mqi_token();
void mqtt_connect();
void print_mqtt_info();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_init();
void mqtt_loop();
void mqtt_send_telemetry();
String generate_topic(const char *msg_type, String topic = "ingest/");

struct mesh_status_t {
    uint8_t mac[6];
    uint16_t node_counter;
    uint16_t trfc_counter;
    int32_t rssi;
};
