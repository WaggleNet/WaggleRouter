#include "wifi_ops.h"
#include "config.h"

ESP8266WebServer server(80);
WiFiClient wclient;

const String ssid_str = String("WaggleRouter_") + String(getRouterID(), HEX);
const char* ssid = ssid_str.c_str();

void mode_ap_begin() {
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, param::get_ap_password().c_str());
	Serial.println("AP Password:");
	Serial.println(param::get_ap_password());
	// Finally, print everything out...
	print_wifi_info();
}

void mode_sta_begin() {
	WiFi.mode(WIFI_STA);
	auto sta_ssid = param::get_wifi_ssid();
	auto sta_pwd = param::get_wifi_password();
	if (sta_pwd.length() == 0)
		WiFi.begin(sta_ssid.c_str());
	else WiFi.begin(sta_ssid.c_str(), sta_pwd.c_str());
	Serial.print(F("Connecting to WiFi AP: "));
	Serial.println(sta_ssid);
	// Serial.print(F("With password: "));
	// Serial.println(sta_pwd);
	// Finally, print everything out...
	print_wifi_info();
}

void route_root() {
	if (!(ESPTemplateProcessor(server).send("/index.html", root_processor)))
		server.send(404, "text/plain", "Page not found.");
}

void route_advanced() {
	if (!(ESPTemplateProcessor(server).send("/advanced.html", root_processor)))
		server.send(404, "text/plain", "Page not found.");
}

String root_processor(const String& key) {
	if (key == String("WIFI_STATUS_TEXT")) {
		if (WiFi.getMode() == WIFI_AP) return "working as AP";
		switch (WiFi.status()) {
			case WL_CONNECTED:
				return "connected";
			case WL_DISCONNECTED:
				return "disconnected";
			case WL_CONNECT_FAILED:
				return "failed to connect";
			case WL_CONNECTION_LOST:
				return "lost connection to";
			default:
				return "unknown";
		}
	} else if (key == String("WIFI_STATUS_CLASS")) {
		if (WiFi.getMode() == WIFI_AP) return "success";
		if (WiFi.status() == WL_CONNECTED) return "success";
		if (WiFi.status() == WL_CONNECT_FAILED) return "danger";
		return "unknown";
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
	} else if (key == String("MQTT_STATUS_TEXT")) {
		if (mqtt_on) return "connected";
		else return "not connected";
	} else if (key == String("MQTT_STATUS_CLASS")) {
		if (mqtt_on) return "success";
		else return "danger";
	} else return "N/A";
}

void route_enable_mqtt() {
	if (server.hasArg("address")) {
		mqtt_broker_address = server.arg("address");
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

void route_addr_broker() {
	if (!server.hasArg("address")) {
		server.send(200, "application/json", "{\"status\": \"error\"}");
		return;
	}
	String addr = server.arg("address");
	param::set_mqtt_address(addr);
	if (server.hasArg("browser")) {
		server.sendHeader("Location", String("/advanced"), true);
		server.send (302, "text/plain", "");
	} else
		server.send(200, "application/json", "{\"status\": \"success\"}");
}

void route_addr_iam() {
	if (!server.hasArg("addr")) {
		server.send(200, "application/json", "{\"status\": \"error\"}");
		return;
	}
	String addr = server.arg("addr");
	param::set_iam_address(addr);
	server.send(200, "application/json", "{\"status\": \"success\"}");
}

void route_mqtt_login_mqi() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	String broker_addr = param::get_mqtt_address();
	if (!server.hasArg("token")) goto bail;
	// PRE-CHECK: If custom server is set, refuse mqi auth
	if (broker_addr.length() <= 2) goto bail;
	// Also clear MQTT username and password
	param::set_mqtt_mqi_token(server.arg("token"));
	param::set_mqtt_username("");
	param::set_mqtt_password("");
	server.send(200, "application/json", "{\"status\": \"success\"}");
	bail:
	server.send(200, "application/json", "{\"status\": \"error\"}");
		return;
}

void route_mqtt_login() {
	if (server.hasArg("username"))
		mqtt_username = server.arg("username");
	if (server.hasArg("password"))
		mqtt_password = server.arg("password");
	param::set_mqtt_username(mqtt_username);
	param::set_mqtt_password(mqtt_password);
	if (server.hasArg("browser")) {
		server.sendHeader("Location", String("/advanced"), true);
		server.send (302, "text/plain", "");
	} else
		server.send(200, "application/json", "{\"status\": \"error\"}");
}

void route_switch_sta() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	if (server.hasArg("ssid") && server.hasArg("password")) {
		Serial.print(F("Setting ssid to "));
		Serial.println(server.arg("ssid"));
		param::set_wifi_ssid(server.arg("ssid"));
		param::set_wifi_password(server.arg("password"));
	}
	if (server.hasArg("browser")) {
		server.sendHeader("Location", String("/"), true);
		server.send(302, "text/plain", "");
	} else
		server.send(200, "application/json", "{\"status\": \"success\"}");
	delay(500);
	ESP.restart();
}

