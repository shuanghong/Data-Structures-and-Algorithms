#ifndef _STRING_H_
#define __STRING_H_

#include "../allocator/Allocator.h"
#include <cstring>
#include <memory>

/*****************************
 * copy from SGI string (basic_string)
 *
 * Class invariants:
 (1) [start, finish) is a valid range.
 (2) Each iterator in [start, finish) points to a valid object of type value_type.
 (3) *finish is a valid object of type value_type; in particular, it is value_type().
 (4) [finish + 1, end_of_storage) is a valid range.
 (5) Each iterator in [finish + 1, end_of_storage) points to unininitialized memory.

 Note one important consequence: a string of length n must manage
 a block of memory whose size is at least n + 1(NULL).  
 ****************************/
class myString
{

/*----------------- Member type -------------------------*/
public:
    using value_type = char;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using reference = char&;
    using const_reference = const char&;
    using pointer = char*;
    using const_pointer = const char*;
    using iterator = char*;
    using const_iterator = const char*;

    static const size_type npos = -1;

/*----------------- Allocator ---------------------------*/

private:
    using dataAllocator = myAllocator<char>;

/*----------------- Member data -------------------------*/
private:
    char *start_;
    char *finish_;
    char *endOfStorage_;

/*           ________________________________________
            |               |                       |
            |   Content     |                       |
            |_______________|_______________________|
            
           /|\             /|\                     /|\
start ______|    finish ____|  endofstorage ________|

size = finish - start
capacity = endofstorage - start

refer to  http://blog.leanote.com/post/804305986@qq.com/basic_string%E6%BA%90%E7%A0%81

*/

public:
/*-------------- Constructor & Destructor ---------------*/

/*****************************
 *
 * brief: default constructor
 * Constructs empty string (zero size and unspecified capacity).
 *
 ****************************/
    myString()
    :start_(nullptr)
    ,finish_(nullptr)
    ,endOfStorage_(nullptr)
    {
        std::cout << "Default constructor myString() called" << std::endl;
    }

/*****************************
 *
 * brief: 
 * Constructs the string with the contents initialized with a copy of the null-terminated character string pointed to by s
 *
 ****************************/
    myString(const char *s)
    :start_(nullptr)
    ,finish_(nullptr)
    ,endOfStorage_(nullptr)
    {
        std::cout << "Constructor myString(const char *s) called" << std::endl;

        start_ = dataAllocator::allocate(strlen(s));
        
        finish_ = std::uninitialized_copy(s, s+strlen(s), start_);
        endOfStorage_= finish_;
    }

/*****************************
 *
 * brief: Copy constructor
 * Constructs the string with the copy of the contents of other
 *
 ****************************/
    myString(const myString& str)
    :start_(nullptr)
    ,finish_(nullptr)
    ,endOfStorage_(nullptr)
    {
        std::cout << "Copy constructor myString(const string&) called" << std::endl;

        start_ = dataAllocator::allocate(str.finish_ - str.start_);
        finish_ = std::uninitialized_copy(str.start_, str.finish_, start_);
        endOfStorage_= finish_;
    }


/*****************************
 *
 * brief: Move constructor
 * Constructs the string with the contents of other using move semantics. other is left in valid, but unspecified state
 *
 ****************************/
    myString(myString&& str) noexcept
    :start_(nullptr)
    ,finish_(nullptr)
    ,endOfStorage_(nullptr)
    {
        std::cout << "Move constructor myString(string&&) called" << std::endl;

		start_ = str.start_;
		finish_ = str.finish_;
		endOfStorage_ = str.endOfStorage_;
		str.start_ = str.finish_ = str.endOfStorage_ = nullptr;
    }


/*****************************
 *
 * brief: Constructs the string with the contents of the initializer list init
 *
 ****************************/
    myString(std::initializer_list<char> init)
    :start_(nullptr)
    ,finish_(nullptr)
    ,endOfStorage_(nullptr)
    {
        std::cout << "Constructor myString(std::initializer_list<char>) called" << std::endl;

        start_ = dataAllocator::allocate(init.size());
        finish_ = std::uninitialized_copy(init.begin(), init.end(), start_);
        endOfStorage_= finish_;
    }

/*****************************
 *
 * brief: Destructor
 *
 ****************************/
    ~myString()
    {
        std::cout << "Destructor ~myString() called" << std::endl;

        dataAllocator::destroy(start_, finish_);
        dataAllocator::deallocate(start_, endOfStorage_-start_);
    }


/*-------------- Operator= ---------------*/

/*****************************
 *
 * brief: Copy assignment operator
 * Note: 
 *      C++ Primer 5th cn P454~P455
 *      Effective C++ 3th Item 11
 *
 ****************************/
    myString& operator=(const myString &str)
    {
        std::cout << "Copy assignment operator myString(const string&) called" << std::endl;

        auto newStart = dataAllocator::allocate(str.finish_ - str.start_);
        auto newFinish = std::uninitialized_copy(str.start_, str.finish_, newStart);
        auto newEndOfStorage = newFinish;

        dataAllocator::destroy(start_, finish_);
        dataAllocator::deallocate(start_, endOfStorage_-start_);

        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = newEndOfStorage;

        return *this;
    }


/*****************************
 *
 * brief: Move assignment operator
 * Note: 
 *      C++ Primer 5th cn P474
 *
 ****************************/
    myString& operator=(myString&& str) noexcept
    {
        std::cout << "Move assignment operator myString(string&&) called" << std::endl;

        if (this != &str)
        {
            dataAllocator::destroy(start_, finish_);
            dataAllocator::deallocate(start_, endOfStorage_-start_);

            start_ = str.start_;
            finish_ = str.finish_;
            endOfStorage_ = str.endOfStorage_;
            str.start_ = str.finish_ = str.endOfStorage_ = nullptr;
        }

        return *this;
    }
};








#endif
