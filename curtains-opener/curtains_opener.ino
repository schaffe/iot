#include <Arduino.h>
#include <HallSensor.cpp>
#include <DcMotor.cpp>

HallSensor hallSensor1 (0);
DcMotor motor (9, 10, 11);

void setup() {
    // initialize digital pin 13 as an output.
    hallSensor1.setup();
    motor.setup();
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
    if (hallSensor1.readDigital()) {
        motor.run(false);
    } else
    {
        motor.stop();
    }
    delay(500);
//    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);              // wait for a second
//    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
//    delay(1000);              // wait for a second
}