void route_switch_ap() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	param::set_wifi_ssid("");
	if (server.hasArg("browser")) {
		server.sendHeader("Location", String("/"), true);
		server.send(302, "text/plain", "");
	} else
		server.send(200, "application/json", "{\"status\": \"success\"}");
	ESP.restart();
}

void route_scan_wifi() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	int count = WiFi.scanNetworks();
	String result = "{\"networks\": [";
	for (int i = 0; i < count; i++) {
		result += "{\"name\": \"";
		result += WiFi.SSID(i);
		result += "\", \"secure\":";
		if (WiFi.encryptionType(i) == ENC_TYPE_NONE)
			result += "false},";
		else result += "true},";
	}
	result += "]}";
	server.send(200, "application/json", result);
}

void route_build_ver() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	String ver = "{\"major\": ";
	ver += MAJOR_VER;
	ver += ", \"minor\": ";
	ver += MINOR_VER;
	ver += ", \"build\": ";
	ver += BUILD_VER;
	ver += "\"}";
	server.send(200, "application/json", ver);
}

void route_device_info() {
	server.sendHeader("Access-Control-Allow-Origin", "*");
	String info = "{\"type\": \"";
	info += DEVTYPE;
	info += "\", \"device_id\": \"";
	info += String(getRouterID(), HEX);
	info += "\"}";
	Serial.println(info);
	server.send(200, "application/json", info);
}

void setup_routes() {
	server.on("/", route_root);
	server.on("/advanced", route_advanced);
	// TODO: Finish these methods
	server.on("/api/meta/info", route_device_info);
	server.on("/api/meta/build", route_build_ver);
	server.on("/api/addr/iam", route_addr_iam);
	server.on("/api/addr/broker", route_addr_broker);
	server.on("/api/wifi/scan", route_scan_wifi);
	server.on("/api/mqtt/login_mqi", route_mqtt_login_mqi);
	server.on("/api/mqtt/login", route_mqtt_login);
	// TODO: End todo
	server.on("/wifi/sta", route_switch_sta);
	server.on("/wifi/ap", route_switch_ap);
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
	String ssid = param::get_wifi_ssid();
	// TLDR: We kick into AP mode if there's no Wifi SSID remembered
	if (ssid.length()) {
		mode_sta_begin();
		lcd.set_state(UI_GET_APP);
	} else {
		mode_ap_begin();
		lcd.set_state(UI_CONN_WIFI);
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
		// I'm on the welcome screen, do nothing
		lcd.set_state(UI_GET_APP);
	}
	else {
		if (WiFi.status() == WL_CONNECTED) {
			Serial.print(F("[Wifi] Status: Connected as "));
			Serial.println(WiFi.localIP());
			// Connected? MQTT has authority on that screen
		} else {
			Serial.println(F("[Wifi] Status: Disconnected"));
			lcd.set_state(UI_CONN_WIFI);
			WiFi.reconnect();
		}
	}
	Serial.println(F("[Wifi] ********************************"));
}
