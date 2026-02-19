#include "VM.hpp"

void VM::mark(Object *object)
{
    if (object == nullptr || object->marked)
        return;
    object->marked = true;

    if (object->type == ObjectType::PAIR)
    {
        PairObject *pair = static_cast<PairObject *>(object); // static cast is
        mark(pair->head);
        mark(pair->tail);
    }
}

void VM::markAll()
{
    for (int i = 0; i < stacksize; i++)
    {
        mark(stack[i]);
    }
}

void VM::sweep()
{
    Object **object = &firstobject;
    while (*object)
    {
        if (!(*object)->marked)
        {
            // Garbage found
            Object *unreached = *object;
            *object = unreached->next;

            delete unreached;
            numobjects--;
        }
        else
        {
            // Object is alive, reset mark for next cycle
            (*object)->marked = false;
            object = &(*object)->next;
        }
    }
}

void VM::push(Object *value)
{
    assert(stacksize < STACK_MAX && "Stack overflow!");
    stack[stacksize++] = value;
}

Object *VM::pop()
{
    assert(stacksize > 0 && "Stack underflow!");
    return stack[--stacksize];
}

void VM::gc()
{
    int prevNumObjects = numobjects;

    markAll();
    sweep();

    // Adjust threshold dynamically
    maxobjects = numobjects == 0 ? INITIAL_GC_THRESHOLD : numobjects * 2;

    std::cout << "Collected " << (prevNumObjects - numobjects)
              << " objects, " << numobjects << " remaining.\n";
}
void VM::pushInt(int value)
{
    if (numobjects == maxobjects)
        gc();

    IntObject *object = new IntObject(value);
    object->next = firstobject;
    firstobject = object;

    numobjects++;
    push(object);
}

void VM::pushPair()
{
    if (numobjects == maxobjects)
        gc();

    // Pop the two objects that will form the pair
    Object *tail = pop();
    Object *head = pop();

    PairObject *object = new PairObject(head, tail);
    object->next = firstobject;
    firstobject = object;

    numobjects++;
    push(object);
}