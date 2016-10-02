//
// Created by dzidzoiev on 9/14/16.
//
#include <Arduino.h>
#include <functional-vlpp.h>
#include <Base.h>
#include <Event.h>

static const int DEBOUNCE = 20;          // ms debounce period to prevent flickering when pressing or releasing the button

class Button : public Updatable {
    enum State {
        ENABLED,
        DISABLED
    };
    State state;
    int position;
    int debounceCount;
    boolean disabledState;

public:
    Button(int position) : position(position) {
        state = DISABLED;
        pinMode(position, INPUT_PULLUP);
        disabledState = digitalRead(position);
        Component::registerComponent(this);
    }

    void update() {
        if (disabledState != digitalRead(position)) {
            debounceCount++;
        } else {
            debounceCount = 0;

            if (state == ENABLED) {
                eventBus->fire(0);
            }

            state = DISABLED;
            return;
        }

        if (debounceCount > DEBOUNCE) {
            state = ENABLED;
        }
    }

    boolean isEnabled() {
        return state == ENABLED;
    }
};

