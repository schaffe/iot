//
// Created by dzidzoiev on 9/25/16.
//
#include <LinkedList.h>
#include <functional-vlpp.h>
#include <Arduino.h>

#ifndef CURTAINS_OPENER_BASE_H
#define CURTAINS_OPENER_BASE_H

typedef vl::Func<void()> Callback;

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
    LinkedList<ReactiveList<Callback>> listenersMap;

public:
    void subscribe(int event, Callback callback) {
        listenersMap.get(event).add(callback);
    }

    void fire(int event) {
        ReactiveList<Callback> callbacksForEvent = listenersMap.get(event);
//        Serial.println(callbacksForEvent);
        callbacksForEvent.forEach([](Callback callback) -> void {
            callback();
        });
    }
};
#endif //CURTAINS_OPENER_BASE_H
