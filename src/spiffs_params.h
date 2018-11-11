#include <FS.h>
#include "Arduino.h"

namespace fs {
    String read_str(String);
    void write_str(String, String);
}

namespace param {
    String get_wifi_ssid();
    String get_wifi_password();
    String get_mqtt_address();
    String get_iam_address();
    String get_mqtt_username();
    String get_mqtt_password();
    String get_mqtt_mqi_token();
    // Read-only
    String get_secret_key();
    String get_ap_password();

    void set_wifi_ssid(String);
    void set_wifi_password(String);
    void set_mqtt_address(String);
    void set_iam_address(String);
    void set_mqtt_username(String);
    void set_mqtt_password(String);
    void set_mqtt_mqi_token(String);
    
    void reset_params();
}
