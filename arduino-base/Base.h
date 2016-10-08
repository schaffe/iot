//
// Created by dzidzoiev on 9/25/16.
//
//#include <LinkedList/LinkedList.h>
//#include <functional-vlpp/src/functional-vlpp.h>
#include <Arduino.h>

#ifndef CURTAINS_OPENER_BASE_H
#define CURTAINS_OPENER_BASE_H

#ifndef COMPONENTS_COUNT
#define COMPONENTS_COUNT 5
#endif

typedef void(*Callback)(void);

//typedef vl::Func<void(void)> Callback;

//template<typename T>
//class ReactiveList : public LinkedList<T> {
//public:
//    void forEach(vl::Func<void(T element)> foreachFun) {
//        for (int i = 0; i < this->_size; i++)
//            foreachFun(this->get(i));
//    }
//};

class Updatable {
public:
    virtual void update() = 0;
};

namespace Component {

    static Updatable** updatable = new Updatable*[COMPONENTS_COUNT];
    static uint8_t count;

    static void registerComponent(Updatable *updatable1);

    static void updateAll();

    void registerComponent(Updatable *updatable1) {
        updatable[count++] = updatable1;
    }

    void updateAll() {
        for (int i = 0; i < count; ++i) {
            if (updatable[i] != NULL)
                updatable[i]->update();
        }
    }
}


#ifndef EBUS_ENABLED
#define EBUS_ENABLED 1
#endif
#if EBUS_ENABLED
#ifndef CALLBACK_NUM
#define CALLBACK_NUM 1
#endif
#ifndef EBUS_EVENT_NUM
#define EBUS_EVENT_NUM 1
#endif
#ifndef EBUS_CALLBACK_NUM
#define EBUS_CALLBACK_NUM 1
#endif
/**
 * Should be created as static field
 */
class EventBus {
    Callback listenersMap[EBUS_EVENT_NUM][EBUS_CALLBACK_NUM];

public:

    EventBus(int events) {
    }

    void subscribe(int event, Callback callback) {
//        log("Subscribe");
        listenersMap[0][0] = callback;
    }

    void fire(int event) {
//        log(event);
        listenersMap[event][0]();
    }
};

static EventBus *eventBus;
#endif //EBUS_ENABLED

class Timer : public Updatable {
    unsigned long fireTime;
    Callback callback;

public:
    Timer(Callback callback, unsigned long ms) :
            fireTime(millis() + ms),
            callback(callback) {
        Component::registerComponent(this);
    }

    void update() {
        if (millis() >= fireTime)
            callback();
        delete this;
    }
};

class DigitalPin {
private:
    const uint8_t position;
    mutable bool state;
public:
    DigitalPin(uint8_t position) : position(position), state(false) {
        pinMode(position, OUTPUT);
    }

    bool getState() {
        return state;
    }

    void on(void) {
        digitalWrite(position, HIGH);
        state = true;
    }

    void off(void) {
        digitalWrite(position, LOW);
        state = false;
    }
};

#endif //CURTAINS_OPENER_BASE_H
