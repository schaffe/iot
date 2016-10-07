#include <Arduino.h>
#include <Base.h>

enum State {
    T_ON,
    S_ON,
    T_OFF,
    S_OFF,
};

class Clap : public Updatable {
    const unsigned int threshold = 20;
    const uint8_t sensorPin;
    boolean sound;

    bool isSound() const {
        auto soundValue = analogRead(sensorPin);
        if (soundValue < 1000)
            Serial.println(soundValue);
        return soundValue < threshold;
    }

public:
    Clap(uint8_t analogPin) : sensorPin(analogPin) {
        Component::registerComponent(this);
    }

    virtual void update() override {
        if (isSound()) {
            sound = true;
            return;
        }

        if (sound && !isSound())
            eventBus->fire(0);
    }

};


/****
 * PROGRAM
 ****/

static State state = T_ON;
static DigitalPin lamp(13);

static Clap clap(0);

void onClap() {
    switch (state) {
        case T_ON:
            lamp.on();
            state = T_OFF;
            break;
        case T_OFF:
            lamp.off();
            state = T_ON;
            break;
    }
}

void setup() {
    Serial.begin(9600);
    lamp.on();
//    eventBus->subscribe(0, vl::Func<void(void)>(onClap));
}

void loop() {
    Serial.println(analogRead(0));
    Component::updateAll();
}
