#include "lcd_ops.h"
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

void ota_init() {
    ArduinoOTA.onStart([]() {
        lcd_ota_start();
    });
    ArduinoOTA.onEnd([]() {
        lcd_ota_complete();
        delay(1000);
        ESP.reset();
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        display_clear_line(1, 2);
        lcd_ota_progress(progress, total);
    });
    ArduinoOTA.onError([](ota_error_t error) {
        lcd_ota_error(error);
        delay(2000);
        ESP.reset();
    });
    ArduinoOTA.begin();
}

void ota_update() {
    ArduinoOTA.handle();
}
