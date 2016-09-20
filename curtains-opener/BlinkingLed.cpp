#include <Arduino.h>
#include <Led.cpp>

class BlinkingLed {
    enum State {
        S_IDLE,
        S_LEDON,
        S_WAITON,
        S_LEDOFF,
        S_WAITOFF,
        S_TURNOFF
    };

    State state;
    Led led;
    int period;
    int blinkTime;
    unsigned long ts;


public:

    BlinkingLed(int position, int period) : BlinkingLed(position, period * 2, period) {}

    BlinkingLed(int position, int period, int blinkTime) :
            led(position),
            state(S_IDLE),
            period(period - blinkTime),
            blinkTime(blinkTime) {
        led.setup();
    }

    void start();

    void stop();

    void loop();
};

void BlinkingLed::start() {
    state = S_LEDON;
}

void BlinkingLed::stop() {
    state = S_TURNOFF;
}

void BlinkingLed::loop() {
    switch (state) {
        case S_IDLE:
            // We don't need to do anything here, waiting for a forced state change.
            break;
        case S_LEDON:
            led.on();
            ts = millis();  // Remember the current time
            state = S_WAITON;  // Move to the next state
            break;
        case S_WAITON:
            // If one second has passed, then move on to the next state.
            if (millis() > ts + blinkTime) {
                state = S_LEDOFF;
            }
            break;
        case S_LEDOFF:
            led.off();
            ts = millis();  // Remember the current time
            state = S_WAITOFF;
            break;
        case S_WAITOFF:
            // If one second has passed, then go back to state 2.
            if (millis() > ts + period) {
                state = S_LEDON;
            }
            break;
        case S_TURNOFF:
            // We only get here when forced from outside.
            led.off();
            state = S_IDLE;  // Return to the "idle" state.
            break;
        default:
            state = S_IDLE;
            break;
    }
}
