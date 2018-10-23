#pragma once
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "config.h"

#include <ESP8266WiFi.h>

void display_init();
void display_clear_line(uint8_t, uint8_t);
void display_clear();

void lcd_radio_info(uint8_t channels, uint8_t nodes, uint8_t traffic);
void welcome_screen();
void lcd_wifi_ap(String ip);
void lcd_wifi_sta(String ssid, String ip, wl_status_t status);
void lcd_mqtt(bool mqtt_broker_enable, bool mqtt_on, String mqtt_broker_address);

void lcd_ota_start();
void lcd_ota_complete();
void lcd_ota_progress(unsigned int progress, unsigned int total);
void lcd_ota_error(int error);