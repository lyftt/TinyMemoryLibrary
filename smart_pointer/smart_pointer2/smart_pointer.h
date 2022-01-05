/*
*只支持移动
*
*/
#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <algorithm>

namespace tiny
{
    template <typename T>
    class smart_unique_pointer
    {
    public:
        //构造函数，必须显示初始化
        explicit smart_unique_pointer(T* p = nullptr):m_ptr(p)
        {

        }

        //析构函数
        ~smart_unique_pointer()
        {
            delete m_ptr;
        }

        //移动构造函数, 供了移动构造函数而没有手动提供拷贝构造函数，那后者自动被禁用(delete)
        smart_unique_pointer(smart_unique_pointer&& other)
        {
            m_ptr = other.release();
        }

        //直接构造临时对象，构造的方式取决去传的是左值还是右值，但是只提供了移动构造函数，自动实现了copy and swap
        //由于只提供了移动构造，所以只支持移动赋值
        smart_unique_pointer& operator=(smart_unique_pointer other)
        {
            other.swap(*this);
            return *this;
        }
    
    private:
        T* release()
        {
            T* p = m_ptr;
            m_ptr = nullptr;
            return p;
        }

        void swap(smart_unique_pointer& other)
        {
            using std::swap;
            std::swap(m_ptr, other.m_ptr);
        }
    
    private:
        T* m_ptr;
    };
}

#endif