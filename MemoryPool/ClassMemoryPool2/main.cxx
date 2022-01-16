#include "ClassMemoryPool.h"
#include <ctime>
#include <iostream>

int main()
{
    clock_t start = clock();
    for(int i = 0; i < 20; ++i)
    {
        A<MemoryAllocator>* pa = new A<MemoryAllocator>;
    }

    clock_t end = clock();

    return 0;
}