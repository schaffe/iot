#include <Arduino.h>

#define threshold 230
#define DEBOUNCE_TIME 100
#define SECOND_CLAP_DELAY 400

static const uint8_t sensor = A0;
static const uint8_t lamp = 8;

uint8_t claps = 0;
unsigned long tsInitial = 0;
unsigned long ts = 0;
boolean lightState = false;

void onClap();
bool isSound();

void setup() {
    pinMode(lamp, OUTPUT);
    digitalWrite(sensor, HIGH);
//    Serial.begin(9600);
}

void loop() {

    boolean sound = isSound();

    if (sound)
    {
        if (claps == 0)
        {
            tsInitial = ts = millis();
            claps++;
        }
        else if (claps > 0 && millis()-ts >= DEBOUNCE_TIME)
        {
            ts = millis();
            claps++;
        }
    }

    if (millis()-tsInitial >= SECOND_CLAP_DELAY)
    {
        if (claps == 2)
        {
            onClap();
        }
        claps = 0;
    }
}

void onClap() {
    Serial.println(claps);
    if (lightState)
        digitalWrite(lamp, LOW);
    else
        digitalWrite(lamp, HIGH);
    lightState = !lightState;
}

bool isSound() {
    auto soundValue = ( 1024 - analogRead(sensor) ) / 4;
//    if (soundValue > 10)
//        Serial.println(soundValue);
    return soundValue > threshold;
}
