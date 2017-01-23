#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <TimerOne.h>

#define DETECT 2  //zero cross detect
#define OUT_LIGHT 13

unsigned long lastTime = 0;
volatile uint8_t state = HIGH;
volatile unsigned int tic;
int led1Power = 30;

void detectDown();
void detectUp();
void halfcycle();

void setup() {

    Serial.begin(115200);
    Timer1.initialize(100);
    pinMode(DETECT, INPUT);     //zero cross detect
    pinMode(OUT_LIGHT, OUTPUT);
    Timer1.attachInterrupt(halfcycle);
    Timer1.stop();
    attachInterrupt(0, detectUp, RISING);
}

void halfcycle() {
    tic++;
    digitalWrite(OUT_LIGHT, led1Power < tic);
}

void detectUp() {

    tic = 0;
    Timer1.restart();
    attachInterrupt(0, detectDown, FALLING);
}

void detectDown() {

    tic = 0;
    Timer1.restart();
    attachInterrupt(0, detectUp, RISING);
}


void loop() {

}