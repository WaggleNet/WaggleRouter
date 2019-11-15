#include "lcd_ops.h"



LCD::LCD():display(LCD_PIN_DC, LCD_PIN_CE, LCD_PIN_RST) {

}

void LCD::begin() {
    display.begin();
    display.setContrast(60);
    display.setTextSize(1);
	display.setTextColor(BLACK, WHITE);
	display.setRotation(2);
    // Print the welcome screen
    set_state(UI_WELCOME); update();
}

void LCD::update() {
    if (last_lcd_page != lcd_page) draw_background();
    if (lcd_page == UI_CONN_WIFI) {
        draw_lower_sta_ssid_ip();
    } else if (lcd_page == UI_CONN_CLOUD) {
        draw_lower_sta_ssid_ip();
    } else if (lcd_page == UI_CONNECTED) {
        draw_lower_sta_ssid_ip();
    } else if (lcd_page == UI_GET_APP) {
        Serial.println("Printing SSID");
        draw_lower_ap_ssid();
    } else if (lcd_page == UI_ERROR) {
        
    }
    last_lcd_page = lcd_page;
}

void LCD::clear() {
    lcd_page = NULL;
    update();
}

void LCD::set_state(uint8_t const * state) {
    lcd_page = state;
}

void LCD::draw_background() {
    display.clearDisplay();
    if (!lcd_page) return;
	display.drawBitmap(0, 0, lcd_page, 84, 48, BLACK);
	display.display();
}

void LCD::draw_lower_banner(String& s) {
    // Clear lower region
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.fillRect(0, 32, 84, 16*8, WHITE);
    display.setCursor(0, 32);
    display.print(s);
    display.display();
}

void LCD::draw_lower_ap_ssid() {
    String ssid = WiFi.softAPSSID();
    draw_lower_banner(ssid);
}

void LCD::draw_lower_sta_ssid_ip() {
    String ssid = WiFi.SSID();
    if (WiFi.status() == WL_CONNECTED) {
        ssid += '\n';
        ssid += WiFi.localIP().toString();
    }
    draw_lower_banner(ssid);
}

void LCD::draw_num_nodes() {
    
}

void LCD::ota_start() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE, BLACK);
    display.println("OTA Update");
    display.setTextColor(BLACK, WHITE);
    display.display();
}

void LCD::ota_complete() {
    clear_line(3, 4);
    display.println("Complete!");
    display.display();
}

void LCD::ota_progress(unsigned int progress, unsigned int total) {
    display.println("Progress:");
    display.print(progress);
    display.print('/');
    display.println(total);
    display.display();
}

void LCD::ota_error(int error) {
    clear_line(3, 4);
    display.print("ERROR ");
    display.println(error);
    if (error == 0) display.println("Auth Failed");
    else if (error == 1) display.println("Begin Failed");
    else if (error == 2) display.println("Connect Failed");
    else if (error == 3) display.println("Receive Failed");
    else if (error == 4) display.println("End Failed");
    display.display();
}

void LCD::clear_line(uint8_t line_start, uint8_t line_end) {
    display.setTextSize(1);
    display.fillRect(0, line_start*8, 84, (line_end-line_start+1)*8, WHITE);
    display.setCursor(0, line_start*8);
}

LCD lcd;
