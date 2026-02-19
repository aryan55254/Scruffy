#include "VM.hpp"
#include <iostream>

int main()
{
    std::cout << "testing basic allocation and collection" << std::endl;
    VM vm;

    vm.pushInt(10);
    vm.pushInt(20);

    vm.gc(); // Nothing should be collected (2 remaining)

    vm.pop();
    vm.pop();

    vm.gc(); // Both should be collected (0 remaining)

    return 0;
}
