# Scruffy

Scruffy is a **minimal Mark-and-Sweep garbage collector implemented in C++**.

It is a small, single-threaded runtime designed to demonstrate the fundamentals of tracing garbage collection, including root tracking, reachability analysis, and heap sweeping.

The system maintains:

* A manually managed heap (linked list of allocated objects)
* A fixed-size VM stack acting as the root set
* A classic two-phase **Mark → Sweep** collection cycle

Scruffy currently supports two object types:

* **INT** — stores an integer value
* **PAIR** — stores references to two heap objects

Garbage collection is triggered automatically when an allocation threshold is reached, or manually via `gc()`.

The implementation is:

* **Tracing-based**
* **Stop-the-world**
* **Single-threaded**

Scruffy focuses purely on correctness and clarity, serving as a foundation for experimenting with more advanced GC strategies in the future.
