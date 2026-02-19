#include "VM.hpp"
#include <iostream>

int main()
{

    std::cout << "stress test , trigger automatic gc" << std::endl;
    VM vm;

    for (int i = 0; i < 1000; i++)
    {
        vm.pushInt(i);
        vm.pop(); // immediately remove reference
    }

    vm.gc(); // Should collect all

    return 0;
}
