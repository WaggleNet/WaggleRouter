#pragma once

#include "Arduino.h"
#include <SPI.h>
#include <EEPROM.h>
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"

#include "wifi_ops.h"
#include "mqtt_ops.h"
#include "config.h"

extern RF24 radio;
extern RF24Network network;
extern RF24Mesh mesh;

extern uint32_t displayTimer;

extern uint8_t channel_counter;
extern uint16_t trfc_counter;

struct channel_t {
    // Using 16-bit channel number is to comply
    // with the alignment on ESP8266 (16-bit).
    uint16_t ch_id;
    uint16_t size;
};

void radio_init(uint8_t node_id = 0);
void radio_update();
void print_assigned_addresses();
void print_radio_info();

void handleCmdPkt(byte* data, byte len);
