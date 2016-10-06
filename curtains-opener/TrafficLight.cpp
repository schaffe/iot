#include <BlinkingLed.cpp>


class TrafficLight {

    const int TIME_WALK = 3000;
    const int YELLOW_TIME = 3000;
    const int BLINK_TIME = 5000;

    enum State {
        S_GREEN_ON,
        S_GREEN_ON_WAIT,
        S_GREEN_BLINK,
        S_GREEN_BLINK_WAIT,
        S_YELLOW_ON,
        S_YELLOW_ON_WAIT,
        S_RED_ON,
        S_RED_ON_WAIT,
        S_RED_BLINK,
        S_RED_BLINK_WAIT
    };

    BlinkingLed green;
    BlinkingLed red;
    BlinkingLed yellow;
    State state;
    unsigned long ts;

public:
    TrafficLight() :
            green(13, 500),
            red(12, 500),
            yellow(11, 500),
            state(S_GREEN_ON) {};

    void loop() {
        green.update();
        red.update();

        switch (state) {
            case S_GREEN_ON:
                green.getLed().on();
                ts = millis();
                state = S_GREEN_ON_WAIT;
                break;
            case S_GREEN_ON_WAIT:
                if (millis() > ts + TIME_WALK) {
                    green.getLed().off();
                    state = S_GREEN_BLINK;
                }
                break;
            case S_GREEN_BLINK:
                green.start();
                ts = millis();
                state = S_GREEN_BLINK_WAIT;
                break;
            case S_GREEN_BLINK_WAIT:
                if (millis() > ts + BLINK_TIME) {
                    green.stop();
                    state = S_YELLOW_ON;
                }
                break;
            case S_YELLOW_ON:
                yellow.getLed().on();
                ts = millis();
                state = S_YELLOW_ON_WAIT;
                break;
            case S_YELLOW_ON_WAIT:
                if (millis() > ts + YELLOW_TIME) {
                    yellow.getLed().off();
                    state = S_RED_ON;
                }
                break;
            case S_RED_ON:
                red.getLed().on();
                ts = millis();
                state = S_RED_ON_WAIT;
                break;
            case S_RED_ON_WAIT:
                if (millis() > ts + TIME_WALK) {
                    state = S_RED_BLINK;
                }
                break;
            case S_RED_BLINK:
                red.getLed().on();
                yellow.getLed().on();
                ts = millis();
                state = S_RED_BLINK_WAIT;
                break;
            case S_RED_BLINK_WAIT:
                if (millis() > ts + YELLOW_TIME) {
                    red.getLed().off();
                    yellow.getLed().off();
                    state = S_GREEN_ON;
                }
                break;
            default:
                green.stop();
                red.stop();
                break;
        }
    }
};

