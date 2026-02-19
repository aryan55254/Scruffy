#include "VM.hpp"
#include <iostream>

int main()
{
    std::cout << "testing in cyclic structures" << std::endl;
    VM vm;

    vm.pushInt(1);
    vm.pushInt(2);
    vm.pushPair();

    Object *pair = vm.pop();
    vm.push(pair);

    vm.gc(); // should not crash

    vm.pop();
    vm.gc(); // should collect everything

    return 0;
}
