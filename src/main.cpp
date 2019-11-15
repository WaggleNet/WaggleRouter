#include "wifi_ops.h"
#include "rf_ops.h"
#include "lcd_ops.h"
#include <EEPROM.h>
#include <FS.h>
#include "config.h"
#include "ota_ops.h"

uint32_t displayTimer = 0;

void setup() {
	Serial.begin(115200);
	Serial.println();
    EEPROM.begin(128);
    SPIFFS.begin();
    lcd.begin();
	// Print the reset prompt
	delay(1000);
	lcd.set_state(UI_RESET);
	lcd.update();
	auto timeout = millis() + 2000;
	while (millis() <= timeout) {
		if (digitalRead(SWITCH_PIN) == LOW) {
			param::reset_params();
			ESP.restart();
		}
	}
	radio_init();
	wifi_init();
    ota_init();
	mqtt_init();
	
}


void loop() {
	// Real time update block
	radio_update();
	wifi_update();
	if(millis() - displayTimer > 5000){
		// Update every 5000 seconds:
		// - Screen display
		// - Debug info
		// - Reconnecting to MQTT if needed
		// - Transmit health telemetry
		displayTimer = millis();
		print_assigned_addresses();
		print_wifi_info();
        print_mqtt_info();
		print_radio_info();
		mqtt_send_telemetry();
	}
	mqtt_loop();
    ota_update();
}
