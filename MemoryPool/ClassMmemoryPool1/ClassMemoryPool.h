#ifndef __CLASS_MEMORY_POOL_H__
#define __CLASS_MEMORY_POOL_H__

#include <cstddef>


/*
* 针对某个类进行分配的内存池
*
*/
class A
{
public:
    //类自定义operator new 和  operator delete
    static void* operator new(size_t size);
    static void  operator delete(void*); 
    static size_t m_newCount;           //new的次数
    static size_t m_mallocCount;        //内存池malloc的次数，内存池的目的就是减少malloc的次数，特别是在分配小内存的时候

    //构造函数
    A();
    ~A();

private:
    A*   m_next;
    int  m_a;
    char m_b;

    static A*     m_freePtr;         //内存池中第一个可用的类A对象地址
    static size_t m_onceAllocCount;  //内存池调用一次malloc时分配多少个类A对象大小的内存
};

#endif