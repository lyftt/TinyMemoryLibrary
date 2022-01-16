#ifndef __CLASS_MEMORY_POOL_H__
#define __CLASS_MEMORY_POOL_H__

#include <cstddef>
#include <iostream>

/*
* 内存分配器
*
*/
class MemoryAllocator
{
public:
    void* allocate(size_t size);
    void  deallocate(void* p);

private:
    struct obj
    {
        obj* next;
    };

    obj*     m_freePtr = nullptr;         //内存池中第一个可用的类A对象地址
    size_t   m_onceAllocCount = 5;        //内存池调用一次malloc时分配多少个类A对象大小的内存
};

/*
* 使用内存分配器的某个类
*
*/
template<typename Alloc=MemoryAllocator>
class A
{
public:
    //类自定义operator new 和  operator delete
    static void* operator new(size_t size);
    static void  operator delete(void*); 
    static Alloc inerAlloc;

    //构造函数
    A()
    {
        std::cout<<"con:"<<this<<std::endl;
    }

    ~A()
    {
        std::cout<<"decon:"<<this<<std::endl;
    }

private:
    int  m_a;
    char m_b;
};

template<typename Alloc>
Alloc A<Alloc>::inerAlloc;

template<typename Alloc>
void* A<Alloc>::operator new(size_t size)
{
    return inerAlloc.allocate(size);
}

template<typename Alloc>
void A<Alloc>::operator delete(void* p)
{
    return inerAlloc.deallocate(p);
}

#endif