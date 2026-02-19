#pragma once

#include <string>

enum class ObjectType
{
    INT, 
    PAIR, 
    STRING,
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

struct StringObject : public Object {
    std::string value;
    StringObject(const std::string& v)
        : Object(ObjectType::STRING), value(v) {}
};
