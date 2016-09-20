#include <Arduino.h>
#include <HallSensor.cpp>
#include <DcMotor.cpp>
#include <BlinkingLed.cpp>
#include <Button.cpp>

//HallSensor hallSensor1 (0);
//DcMotor motor (9, 10, 11);
//Led led (13);
//Button btn(8);
static BlinkingLed blinkingLed (13, 2000, 500);
static BlinkingLed blinkingLed2 (12, 2000, 100);

void setup() {
//    btn.setup();
//    led.setup();
//    Serial.begin(9600);
    blinkingLed.start();
    blinkingLed2.start();
}

void loop() {
    blinkingLed.loop();
    blinkingLed2.loop();
//    delay(500);
//    if ( btn.read() )
//        led.on();
//    else
//        led.off();
//    static int state = 1; // initial state is 1, the "idle" state.
//    static unsigned long ts;  // To store the "current" time in for delays.
//
//    switch (state) {
//        case 1:
//            // We don't need to do anything here, waiting for a forced state change.
//            break;
//        case 2:
//            digitalWrite(13, HIGH);  // Turn on the light
//            ts = millis();  // Remember the current time
//            state = 3;  // Move to the next state
//            break;
//        case 3:
//            // If one second has passed, then move on to the next state.
//            if (millis() > ts + 1000) {
//                state = 4;
//            }
//            break;
//        case 4:
//            digitalWrite(13, LOW);  // Turn off the light
//            ts = millis();  // Remember the current time
//            state = 5;
//            break;
//        case 5:
//            // If one second has passed, then go back to state 2.
//            if (millis() > ts + 1000) {
//                state = 2;
//            }
//            break;
//        case 6:
//            // We only get here when forced from outside.
//            digitalWrite(13, LOW);  // Turn off the light
//            state = 1;  // Return to the "idle" state.
//            break;
//        default:
//            state = 1;
//            break;
//    }
}

//void setup() {
//    // initialize digital pin 13 as an output.
//    hallSensor1.setup();
//    motor.setup();
//    pinMode(13, OUTPUT);
//    Serial.begin(9600);
//}
//
//// the loop function runs over and over again forever
//void loop() {
//    if (hallSensor1.readDigital()) {
//        motor.run(false);
//    } else
//    {
//        motor.stop();
//    }
//    delay(500);
////    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
////    delay(1000);              // wait for a second
////    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
////    delay(1000);              // wait for a second
//}
