//
// Created by dzidzoiev on 9/14/16.
//
#include <Arduino.h>

const int DEFAULT_DIST = 40;

class HallSensor {
    private:
        int normalValue;
        int position;
    public:
        HallSensor(int position) {
            this->position = position;
        }
        void setup();
        boolean readDigital();
        int readAnalog();
};

void HallSensor::setup() {
    normalValue = analogRead(position);
}

int HallSensor::readAnalog() {
    return analogRead(position);
}

boolean HallSensor::readDigital() {
    int level = analogRead(position);
    int dist = normalValue - level;
    return abs(dist) > DEFAULT_DIST;
}