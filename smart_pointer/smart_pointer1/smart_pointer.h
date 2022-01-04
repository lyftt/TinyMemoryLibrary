#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <algorithm>

namespace tiny
{

    template<typename T>
    class smart_unique_ptr
    {
    public:
        explicit smart_unique_ptr(T* p = nullptr):m_ptr(p)
        {
        }

        //拷贝时转移所有权
        smart_unique_ptr(smart_unique_ptr& other)
        {
            m_ptr = other.release();
        }

        //析构时释放资源
        ~smart_unique_ptr()
        {
            delete m_ptr;
        }

        T* get() const { return m_ptr; }
        T& operator*() { return *m_ptr; }
        T* operator->() { return m_ptr; }
        operator bool() { return m_ptr; }

        //赋值运算符
        smart_unique_ptr& operator=(smart_unique_ptr& other)
        {
            smart_unique_ptr(other).swap(*this);  //copy and swap 构造临时对象提供异常安全的保证
            return *this;
        }

    private:
        T* release()
        {
            T* ptr = m_ptr;
            m_ptr = nullptr;
            return ptr;
        }

        void swap(smart_unique_ptr& other)
        {
            using std::swap;
            std::swap(m_ptr, other.m_ptr);
        }

    private:
        T* m_ptr;
    };
}

#endif