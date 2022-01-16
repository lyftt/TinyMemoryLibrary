#include "ClassMemoryPool.h"
#include <ctime>
#include <iostream>

int main()
{
    clock_t start = clock();
    for(int i = 0; i < 5000000; ++i)
    {
        A* pa = new A;
    }

    clock_t end = clock();

    std::cout<<"new count:"<<A::m_newCount<<std::endl;
    std::cout<<"new malloc:"<<A::m_mallocCount<<std::endl;
    std::cout<<"time(ms) used:"<<(end - start)<<std::endl;

    return 0;
}