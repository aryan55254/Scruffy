#include "VM.hpp"
#include <iostream>

int main()
{
    std::cout << "stress test nested objects" << std::endl;
    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair(); // P1

    vm.pushInt(3);
    vm.pushPair(); // P2 (P1,3)

    vm.gc(); // Should collect nothing

    vm.pop();
    vm.gc(); // Should collect everything

    return 0;
}
