#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <class T, std::size_t N>
class myArray
{

/*----------------- Member type -------------------------*/
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
    //using reverse_iterator = std::reverse_iterator<T*>;
    //using const_reverse_iterator = std::reverse_iterator<const T*>;

private:
/*---------- Fixed size array of elements of type T -----*/
    //T m_elements[N];
    std::size_t sizes;
    T* data_ptr;


public:
/*-------------- Constructor & Destructor ---------------*/
/*****************************
 * 
 * bref: 默认构造函数.
 * 对于顺序容器中的array，元素按默认方式初始化
 * 默认初始化由变量的类型和位置决定， 内置类型的变量如果未被显示初始化，其值由定
 * 义的位置决定，函数体之外被初始化为0，函数内部的局部变量不会被初始化；类类型和
 * 自定义类型默认初始化由其默认构造数决定.
 *
 ****************************/
    //myArray<T, N>() = default; //使用编译器自动生成的构造函数 
    myArray<T, N>()
    :sizes(0)
    ,data_ptr(nullptr)
    {
        std::cout << "myArray() called" << std::endl;
        sizes = N;
        data_ptr = new T[sizes];
    } 

/*****************************
 * 
 * bref: 构造函数, 参数为列表初始化, 任何使用列表初始化的情况: {} 或者 ={}均调用此函数
 * 标准的 std::array 是一个聚合体(aggregate)
 * 所谓聚合体, 没有用户自定义的构造函数, 没有private和projected成员, 没有基类 等,
 * 不支持 array<int, 3>({1,2,3})这样的构造方法
 *
 ****************************/
    myArray<T, N>(std::initializer_list<T> list)
    :sizes(N)
    ,data_ptr(new T[N])
    {
        std::cout << "myArray(std::initializer) called" << std::endl;

        size_type i = 0;

        for (auto it = list.begin(); it != list.end() && i < N; ++it)
        {
            //m_elements[i] = *it;
            data_ptr[i] = *it;
            i++;
        }
    } 

/*****************************
 * 
 * bref: 拷贝构造函数, 如果没有定义，则编译器会在调用的时候生成一个 
 * 语义: 拷贝构造函数是复制给定的对象资源,如将实参的内容复制给临时对象,一般会有分配新内存的操作来构建临时对象,
 * 
 * 注意: 因为参数是 const 对象, 只能调用对象的const成员函数, 否则出现“discards qualifiers”
 *
 ****************************/
    myArray<T, N>(const myArray<T, N> &value)
    :sizes(value.sizes)
    ,data_ptr(new T[value.sizes])
    {
        std::cout << "myArray copy contructor called" << std::endl;

        for (auto i = 0; i < value.sizes; ++i)
        {
            data_ptr[i] = value.data_ptr[i];
        }

        //std::copy(value.cbegin(), value.cend(), this->m_elements);
    } 

/*****************************
 * 
 * bref: 拷贝赋值运算符,即重载 = 操作符. 如果没有定义，则编译器会在调用的时候生成一个 
 * 语义: 拷贝赋值时, 被赋值对象已存在, 需先释放当前对象的资源, 再分配新内存存储资源

 * 注意: 自赋值安全和异常安全，特别是带有指针成员的类, 适当的释放资源
 * 参考: effective c++ 3rd, item 11
 * http://www.aichengxu.com/view/1371091
 *
 * 返回类型是 myArray&
 *
 ****************************/
    myArray<T, N>& operator=(const myArray<T, N> &value)
    {
        std::cout << "myArray copy assinment opeartor called" << std::endl;

        if (this == &value) return *this;

        delete[] data_ptr;
        sizes = value.sizes;
        data_ptr = new T[value.sizes];

        for (auto i = 0; i < value.sizes; ++i)
        {
            data_ptr[i] = value.data_ptr[i];
        }
        //std::copy(value.cbegin(), value.cend(), this->m_elements);
        
        return *this;
    } 


/*****************************
 * 
 * bref: 移动构造函数, 如果没有定义，则编译器会在调用的时候生成一个 
 * 语义: 移动构造函数是窃取给定的对象资源而不是拷贝资源,移动后源对象不再指向被移动的资源,这些资源的所有权已经归属新创建的对象,移动构造函数不分配任何新内存,接管给定对象中的内存,并确保移动完成后源对象处于可销毁的状态.
 *
 * 参考: https://msdn.microsoft.com/zh-cn/library/dd293665.aspx
 * 注意: 参数没有 const, noexcept 是告诉编译器不会抛出任何异常. 
 *
 ****************************/
    myArray<T, N>(myArray<T, N> &&value) noexcept
    :sizes(0)
    ,data_ptr(nullptr)
    {
        std::cout << "myArray move contructor called" << std::endl;

        sizes = value.sizes;
        data_ptr = value.data_ptr;      // 接管资源

        value.sizes = 0;
        value.data_ptr = nullptr;
        std::cout << "myArray move contructor end" << std::endl;

        //std::copy(value.cbegin(), value.cend(), this->m_elements);
    } 


/*****************************
 * 
 * bref: 移动赋值运算符
 * 语义: 移动赋值时与拷贝赋值类似, 被赋值对象已存在, 需先释放当前对象的资源, 但是不用分配新内存而是接管资源
 *
 * 注意: 自赋值安全和异常安全
 * 参考: https://msdn.microsoft.com/zh-cn/library/dd293665.aspx
 *
 * 返回类型是 myArray& 
 *
 ****************************/
    myArray<T, N>& operator=(myArray<T, N> &&value) noexcept
    {
        std::cout << "myArray move assinment opeartor called" << std::endl;

        if (this == &value) return *this;

        delete[] data_ptr;
        sizes = value.sizes;
        data_ptr = value.data_ptr;      // 接管资源

        value.sizes = 0;
        value.data_ptr = nullptr;

        //std::copy(value.cbegin(), value.cend(), this->m_elements);

        return *this;
    } 


/*****************************
 * 
 * bref: 析构函数， 可以使用编器器生成， 这里只是为了看打印.
 *       如果一个类需要自定义析构函数，则也需要自定义拷贝构造函数和拷贝赋值运算符
 *
 ****************************/
    //~myArray<T, N>() = default; //使用编译器自动生成的构造函数 
    ~myArray<T, N>()
    {
        std::cout << "~myArray() called" << std::endl;

        delete[] data_ptr;
    }
     

/*-------------- Element access -------------------------*/
/*****************************
 * 
 * bref: [] 操作符重载, 返回指定位置的元素, 不带边界检查
 * 参考 http://en.cppreference.com/w/cpp/container/array/operator_at
 *
 ****************************/
    const T& operator[](size_type index) const
    { 
        return data_ptr[index];
        //return m_elements[index];
    }


/*****************************
 * 
 * bref: at() 访问指定的成员
 * 注意: 带有边界检测
 * 参考: http://en.cppreference.com/w/cpp/container/array/at
 *
 ****************************/
    const T& at(size_type index) const
    { 
        if (index >= sizes)
          throw std::out_of_range("index out of range");

        return data_ptr[index];
        //return m_elements[index];
    }


/*****************************
 * 
 * bref: front() 返回第一个元素
 * 注意: 对一个空array(N=0, array.begin() = array.end() )调用front()的行为是未定义的
 * 参考: http://en.cppreference.com/w/cpp/container/array/front
 *
 ****************************/
    const T& front(void) const
    { 
        return data_ptr[0];
        //return m_elements[0];
    }

/*****************************
 * 
 * bref: back() 返回最后一个元素
 * 注意: 对一个空array(N=0, array.begin() = array.end() )调用back()的行为是未定义的
 * 参考: http://en.cppreference.com/w/cpp/container/array/back
 *
 ****************************/
     const T& back(void) const
    { 
        return data_ptr[sizes-1];
        //return m_elements[N-1];
    }


/*****************************
 * 
 * bref: 返回 array首地址
 * 注意: 对一个空array(N=0, array.begin() = array.end() )调用data()是有效的，
 * 但是不能解引用.
 * 参考: http://en.cppreference.com/w/cpp/container/array/data
 *
 ****************************/
     T* data(void)
    { 
        return &data_ptr[0];
        //return &m_elements[0];
    }


/*----------------- Iterators ---------------------------*/
/*****************************
 * 
 * bref: 
 * 参考 http://en.cppreference.com/w/cpp/container/array/begin 
 * 返回类型是 T* 
 *
 **************/
iterator begin()
{
    return &data_ptr[0];
    //return &m_elements[0];
}

iterator end()
{
    return &data_ptr[sizes];
    //return &m_elements[N];
}

const_iterator cbegin() const
{
    return &data_ptr[0];
    //return &m_elements[0];
}

const_iterator cend() const
{
    return &data_ptr[sizes];
    //return &m_elements[N];
}


/*----------------- Capacity ----------------------------*/
/*****************************
 * 
 * bref: 
 * 参考 
 * 返回类型是 T* 
 *
 **************/
bool empty()
{
    if (size() == 0)
      return true;
    else
      return false;

}

size_type size()
{
    return sizes;
    //return N;
}


};


#endif
