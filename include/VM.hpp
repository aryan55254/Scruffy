#pragma once

#include <iostream>
#include <cassert>
#include "Object.hpp"

class VM
{
private:
    static constexpr int STACK_MAX = 256;
    static constexpr int INITIAL_GC_THRESHOLD = 8;

    Object *stack[STACK_MAX];
    int stacksize;

    Object *firstobject;
    int numobjects;
    int maxobjects;

    void mark(Object *object);

    void markAll();

    void sweep();

public:
    VM() : stacksize(0), firstobject(nullptr), numobjects(0), maxobjects(INITIAL_GC_THRESHOLD) {}
    ~VM()
    {
        // Cleanup all remaining objects on shutdown
        stacksize = 0;
        gc();
    }

    void push(Object *value);

    Object *pop();

    void gc();
    void pushInt(int value);

    void pushPair();
};