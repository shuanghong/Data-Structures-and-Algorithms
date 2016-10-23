#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include "Alloc.h"

/*****************************
 * 
 * brief: 空间配置器, 以对象个数为单位分配
 * 一般 C++ 内存分配和释放如下
 * class Foo {...};
 * Foo *p = new Foo;
 * delete p;
 * 其中的 new操作包含两个步骤
 * 1). 调用 ::operator new 分配内存
 * 2). 调用 Foo::Foo() 构造对象内容
 * 同理，delete 样样包含两个步骤，
 * 1). 调用 Foo::~Foo() 析构对象
 * 2). 调用 ::operator delete 释放内存
 *
 * 这里参考 sgi STL实现将这两个步骤区分开来，内存分配由 allocate()实现，释放由 deallocate()实现，
 * 对象构造由 construct()实现，对象析构由 destroy()实现
 *
 ****************************/

template <class T>
class myAllocator
{

public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    using iterator = T*;
    using const_iterator = const T*;

public:
    static T *allocate();
    static T *allocate(size_type n);
    static void deallocate(T *ptr);
    static void deallocate(T *ptr, size_type n);

    static void construct(T *ptr);
    static void construct(T *ptr, const T& value);
    static void destroy(T *ptr);
    static void destroy(T *first, T *last);

};


template<class T>
T *myAllocator<T>::allocate()
{
    return static_cast<T *>(myAlloc::allocate(sizeof(T)));
}

template<class T>
T *myAllocator<T>::allocate(size_type n)
{
    if (n == 0) return nullptr;
    return static_cast<T *>(myAlloc::allocate(sizeof(T) * n));
}

template<class T>
void myAllocator<T>::deallocate(T *ptr)
{
    myAlloc::deallocate(static_cast<void *>(ptr), sizeof(T));
}

template<class T>
void myAllocator<T>::deallocate(T *ptr, size_type n)
{
    if (n == 0) return;
    myAlloc::deallocate(static_cast<void *>(ptr), sizeof(T)* n);
}

template<class T>
void myAllocator<T>::construct(T *ptr)
{
    new(ptr)T();
}

template<class T>
void myAllocator<T>::construct(T *ptr, const T& value)
{
    new(ptr)T(value);
}

template<class T>
void myAllocator<T>::destroy(T *ptr)
{
    ptr->~T();
}

template<class T>
void myAllocator<T>::destroy(T *first, T *last)
{
    for (; first != last; ++first)
    {
        first->~T();
    }
}

#endif
