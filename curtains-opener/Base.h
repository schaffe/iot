//
// Created by dzidzoiev on 9/25/16.
//
#include <LinkedList.h>
#include <functional-vlpp.h>

#ifndef CURTAINS_OPENER_BASE_H
#define CURTAINS_OPENER_BASE_H

template <typename T>
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

static ReactiveList<Updatable*> updatable;

static void registerComponent(Updatable *updatable1);

static void updateAll();

void registerComponent(Updatable *updatable1) {
    updatable.add(updatable1);
}

void updateAll() {
    updatable.forEach([](Updatable* component) -> void {
        component->update();
    });
}

#endif //CURTAINS_OPENER_BASE_H
