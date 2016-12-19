#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
#include "WifiConfig.h"
#include "CurtainsConfig.h"

LOCAL WiFiClient client;
LOCAL PubSubClient MQTT(client);

LOCAL Ticker pingTimer;
LOCAL bool pingFlag;

LOCAL Ticker curtainsTimer;
LOCAL bool openIntFlag;
LOCAL bool closeIntFlag;

static const String NOOP("NOOP");
static const char *const MAIN_TOPIC = "/room/curtains/general";
LOCAL String command = NOOP;

char *toString(uint8_t *msg, int len);

void onOpen();

void callback(char *topic, byte *payload, unsigned int length);

void stopDrive();

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
    MQTT.setCallback([](char *topic, uint8_t *payload, unsigned int length) -> void {
        char *result = toString(payload, length);
        command = String(result);
        delete[] result;
    });

    pinMode(OPEN_PIN, INPUT_PULLUP);
    pinMode(CLOSE_PIN, INPUT_PULLUP);

    pinMode(DRIVE1_PIN, OUTPUT);
    pinMode(DRIVE2_PIN, OUTPUT);
}

void commandStop() {
    detachInterrupt(OPEN_PIN);
    detachInterrupt(CLOSE_PIN);
    stopDrive();
    curtainsTimer.detach();
    MQTT.publish(MAIN_TOPIC, "Stopped!");
}

void stopDrive() {
    digitalWrite(DRIVE1_PIN, LOW);
    digitalWrite(DRIVE2_PIN, LOW);
}

void commandOpen() {
    void (*callback)()=[]() -> void { 
        openIntFlag = true; 
    };
    attachInterrupt(OPEN_PIN, callback, FALLING);
    digitalWrite(DRIVE1_PIN, HIGH);
    digitalWrite(DRIVE2_PIN, LOW);
    curtainsTimer.once(OPERATION_TIMEOUT, callback);
    MQTT.publish(MAIN_TOPIC, "Opening");
}

void onOpen() {
    openIntFlag = false;
    stopDrive();
    detachInterrupt(OPEN_PIN);
    MQTT.publish(MAIN_TOPIC, "Open!");
}

void commandClose() {
    void (*callback)()=[]() -> void { 
        closeIntFlag = true; 
    };
    attachInterrupt(CLOSE_PIN, callback, FALLING);
    digitalWrite(DRIVE1_PIN, LOW);
    digitalWrite(DRIVE2_PIN, HIGH);
    curtainsTimer.once(OPERATION_TIMEOUT, callback);
    MQTT.publish(MAIN_TOPIC, "Closing");
}

void onClose() {
    closeIntFlag = false;
    stopDrive();
    detachInterrupt(CLOSE_PIN);
    MQTT.publish(MAIN_TOPIC, "Close!");
}

void commandReboot() {
    MQTT.publish(MAIN_TOPIC, "Now rebooting");
    ESP.restart();
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
            MQTT.publish(MAIN_TOPIC, "Curtains just got started");
            // ... and resubscribe
            MQTT.subscribe("/room/curtains/listen");

            pingTimer.attach(PING_TIMEOUT, []() -> void {
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
        MQTT.publish(MAIN_TOPIC, String(ESP.getFreeHeap()).c_str());
    else
        MQTT.publish(MAIN_TOPIC, (String("echo") += command).c_str());

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

    if (openIntFlag)
        onOpen();
    if (closeIntFlag)
        onClose();
}