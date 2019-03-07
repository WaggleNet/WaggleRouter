#include "rf_ops.h"

RF24 radio(RF_PIN_CE, RF_PIN_CS);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

#define DEBUG 1

uint8_t channel_counter = 0;
uint16_t trfc_counter = 0;

void radio_init(uint8_t node_id) {
    radio.setPALevel(RF24_PA_MAX);
    mesh.setNodeID(node_id);
    Serial.println(F("[Radio] Configuring mesh network..."));
	mesh.begin(RF_CHANNEL, RF24_2MBPS);
    Serial.println(F("[Radio] Mesh network configuration complete"));
}



/** Handle Telemetry Packet (CH# 120)
 * See https://wagglenet.atlassian.net/wiki/spaces/SPORT/pages/13238331/Node-to-Router+Data+Format
 */
void handleTelemetryPkt(byte* data, byte len) {
    auto topic = generate_topic("telemetry");
    mqclient.publish(topic.c_str(), data, len);
}

/** Handle heartbeat packet (CH# 66)
 * 
 */
void handleHeartbeatPkt(byte* data, byte len) {
    auto topic = generate_topic("heartbeat");
    mqclient.publish(topic.c_str(), data, len);
}

/** Handle system message (CH# 67)
 * 
 */
void handleSysMsgPkt(byte* data, byte len) {
    auto topic = generate_topic("system");
    mqclient.publish(topic.c_str(), data, len); 
}

/** Handle sending commands (CH# 121)
 * 
 */
void handleCmdPkt(byte* data, byte len) {
    return;
}

void radio_update() {
    mesh.update();
	mesh.DHCP();
    // Check for incoming data from the sensors
    if(network.available()){
		RF24NetworkHeader header;
        size_t data_size = network.peek(header);
        #ifdef DEBUG
    		Serial.print(F("[Radio] Rx Pkt from "));
            Serial.print(header.from_node);
            Serial.print(F(", node "));
            Serial.print(mesh.getNodeID(header.from_node));
            Serial.print(F(", size "));
            Serial.println(data_size);
        #endif
        // Assemble memory for MQTT forwarding
        byte *payload;
        payload = new byte[data_size];
        network.read(header, payload, data_size);
        #ifdef DEBUG
            Serial.print(F("Pkt dump: "));
            for (byte i = 0; i < data_size; i++) {
                Serial.print(payload[i], HEX);
                Serial.print(' ');
            }
            Serial.println();
        #endif
        if (header.type == 120) {
            handleTelemetryPkt(payload, data_size);
        } else if (header.type == 66) {
            handleHeartbeatPkt(payload, data_size);
        } else if (header.type == 67) {
            handleSysMsgPkt(payload, data_size);
        }
        trfc_counter ++;
        delete[] payload;
	}
}

void print_radio_info() {
    lcd_radio_info(channel_counter, mesh.addrListTop, trfc_counter);
    trfc_counter = 0;
}

void print_assigned_addresses() {
    Serial.println(" ");
    Serial.println(F("[Radio] ********Assigned Addresses********"));
    for(int i=0; i<mesh.addrListTop; i++){
        Serial.print(F("[Radio] NodeID: "));
        Serial.print(mesh.addrList[i].nodeID);
        Serial.print(F(" RF24Network Address: 0"));
        Serial.println(mesh.addrList[i].address,OCT);
    }
    Serial.println(F("[Radio] **********************************"));
}
