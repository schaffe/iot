#include <Arduino.h>
#include <Button.cpp>
#include <BlinkingLed.cpp>
#include <Base.h>

enum State {
    T_STARTED = 10,
    S_STARTED,
    T_STOPPED,
    S_STOPPED,
};

class ButtonFSM : public Updatable {

    const unsigned int BTN_DELAY = 300;

    mutable State state;
    Button button;
    BlinkingLed blinkingLed;
    unsigned long ts;

public:
    ButtonFSM() :
            state(T_STOPPED),
            button(8),
            blinkingLed(13, 100) {
        registerComponent(this);
    }

    void update() {
        switch (state) {
            case T_STARTED:
//                Serial.println( "T_STARTED change state ");
                blinkingLed.start();
                state = S_STARTED;
                break;
            case S_STARTED:
                button.onClick([this]() -> void {
                    state = T_STOPPED;
                });
                break;
            case T_STOPPED:
//                Serial.println( "T_STOPPED change state ");
                blinkingLed.stop();
                state = S_STOPPED;
                break;
            case S_STOPPED:
                button.onClick([this]() -> void {
                    state = T_STARTED;
                });
                break;
        }
    }
};