#define EBUS_ENABLED 0
#include <Arduino.h>

#include <Base.h>
#include <OneButton.h>
enum State {
    T_ON,
    S_ON,
    T_OFF,
    S_OFF,
};

static const unsigned int threshold = 40;

void onClap();

class Clap : public Updatable {
    static const unsigned long debounce = 30;
    const uint8_t sensorPin;
    boolean wasSound;
    unsigned long ts;

    bool isSound() const {
        auto soundValue = analogRead(sensorPin);
//        if (soundValue < 1000)
//            Serial.println(soundValue);
        return soundValue < threshold;
    }

public:
    Clap(uint8_t analogPin) : sensorPin(analogPin) {
        Component::registerComponent(this);
    }

    virtual void update() override {
//        Serial.println("update");
        if (!wasSound && isSound()) {
            wasSound = true;
            ts = millis();
            return;
        }
        if (ts + debounce > millis() && wasSound && !isSound()) {
            wasSound = false;

            onClap();
        }
    }

};

static int isSound(uint8_t pin) {
    auto soundValue = analogRead(pin);
//        if (soundValue < 1000)
//            Serial.println(soundValue);
    return soundValue < threshold;
}

/****
 * PROGRAM
 ****/

static State state = T_OFF;
static DigitalPin lamp(12);
static OneButton button(0, true, isSound);

//static volatile Clap clap(0);

void onClap() {
    switch (state) {
        case T_ON:
            lamp.off();
            state = T_OFF;
            break;
        case T_OFF:
            lamp.on();
            state = T_ON;
            break;
    }
}

void setup() {
    callbackFunction c;
    button.attachDoubleClick(onClap);
    onClap();
//    Serial.begin(9600);
//    lamp.on();
//    eventBus->subscribe(0, vl::Func<void(void)>(onClap));
}

void loop() {
    button.tick();
//    Serial.println(analogRead(0));
    Component::updateAll();
}
