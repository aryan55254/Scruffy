#pragma once

enum class ObjectType
{
    INT, 
    PAIR
};

struct Object
{
    ObjectType type;
    bool marked;
    Object *next; //pointer for linked list 

    Object(ObjectType type) : type(type), marked(false), next(nullptr) {}
    virtual ~Object() {} // virtual destructor for inhertance 
};

struct IntObject : public Object
{
    int value;
    IntObject(int value) : Object(ObjectType ::INT), value(value) {}
};

struct PairObject : public Object
{
    Object *head;
    Object *tail;
    PairObject(Object *head, Object *tail) : Object(ObjectType ::PAIR), head(head), tail(tail) {}
};