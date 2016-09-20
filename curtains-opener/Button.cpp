//
// Created by dzidzoiev on 9/14/16.
//
#include <Arduino.h>

class Button {
private:
    int position;
public:
    Button(int position) {
        this->position = position;
    }

    void setup();
    boolean read();
};

void Button::setup() {
    pinMode(position, INPUT_PULLUP);
}

boolean Button::read() {
    return !digitalRead(position);
}