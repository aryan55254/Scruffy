#include "VM.hpp"
#include <iostream>
#include <thread>
#include <vector>
#include <random>

void worker(VM& vm, int id)
{
    std::mt19937 rng(id);
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < 5000; i++)
    {
        int choice = dist(rng) % 3;

        if (choice == 0)
        {
            vm.pushInt(i);
            vm.pop();
        }
        else if (choice == 1)
        {
            vm.pushInt(i);
            vm.pushInt(i + 1);
            vm.pushPair();
            vm.pop();
        }
        else
        {
            vm.pushString("thread_" + std::to_string(id));
            vm.pop();
        }

        // Occasionally trigger manual GC
        if (i % 1000 == 0)
        {
            vm.gc();
        }
    }
}

int main()
{
    std::cout << "=== Multithreaded GC Stress Test ===\n";

    VM vm;

    const int THREAD_COUNT = 4;
    std::vector<std::thread> threads;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        threads.emplace_back(worker, std::ref(vm), i);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    // Final cleanup
    vm.gc();

    std::cout << "Multithreaded test completed successfully.\n";
    return 0;
}
