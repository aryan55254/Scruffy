#pragma once

#include <iostream>
#include <cassert>
#include <mutex>
#include "Object.hpp"

class VM
{
private:
    std::mutex heapMutex;

    static constexpr int STACK_MAX = 256;
    static constexpr int INITIAL_GC_THRESHOLD = 8;
    static constexpr int GLOBAL_MAX = 256;

    Object *globals[GLOBAL_MAX];
    int globalCount;

    Object *stack[STACK_MAX];
    int stacksize;

    Object *firstobject;
    int numobjects;
    int maxobjects;

    void mark(Object *object);

    void markAll();

    void sweep();

public:
    VM() : stacksize(0), firstobject(nullptr), numobjects(0), maxobjects(INITIAL_GC_THRESHOLD) , globalCount(0) {}
    ~VM()
    {
        // Cleanup all remaining objects on shutdown
        stacksize = 0;
        gc();
    }

    void push(Object *value);

    void addGlobal(Object* obj);

    Object *pop();

    void gc();

    void gc_unlocked();

    void pushInt(int value);

    void pushPair();

    void pushString(const std::string& value);

};