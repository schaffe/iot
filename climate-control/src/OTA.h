//
// Created by dzidzoiev on 22.12.16.
//

#ifndef CLIMATE_CONTROL_OTA_H
#define CLIMATE_CONTROL_OTA_H
#include <ArduinoOTA.h>

static long lastChecked;

class OTA {

public:
    static void init() {

        // Port defaults to 8266
        // ArduinoOTA.setPort(8266);

        // Hostname defaults to esp8266-[ChipID]
        // ArduinoOTA.setHostname("myesp8266");

        // No authentication by default
        // ArduinoOTA.setPassword((const char *)"123");

        ArduinoOTA.onStart([]() {
            Serial.println("Start");
        });
        ArduinoOTA.onEnd([]() {
            Serial.println("\nEnd");
        });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            int p = (progress / (total / 100));
            if(p % 10 == 0) {
                Serial.print(p);
                Serial.println("%");
            }
        });
        ArduinoOTA.onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });
        ArduinoOTA.begin();
        lastChecked = millis();
    }

    static void handle() {
        if ( lastChecked < millis() - 1000 ) {
            lastChecked = millis();
//            Serial.println("check for update");
            ArduinoOTA.handle();
        }
    }

};

extern OTA OTA;


#endif //CLIMATE_CONTROL_OTA_H
