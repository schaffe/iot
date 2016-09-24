//
// Created by dzidzoiev on 9/14/16.
//
#include <Arduino.h>

class Led {
private:
    int position;
public:
    Led(int position) {
        this->position = position;
        setup();
    }

    void setup();
    boolean on();
    boolean off();
};

void Led::setup() {
    pinMode(position, OUTPUT);
}

boolean Led::on() {
    digitalWrite(position, HIGH);
}

boolean Led::off() {
    digitalWrite(position, LOW);
}