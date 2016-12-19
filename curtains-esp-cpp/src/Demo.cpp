#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "WifiConfig.h"

LOCAL WiFiClient client;
LOCAL PubSubClient MQTT(client);

LOCAL Ticker pingTimer;
LOCAL bool pingFlag;

const String NOOP("NOOP");
LOCAL String command = NOOP;

char *toString(uint8_t *msg, int len);

void callback(char *topic, byte *payload, unsigned int length);

void setup() {
    Serial.begin(115200);
    delay(10);

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(F("."));
    }
    Serial.println(F(" WiFi connected."));

    MQTT.setServer(MQTT_SERVER, MQTT_PORT);
    MQTT.setCallback(callback);

}

void commandStop() {
    MQTT.publish("/room/curtains/general", "Stopping");
}

void commandOpen() {
    MQTT.publish("/room/curtains/general", "Opening");
}

void commandClose() {
    MQTT.publish("/room/curtains/general", "Closing");
}

void commandReboot() {
    MQTT.publish("/room/curtains/general", "Now rebooting");
    ESP.restart();
}

void callback(char *topic, uint8_t *payload, unsigned int length) {
    char *result = toString(payload, length);
    command = String(result);
    delete[] result;
}

char *toString(uint8_t *msg, int len) {
    char *result = new char[len];
    for (int i = 0; i < len; ++i) {
        result[i] = (char) msg[i];
    }
    result[len] = '\0';
    return result;
}

void reconnect() {
    // Loop until we're reconnected
    while (!MQTT.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (MQTT.connect("ESP8266Client")) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            MQTT.publish("/room/curtains/general", "Curtains just got started");
            // ... and resubscribe
            MQTT.subscribe("/room/curtains/listen");

            pingTimer.attach(5, []() -> void {
                Serial.println("Ping....");
                pingFlag = true;
            });
        } else {
            Serial.print("failed, rc=");
            Serial.print(MQTT.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void handleCommand() {
    if (command == NOOP)
        return;
    else if (command.equals("stop"))
        commandStop();
    else if (command.equals("open"))
        commandOpen();
    else if (command.equals("close"))
        commandClose();
    else if (command.equals("reboot"))
        commandReboot();
    else if (command.equals("heap"))
        MQTT.publish("/room/curtains/general", String(ESP.getFreeHeap()).c_str());
    else
        MQTT.publish("/room/curtains/general", (String("echo") += command).c_str());

    command = NOOP;
}

void loop() {

    if (!MQTT.connected()) {
        reconnect();
    }
    MQTT.loop();
    if (pingFlag) {
        MQTT.publish("/room/curtains/ping", "curtains");
        pingFlag = false;
        yield();
    }
    handleCommand();

//    long now = millis();
//    if (now - lastMsg > 2000) {
//        lastMsg = now;
//        ++value;
//        snprintf (msg, 75, "hello world #%ld", value);
//        Serial.print("Publish message: ");
//        Serial.println(msg);
//        MQTT.publish("outTopic", msg);
//    }
}