#include "ClassMemoryPool.h"
#include <iostream>

void* MemoryAllocator::allocate(size_t size)
{
    obj* tmpPtr;

    if(m_freePtr == nullptr)
    {
        size_t realSize = m_onceAllocCount * size;
        m_freePtr = (obj*)malloc(realSize);
        tmpPtr = m_freePtr;

        for(size_t i = 0; i < m_onceAllocCount - 1; ++i)
        {
            tmpPtr->next = (obj*)(((char*)tmpPtr) + size);
            tmpPtr = tmpPtr->next;
        }

        tmpPtr->next = nullptr;
    }

    tmpPtr = m_freePtr;
    m_freePtr = m_freePtr->next;
    return tmpPtr;
}

void MemoryAllocator::deallocate(void* p)
{
    ((obj*)p)->next = m_freePtr;
    m_freePtr = (obj*)p;
}