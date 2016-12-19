#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "WifiConfig.h"

LOCAL WiFiClient client;
LOCAL PubSubClient MQTT(client);

LOCAL Ticker pingTimer;
LOCAL bool pingFlag;

long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length);

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

void callback(char* topic, uint8_t* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    MQTT.publish("/room/curtains/general", "echo");
//    for (int i = 0; i < length; i++) {
//        Serial.print((char)payload[i]);
//    }
//    Serial.println();

//    // Switch on the LED if an 1 was received as first character
//    if ((char)payload[0] == '1') {
//        digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//        // but actually the LED is on; this is because
//        // it is acive low on the ESP-01)
//    } else {
//        digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//    }

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

void loop() {

    if (!MQTT.connected()) {
        reconnect();
    }
    MQTT.loop();
    if (pingFlag) {
        MQTT.publish("/room/curtains/ping", "curtains");
        pingFlag = false;
    }

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
