#include "lcd_ops.h"
#include "lcd_ui.h"

Adafruit_PCD8544 display(LCD_PIN_DC, LCD_PIN_CE, LCD_PIN_RST);

void display_init() {
    display.begin();
    display.setContrast(60);
    display.setTextSize(1);
	display.setTextColor(BLACK, WHITE);
	display.setRotation(2);
    // Print the welcome screen
    display.drawBitmap(0, 0, UI_WELCOME, 84, 48, BLACK);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
}

void display_clear_line(uint8_t line_start, uint8_t line_end) {
    display.setTextSize(1);
    display.fillRect(0, line_start*8, 84, (line_end-line_start+1)*8, WHITE);
    display.setCursor(0, line_start*8);
}


void lcd_radio_info(uint8_t channels, uint8_t nodes, uint8_t traffic) {
    display_clear_line(4, 5);
    display.setTextColor(WHITE, BLACK);
    display.println("CH NODE TRFC  ");
    display.setTextColor(BLACK, WHITE);
    display.print(channels);
    display.setCursor(18, 40);
    display.print(nodes);
    display.setCursor(48, 40);
    display.print(traffic);
}

void welcome_screen() {
    display.clearDisplay();
	display.drawBitmap(0, 0, UI_RESET, 84, 48, BLACK);
	display.display();
}

void display_clear() {
    display.clearDisplay();
    display.display();
}

void lcd_wifi_base() {
    display_clear_line(0, 1);
	display.setTextWrap(false);
	display.setTextColor(WHITE, BLACK);
    display.print("WIFI>");
    display.setTextColor(BLACK, WHITE);
}

void lcd_wifi_ap(String ip) {
    lcd_wifi_base();
    display.println(F("AP Mode"));
    display.println(ip);
    display.display();
}

void lcd_wifi_sta(String ssid, String ip, wl_status_t status) {
    display.println(ssid);
    if (status == WL_CONNECTED) {
        display.println(ip);
    } else {
        display.println(F("!Disconnected!"));
    }
    display.display();
}

void lcd_ota_start() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE, BLACK);
    display.println("OTA Update");
    display.setTextColor(BLACK, WHITE);
    display.display();
}

void lcd_ota_complete() {
    display_clear_line(3, 4);
    display.println("Complete!");
    display.display();
}

void lcd_ota_progress(unsigned int progress, unsigned int total) {
    display.println("Progress:");
    display.print(progress);
    display.print('/');
    display.println(total);
    display.display();
}

void lcd_ota_error(int error) {
    display_clear_line(3, 4);
    display.print("ERROR ");
    display.println(error);
    if (error == 0) display.println("Auth Failed");
    else if (error == 1) display.println("Begin Failed");
    else if (error == 2) display.println("Connect Failed");
    else if (error == 3) display.println("Receive Failed");
    else if (error == 4) display.println("End Failed");
    display.display();
}

void lcd_mqtt(bool mqtt_broker_enable, bool mqtt_on, String mqtt_broker_address) {
    display_clear_line(2, 3);
    display.setTextWrap(false);
    display.setTextColor(WHITE, BLACK);
    display.print("MQTT>");
    display.setTextColor(BLACK, WHITE);
    if (mqtt_broker_enable) {
        display.print("On,");
        display.println(mqtt_on ? "OK" : "Wait");
        display.println(mqtt_broker_address);
    } else display.println("Off");
}