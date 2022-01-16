#include "ClassMemoryPool.h"
#include <iostream>

size_t A::m_mallocCount = 0;
size_t A::m_newCount = 0;
A* A::m_freePtr = nullptr;
size_t A::m_onceAllocCount = 100;

//每次都先从内存池中获取，如果内存池中满了则继续分配
void* A::operator new(size_t size)
{
    A* tmpPtr = nullptr;

    if(m_freePtr == nullptr)
    {
        size_t realSize = m_onceAllocCount * size;
        m_freePtr = (A*)malloc(realSize);

        for(tmpPtr = m_freePtr; tmpPtr != &m_freePtr[m_onceAllocCount - 1]; ++tmpPtr)
        {
            tmpPtr->m_next = (tmpPtr + 1);
        }

        tmpPtr->m_next = nullptr;
        ++m_mallocCount;
    }

    tmpPtr = m_freePtr;
    m_freePtr = tmpPtr->m_next;
    ++m_newCount;
    return tmpPtr;
}

//并不真正释放内存，而是放回内存池中
//会导致内存池不断变大
void A::operator delete(void * p)
{
    (static_cast<A*>(p))->m_next = m_freePtr;
    m_freePtr = static_cast<A*>(p);
}

A::A()
{
    //std::cout<<"A con"<<std::endl;
}

A::~A()
{
    //std::cout<<"A decon"<<std::endl;
}