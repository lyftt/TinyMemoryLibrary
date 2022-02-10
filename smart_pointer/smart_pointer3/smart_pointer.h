/*
*只支持移动
*
*/
#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

#include <algorithm>

namespace tiny
{
    //控制块
    class shared_count 
    {
    public:
        shared_count() noexcept: m_count(1) {}

        void add() noexcept
        {
            ++m_count;
        }

        long reduce() noexcept
        {
            return --m_count;
        }
        
        long count() const noexcept
        {
            return m_count;
        }

    private:
        long m_count;
    };

    template <typename T>
    class smart_shared_pointer
    {
    public:
        template <typename U>
        friend class smart_shared_pointer;

        //必须显示构造
        explicit smart_shared_pointer(T* ptr = nullptr) : m_ptr(ptr)
        {
            if (ptr) 
            {
                m_shared_count = new shared_count();
            }
        }

        //析构函数
        ~smart_shared_pointer()
        {
            if (m_ptr && !m_shared_count->reduce()) 
            {
                delete m_ptr;
                delete m_shared_count;
            }
        }

        //拷贝构造函数
        smart_shared_pointer(const smart_shared_pointer& other)
        {
            m_ptr = other.m_ptr;
            if (m_ptr) 
            {
                other.m_shared_count->add();
                m_shared_count = other.m_shared_count;
            }
        }

        //用于和子类类型进行转换
        //构造函数（拷贝）
        template <typename U>
        smart_shared_pointer(const smart_shared_pointer<U>& other) noexcept
        {
            m_ptr = other.m_ptr;
            if (m_ptr) 
            {
                other.m_shared_count->add();
                m_shared_count = other.m_shared_count;
            }
        }

        //用于和子类类型进行转换
        //构造函数（移动）
        template <typename U>
        smart_shared_pointer(smart_shared_pointer<U>&& other) noexcept
        {
            m_ptr = other.m_ptr;
            if (m_ptr) 
            {
                m_shared_count = other.m_shared_count;
                other.m_ptr = nullptr;
            }
        }

        //用于智能指针的类型转换
        template <typename U>
        smart_shared_pointer(const smart_shared_pointer<U>& other, T* ptr) noexcept
        {
            m_ptr = ptr;
            if (m_ptr) {
                other.m_shared_count->add();
                m_shared_count = other.m_shared_count;
            }
        }

        //赋值运算符，是移动韩式拷贝取决于rhs的构造方式
        smart_shared_pointer& operator=(smart_shared_pointer rhs) noexcept
        {
            rhs.swap(*this);
            return *this;
        }

        //获取指针
        T* get() const noexcept
        {
            return m_ptr;
        }

        //获取引用计数
        long use_count() const noexcept
        {
            if (m_ptr) 
            {
                return m_shared_count->count();
            }

            return 0;
        }

        void swap(smart_shared_pointer& rhs) noexcept
        {
            using std::swap;
            swap(m_ptr, rhs.m_ptr);
            swap(m_shared_count, rhs.m_shared_count);
        }

        T& operator*() const noexcept
        {
            return *m_ptr;
        }

        T* operator->() const noexcept
        {
            return m_ptr;
        }

        operator bool() const noexcept
        {
            return m_ptr;
        }

    private:
        T* m_ptr;
        shared_count* m_shared_count;
    };

    template <typename T>
    void swap(smart_shared_pointer<T>& lhs, smart_shared_pointer<T>& rhs) noexcept
    {
        lhs.swap(rhs);
    }

    template <typename T, typename U>
    smart_shared_pointer<T> static_pointer_cast(const smart_shared_pointer<U>& other) noexcept
    {
        T* ptr = static_cast<T*>(other.get());
        return smart_shared_pointer<T>(other, ptr);
    }

    template <typename T, typename U>
    smart_shared_pointer<T> reinterpret_pointer_cast(const smart_shared_pointer<U>& other) noexcept
    {
        T* ptr = reinterpret_cast<T*>(other.get());
        return smart_shared_pointer<T>(other, ptr);
    }

    template <typename T, typename U>
    smart_shared_pointer<T> const_pointer_cast(const smart_shared_pointer<U>& other) noexcept
    {
        T* ptr = const_cast<T*>(other.get());
        return smart_shared_pointer<T>(other, ptr);
    }

    template <typename T, typename U>
    smart_shared_pointer<T> dynamic_pointer_cast(const smart_shared_pointer<U>& other) noexcept
    {
        T* ptr = dynamic_cast<T*>(other.get());
        return smart_shared_pointer<T>(other, ptr);
    }
}

#endif