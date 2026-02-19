#include "VM.hpp"
#include <iostream>

void test1() {
    std::cout << "--- Test 1: Basic allocation and collection ---" << std::endl;
    VM vm;

    vm.pushInt(10);
    vm.pushInt(20);

    vm.gc(); // Nothing should be collected (2 remaining)

    vm.pop();
    vm.pop();

    vm.gc(); // Both should be collected (0 remaining)
}

void test2() {
    std::cout << "\n--- Test 2: Nested objects ---" << std::endl;
    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair(); // pair(1,2)

    vm.gc(); // Nothing collected

    vm.pop(); // Remove pair from stack

    vm.gc(); // Should collect pair + both ints
}

void test3() {
    std::cout << "\n--- Test 3: Stress test / Automatic GC ---" << std::endl;
    VM vm;

    for (int i = 0; i < 1000; i++)
    {
        vm.pushInt(i);
        vm.pop(); // immediately remove reference
    }

    vm.gc(); // Should collect all
}

void test4() {
    std::cout << "\n--- Test 4: Stress test nested objects ---" << std::endl;
    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair(); // P1

    vm.pushInt(3);
    vm.pushPair(); // P2 (P1,3)

    vm.gc(); // Should collect nothing

    vm.pop();
    vm.gc(); // Should collect everything
}

void test5() {
    std::cout << "\n--- Test 5: Cyclic structures ---" << std::endl;
    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair();

    Object *pair = vm.pop();
    vm.push(pair);

    vm.gc(); // should not crash

    vm.pop();
    vm.gc(); // should collect everything
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    
    std::cout << "\nAll tests completed." << std::endl;
    return 0;
}
