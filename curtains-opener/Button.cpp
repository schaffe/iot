//
// Created by dzidzoiev on 9/14/16.
//
#include <Arduino.h>
#include <FSMObject.h>
#include <functional-vlpp.h>

typedef vl::Func<void()> Callback;
static const int DEBOUNCE = 20;          // ms debounce period to prevent flickering when pressing or releasing the button

class Button {
    enum State {
        ENABLED,
        DISABLED
    };
    State state;
    int position;
    int debounceCount;
    boolean disabledState;
    Callback onClickCallback;

public:
    Button(int position) : position(position) {
        state = DISABLED;
        pinMode(position, INPUT_PULLUP);
        disabledState = digitalRead(position);
    }

    void onClick(Callback callback) {
        this->onClickCallback = callback;
    }

    void loop() {
        if (disabledState != digitalRead(position)) {
            debounceCount++;
        } else {
            debounceCount = 0;

            if (state == ENABLED)
                onClickCallback();

            state = DISABLED;
            return;
        }

        if (debounceCount > DEBOUNCE) {
            state = ENABLED;
            Serial.println("State ENABLED " + debounceCount);
        }
    }

    boolean isEnabled() {
        return state == ENABLED;
    }
};

