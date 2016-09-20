#include <Arduino.h>
#include <HallSensor.cpp>
#include <DcMotor.cpp>
#include <TrafficLight.cpp>
#include <Button.cpp>

//HallSensor hallSensor1 (0);
//DcMotor motor (9, 10, 11);
//Led led (13);
//Button btn(8);
static TrafficLight trafficLight;

void setup() {
//    btn.setup();
//    led.setup();
//    Serial.begin(9600);
}

void loop() {
    trafficLight.loop();
}
