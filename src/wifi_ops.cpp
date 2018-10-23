#include "wifi_ops.h"

ESP8266WebServer server(80);
WiFiClient wclient;

const String ssid_str = String("HoneyRouter_") + String(ESP.getChipId(), HEX);
const char* ssid = ssid_str.c_str();
#define password "12345678"

void mode_ap_begin(boolean persist = false) {
	if (persist) {
		EEPROM.write(EE_WIFI_MODE, WIFI_MODE_AP);
		EEPROM.commit();
	}
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, password);
	// Finally, print everything out...
	print_wifi_info();
}

void mode_sta_begin(boolean persist = false) {
	if (persist) {
		EEPROM.write(EE_WIFI_MODE, WIFI_MODE_STA);
		EEPROM.commit();
	}
	WiFi.mode(WIFI_STA);
	auto sta_ssid = param::get_wifi_ssid();
	auto sta_pwd = param::get_wifi_password();
	if (sta_pwd.length() == 0)
		WiFi.begin(sta_ssid.c_str());
	else WiFi.begin(sta_ssid.c_str(), sta_pwd.c_str());
	Serial.print(F("Connecting to WiFi AP: "));
	Serial.println(sta_ssid);
	Serial.print(F("With password: "));
	Serial.println(sta_pwd);
	// Finally, print everything out...
	print_wifi_info();
}

void route_root() {
	if (!(ESPTemplateProcessor(server).send("/index.html", root_processor)))
		server.send(404, "text/plain", "Page not found.");
}

String root_processor(const String& key) {
	if (key == String("CONN_MODE")) {
		if (WiFi.getMode() == WIFI_AP) return "WiFi Mode: AP";
		else return String("WiFi Mode: Station");
	} else if (key == String("CONN_STATUS")) {
		if (WiFi.getMode() == WIFI_AP) return "Operating";
		else switch (WiFi.status()) {
			case WL_CONNECTED:
				return "Connected";
			case WL_DISCONNECTED:
				return "Disconnected";
			case WL_CONNECT_FAILED:
				return "Failed to Connect";
			case WL_CONNECTION_LOST:
				return "Connection Lost";
			default:
				return "Unknown";
		}
	} else if (key == String("CONN_SSID")) {
		if (WiFi.getMode() == WIFI_AP) return ssid_str;
		else return WiFi.SSID();
	} else if (key == String("CONN_IP")) {
		if (WiFi.getMode() == WIFI_AP) return WiFi.softAPIP().toString();
		else return WiFi.localIP().toString();
	} else if (key == String("RF_CHANNELS")) {
		return String(channel_counter);
	} else if (key == String("RF_ADDRESSES")) {
		return String(mesh.addrListTop);
	} else if (key == String("RF_ADDRLIST")) {
		String message = "<ul class=\"list-group\">";
		for (int i = 0; i < mesh.addrListTop; i++) {
			message += "<li class=\"list-group-item\"><strong>ID: ";
			message += String(mesh.addrList[i].nodeID) + "</strong>";
			message += " Address: ";
			message += String(mesh.addrList[i].address);
			message += "</li>";
		}
		message += "</ul>";
		return message;
	} else if (key == String("RF_TRAFFIC")) {
		return String(trfc_counter);
	} else if (key == String("MQTT_MODE")) {
		if (mqtt_broker_enable) return "MQTT: On";
		else return "MQTT: Off";
	} else if (key == String("MQTT_STATUS")) {
		if (mqtt_on) return "Connected";
		else return "Trying to connect";
	} else if (key == String("MQTT_ADDR")) {
		if (mqtt_on) return mqtt_broker_address;
		else return "N/A";
	} else return "N/A";
}

