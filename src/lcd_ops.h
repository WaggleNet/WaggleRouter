#pragma once
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "lcd_ui.h"

class LCD {
    public:
    LCD();
    void begin();
    void clear();
    void update();

    void set_state(uint8_t const * state);

    // Incoming display states
    int num_nodes = 1;
    int traffic_amount = 1;
    String error;

    // OTA only
    void ota_start();
    void ota_complete();
    void ota_progress(unsigned int progress, unsigned int total);
    void ota_error(int error);
    void clear_line(uint8_t line_start, uint8_t line_end);

    private:
    Adafruit_PCD8544 display;
    // Component drawing
    void draw_background();
    void draw_lower_banner(String& s);
    void draw_lower_ap_ssid();
    void draw_lower_sta_ssid_ip();
    void draw_num_nodes();
    // Internal state
    uint8_t const * lcd_page = NULL;
    uint8_t const * last_lcd_page = NULL;
    uint32_t lcd_timer = 0;
};

extern LCD lcd;
