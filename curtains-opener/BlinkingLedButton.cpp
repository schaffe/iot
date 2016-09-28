#include <Arduino.h>
#include <Button.cpp>
#include <BlinkingLed.cpp>
#include <Base.h>

enum State {
    T_STARTED = 0,
    S_STARTED,
    T_STOPPED,
    S_STOPPED,
    __TOTAL
};

struct Event {
    enum EventEnum {
        E_BUTTON_CLICK = 0,
        __TOTAL
    };
};

static EventBus* eventBus = new EventBus();

class ButtonFSM : public Updatable {

    const unsigned int BTN_DELAY = 300;

    mutable State state;
    Button button;
    BlinkingLed blinkingLed;
    unsigned long ts;

    void changeState() {
        if (state == S_STARTED || state == T_STARTED)
            state = T_STOPPED;
        else
            state = T_STARTED;
    }

public:
    ButtonFSM() :
            state(T_STOPPED),
            button(8),
            blinkingLed(13, 100) {
        Component::registerComponent(this);
        eventBus->subscribe(Event::E_BUTTON_CLICK, [this]() -> void {
            changeState();
        });
    }

    void update() {
        switch (state) {
            case T_STARTED:
//                Serial.println( "T_STARTED change state ");
                blinkingLed.start();
                state = S_STARTED;
                break;
            case T_STOPPED:
//                Serial.println( "T_STOPPED change state ");
                blinkingLed.stop();
                state = S_STOPPED;
                break;
        }
    }
};