void route_enable_mqtt() {
	if (server.hasArg("address")) {
		mqtt_broker_address = server.arg("address");
		mqtt_broker_enable = 1;
		if (server.hasArg("username")) {
			mqtt_username = server.arg("username");
			mqtt_password = server.arg("password");
		} else {
			mqtt_username = "";
			mqtt_password = "";
		}
		param::set_mqtt_address(mqtt_broker_address);
		param::set_mqtt_username(mqtt_username);
		param::set_mqtt_password(mqtt_password);
		print_mqtt_info();
		server.send(200, "application/json", "{\"status\": \"success\"}");
	} else {
		server.send(200, "application/json", "{\"status\": \"error\"}");
	}
}

void route_switch_sta() {
	if (server.hasArg("ssid") && server.hasArg("password")) {
		param::set_wifi_ssid(server.arg("ssid"));
		param::set_wifi_password(server.arg("password"));
	}
	server.send(200, "application/json", "{\"status\": \"success\"}");
	// mqtt_broker_enable = 0;
	mode_sta_begin(true);
}

void route_switch_ap() {
	server.send(200, "application/json", "{\"status\": \"success\"}");
	// mqtt_broker_enable = 0;
	mode_ap_begin(true);
}

void route_disable_mqtt() {
	mqtt_broker_enable = 0;
	param::set_mqtt_address("");
	Serial.println(F("[MQTT] Broker disabled via REST."));
	server.send(200, "application/json", "{\"status\": \"success\"}");
}

void setup_routes() {
	server.on("/", route_root);
	server.on("/wifi/sta", route_switch_sta);
	server.on("/wifi/ap", route_switch_ap);
	server.on("/mqtt/enable", route_enable_mqtt);
	server.on("/mqtt/disable", route_disable_mqtt);
	server.onNotFound([]() {
		if (!handleFileRead(server.uri()))
		server.send(404, "text/plain", "404: Not Found");
  });
}

bool handleFileRead(String path) {
	if (path.endsWith("/")) path += "index.html";
	String contentType = getContentType(path);
	if (SPIFFS.exists(path)) {
		auto f = SPIFFS.open(path, "r");
		server.streamFile(f, contentType);
		f.close();
		return true;
	} else return false;
}

void wifi_init() {
	Serial.println(F("[Wifi] Configuring access point..."));
	welcome_screen();
	auto timeout = millis() + 2000;
	while (millis() <= timeout) {
		if (digitalRead(SWITCH_PIN) == LOW) {
			EEPROM.write(EE_WIFI_MODE, WIFI_MODE_AP);
			EEPROM.commit();
			delay(200);
			break;
		}
	}
	display_clear();
	uint8_t stored_mode = EEPROM.read(EE_WIFI_MODE);
	switch (stored_mode) {
		case WIFI_MODE_AP:
			mode_ap_begin();
			break;
		case WIFI_MODE_STA:
			mode_sta_begin();
			break;
		default:
			EEPROM.write(EE_WIFI_MODE, WIFI_MODE_AP);
			EEPROM.commit();
			mode_ap_begin();
	}
	setup_routes();
	server.begin();
}

void wifi_update() {
	server.handleClient();
}

void print_wifi_info() {
	Serial.println(F("[Wifi] ********WiFi Information********"));
	Serial.println(WiFi.macAddress());
	Serial.println(WiFi.softAPmacAddress());
	if (WiFi.getMode() == WIFI_AP) {
		lcd_wifi_ap(WiFi.softAPIP().toString());
		Serial.print(F("[Wifi] SoftAP, IP: "));
		Serial.println(WiFi.softAPIP());
	}
	else {
		lcd_wifi_sta(WiFi.SSID(), WiFi.localIP().toString(), WiFi.status());
		if (WiFi.status() == WL_CONNECTED) {
			Serial.print(F("[Wifi] Status: Connected as "));
			Serial.println(WiFi.localIP());
		} else {
			Serial.println(F("[Wifi] Status: Disconnected"));
			WiFi.reconnect();
		}
	}
	Serial.println(F("[Wifi] ********************************"));
}
