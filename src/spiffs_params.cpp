#include "spiffs_params.h"
#include "config.h"
#include <Base64.h>

namespace fs {

    String read_str(String filename) {
        if (SPIFFS.exists(filename)) {
            auto f = SPIFFS.open(filename, "r");
            auto s = f.readString();
            f.close();
            return s;
        } else return String("");
    }

    void write_str(String filename, String content) {
        auto f = SPIFFS.open(filename, "w");
        f.print(content);
        f.close();
    }

}

namespace param {

    String get_wifi_ssid() {
        return fs::read_str("/wifi/ssid");
    }

    String get_wifi_password() {
        return fs::read_str("/wifi/password");
    }

    String get_mqtt_address() {
        auto result = fs::read_str("/conf/broker_addr");
        // <= 2 because there might be a linebreak
        if (result.length() <= 2) return default_broker_addr;
        return result;
    }
    
    String get_iam_address() {
        auto result = fs::read_str("/conf/iam_addr");
        if (result.length() <= 2) return default_iam_addr;
        return result;
    }

    String get_mqtt_username() {
        return fs::read_str("/mqtt/username");
    }

    String get_mqtt_mqi_token() {
        return fs::read_str("/mqtt/mqi_token");
    }

    int get_secret_key(uint8_t* data) {
        // Return length of decoded key
        String key_str = fs::read_str("/conf/key");
        char key_str_s[key_str.length() + 1];
        strcpy(key_str_s, key_str.c_str());
        int length = Base64.decodedLength(key_str_s, key_str.length());
        if (length > 0)
            Base64.decode((char*)data, key_str_s, key_str.length());
        return length;
    }

    String get_mqtt_password() {
        return fs::read_str("/mqtt/password");
    }

    String get_ap_password() {
        return fs::read_str("/wifi/ap_psk");
    }

    void set_wifi_ssid(String s) {
        return fs::write_str("/wifi/ssid", s);
    }

    void set_wifi_password(String s) {
        return fs::write_str("/wifi/password", s);
    }

    void set_mqtt_address(String s) {
        return fs::write_str("/conf/broker_addr", s);
    }

    void set_iam_address(String s) {
        return fs::write_str("/conf/iam_addr", s);
    }

    void set_mqtt_username(String s) {
        return fs::write_str("/mqtt/username", s);
    }

    void set_mqtt_password(String s) {
        return fs::write_str("/mqtt/password", s);
    }

    void set_mqtt_mqi_token(String s) {
        return fs::write_str("/mqtt/mqi_token", s);
    }
    
    void set_whitelist(nodeid_t* addresses, size_t length) {
        auto f = SPIFFS.open("/conf/whitelist", "w");
        f.write((uint8_t*)length, sizeof(size_t));
        for (size_t i = 0; i < length; i++) {
            f.write((uint8_t*)addresses, sizeof(nodeid_t));
            addresses ++;
        }
        f.close();
    }

    // Returns number of entries copied
    size_t get_whitelist(nodeid_t* addresses) {
        // File does not exist
        if (!SPIFFS.exists("/conf/whitelist")) return 0;
        auto f = SPIFFS.open("/conf/whitelist", "r");
        // File is empty
        if (!f.size()) {
            f.close();
            return 0;
        }
        // Read the size
        size_t size, res, i;
        f.readBytes((char*)&size, sizeof(size));
        for (i = 0; i < size; i++) {
            res = f.readBytes((char*)addresses, sizeof(nodeid_t));
            // Didn't read anything? Go home
            if (!res) break;
            addresses ++;
        }
        f.close();
        return i;
    }

    void reset_params() {
        set_mqtt_address("");
        set_iam_address("");
        set_mqtt_username("");
        set_mqtt_password("");
        set_wifi_password("");
        set_wifi_ssid("");
        set_mqtt_mqi_token("");
        set_whitelist(NULL, 0);
    }
}
