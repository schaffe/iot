//
// Created by dzidzoiev on 9/25/16.
//
#include <LinkedList.h>
#include <functional-vlpp.h>
#include <Arduino.h>
#include <Event.h>

#ifndef CURTAINS_OPENER_BASE_H
#define CURTAINS_OPENER_BASE_H

typedef vl::Func<void(void)> Callback;

template<typename T>
class ReactiveList : public LinkedList<T> {
public:
    void forEach(vl::Func<void(T element)> foreachFun) {
        for (int i = 0; i < this->_size; i++)
            foreachFun(this->get(i));
    }
};

class Updatable {
public:
    virtual void update() = 0;
};

static ReactiveList<Updatable *> updatable;

namespace Component {
    static void registerComponent(Updatable *updatable1);

    static void updateAll();

    void registerComponent(Updatable *updatable1) {
        updatable.add(updatable1);
    }

    void updateAll() {
        updatable.forEach([](Updatable *component) -> void {
            component->update();
        });
    }
}

/**
 * Should be created as static field
 */
class EventBus {
    Callback listenersMap[Event::__TOTAL][3];

public:

    EventBus(int events) {
    }

    void subscribe(int event, Callback callback) {
        Serial.println("Subscribe");
        listenersMap[0][0] = callback;
        Serial.flush();
    }

    void fire(int event) {
        listenersMap[event][0]();
    }
};

static EventBus *eventBus;

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

#endif //CURTAINS_OPENER_BASE_H
