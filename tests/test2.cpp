#include "VM.hpp"
#include <iostream>

int main()
{
    std::cout << "testing for nested objects" << std::endl;

    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair(); // pair(1,2)

    vm.gc(); // Nothing collected

    vm.pop(); // Remove pair from stack

    vm.gc(); // Should collect pair + both ints

    return 0;
}
