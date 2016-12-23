#include <Arduino.h>
#include <WifiConfig.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <OTA.h>
#include <dht.h>
#include <Ticker.h>

LOCAL dht DHT;
LOCAL const uint8_t DHT11_PIN = D2;

LOCAL WiFiClient client;
LOCAL PubSubClient MQTT(client);
LOCAL Ticker sensorTimer;
volatile bool sensorFlag;
LOCAL Ticker ping;
bool pingFlag;

IPAddress ipAddress;

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    OTA.init();
    Serial.println("Ready");
    Serial.print("IP address: ");
    ipAddress = WiFi.localIP();
    Serial.println(ipAddress);

    MQTT.setServer(MQTT_SERVER, MQTT_PORT);
    sensorTimer.attach(30, []()->void{
        sensorFlag = true;
    });
    ping.attach(5, []() -> void {
        pingFlag = true;
    });
}

void dhtRead();

char* buff = new char[100];
uint8_t* int_buff = new uint8_t[1];

void dhtRead()
{
    // READ DATA
    Serial.print("DHT11, \t");
    int chk = DHT.read11(DHT11_PIN);
    switch (chk)
    {
        case DHTLIB_OK:
            Serial.print("OK,\t");
            break;
        case DHTLIB_ERROR_CHECKSUM:
            Serial.print("Checksum error,\t");
            break;
        case DHTLIB_ERROR_TIMEOUT:
            Serial.print("Time out error,\t");
            break;
        default:
            Serial.print("Unknown error,\t");
            break;
    }
    // DISPLAY DATA
    sprintf(buff, "%d", (int) DHT.temperature);
    MQTT.publish("/room/sensor/temperature", buff);
    sprintf( buff, "%d", (int) DHT.humidity);
    MQTT.publish("/room/sensor/humidity", buff);

    Serial.print(buff);
    Serial.print(",\t");
    Serial.println(DHT.temperature, 1);
}

static void reconnect() {
    // Loop until we're reconnected
    while (!MQTT.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        sprintf( buff, "%d", ESP.getChipId() );
        if (MQTT.connect((String("ESP8266") + buff).c_str())) {
            Serial.println( "connected");
            // Once connected, publish an announcement...
            MQTT.publish("/room/sensor/general", WiFi.localIP().toString().c_str());
            // ... and resubscribe
//            MQTT.subscribe(LISTEN_TOPIC);
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
    OTA.handle();
    if (!MQTT.connected()) {
        reconnect();
    }
    if (sensorFlag) {
        sensorFlag = false;
        dhtRead();
    }
    if (pingFlag) {
        pingFlag = false;
        MQTT.publish("/room/sensor/ping", ipAddress.toString().c_str());
    }
}
