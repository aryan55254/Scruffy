# Scruffy

Scruffy is a **thread-safe, stop-the-world Mark-and-Sweep garbage collector implemented in C++**.

It provides a minimal runtime environment that demonstrates tracing garbage collection with multi-source root tracking and safe multi-threaded allocation.

---

## Overview

Scruffy manages heap-allocated objects using a classic two-phase:

1. **Mark** — Traverse reachable objects starting from the root set
2. **Sweep** — Delete all unmarked objects from the heap

The system maintains:

* A manually managed heap (linked list of all allocated objects)
* A fixed-size VM stack acting as a root set
* A global root array for persistent references
* Automatic GC triggering based on allocation threshold
* Mutex-based synchronization for thread-safe operation

---

## Supported Object Types

Scruffy currently supports:

* **INT** — stores an integer value
* **PAIR** — stores references to two heap objects
* **STRING** — stores a heap-allocated string value

PAIR objects form object graphs, allowing nested and cyclic structures.

---

## Features

* Tracing-based garbage collection
* Stop-the-world design
* Multi-root tracking (stack + globals)
* Cyclic reference handling
* Automatic heap threshold adjustment
* Thread-safe heap access using a single global mutex
* Multithreaded stress-tested allocation safety

---

## Architecture

Scruffy separates memory management into three layers:

### Heap

All dynamically allocated objects are stored in a singly linked list.
Used during the sweep phase.

### Root Set

* VM stack (simulated runtime stack)
* Global references

Used as entry points during the mark phase.

### Object Graph

Objects may reference other heap objects.
Traversed recursively during marking.

---

## Thread Safety Model

Scruffy uses a **single mutex** to protect all heap state.

* Only one thread may mutate the heap at a time.
* GC pauses all mutator threads (stop-the-world).
* No concurrent marking or parallel sweeping.

This ensures correctness under multi-threaded allocation without introducing write barriers or concurrent GC complexity.

---

## Limitations

* Stop-the-world collector
* Single global heap
* Recursive marking (not iterative)
* No generational GC
* No concurrent or parallel GC
* Single mutex serialization (no per-thread heaps)

---

## Build and Run

### Single-threaded tests

```bash
g++ -std=c++17 -I ./include src/VM.cpp tests/test.cpp -o test
./test
```

### Multithreaded stress test

```bash
g++ -std=c++17 -pthread -I ./include src/VM.cpp tests/multithread_test.cpp -o mt_test
./mt_test
```