//
// Created by dzidzoiev on 9/15/16.
//
#include <Arduino.h>

class DcMotor {
    int enablePos;
    int a1Pos;
    int a2Pos;
public:
    DcMotor(int enablePosition, int a1, int a2) {
        this->a1Pos = a1;
        this->a2Pos = a2;
        this->enablePos = enablePosition;
    }
    void setup() {
        pinMode(enablePos, OUTPUT);
        pinMode(a1Pos, OUTPUT);
        pinMode(a2Pos, OUTPUT);
    }
    void run(boolean reverse);
    void stop();
};

void DcMotor::run(boolean reverse) {
    digitalWrite(a1Pos, reverse);
    digitalWrite(a2Pos, !reverse);
    digitalWrite(enablePos, HIGH);
}

void DcMotor::stop() {
    digitalWrite(enablePos, LOW);
}