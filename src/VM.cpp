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
    for (int i = 0; i < globalCount; i++)
    {
        mark(globals[i]);
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

void VM::addGlobal(Object* obj)
{
    assert(globalCount < GLOBAL_MAX && "Too many global roots!");
    globals[globalCount++] = obj;
}


Object *VM::pop()
{
    assert(stacksize > 0 && "Stack underflow!");
    return stack[--stacksize];
}

void VM::gc_unlocked() {
    int prev = numobjects;
    markAll();
    sweep();
    maxobjects = numobjects == 0 ? INITIAL_GC_THRESHOLD : numobjects * 2;

    std::cout << "Collected "
              << (prev - numobjects)
              << " objects, "
              << numobjects << " remaining.\n";
}

void VM::gc()
{
    std::lock_guard<std::mutex> lock(heapMutex);  
    gc_unlocked();
}

void VM::pushInt(int value)
{
    std::lock_guard<std::mutex> lock(heapMutex);  
    if (numobjects == maxobjects)
        gc_unlocked();

    IntObject *object = new IntObject(value);
    object->next = firstobject;
    firstobject = object;

    numobjects++;
    push(object);
}

void VM::pushPair()
{
    std::lock_guard<std::mutex> lock(heapMutex);  
    if (numobjects == maxobjects)
        gc_unlocked();

    // Pop the two objects that will form the pair
    Object *tail = pop();
    Object *head = pop();

    PairObject *object = new PairObject(head, tail);
    object->next = firstobject;
    firstobject = object;

    numobjects++;
    push(object);
}

void VM::pushString(const std::string& value)
{
    std::lock_guard<std::mutex> lock(heapMutex);  
    if (numobjects == maxobjects)
        gc_unlocked();

    StringObject* object = new StringObject(value);

    object->next = firstobject;
    firstobject = object;

    numobjects++;
    push(object);
}
