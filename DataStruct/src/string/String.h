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
    char *end_of_storage_;

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
    ,end_of_storage_(nullptr)
    {
        std::cout << "myString() called" << std::endl;
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
    ,end_of_storage_(nullptr)
    {
        std::cout << "myString(const char *s) called" << std::endl;

        start_ = dataAllocator::allocate(strlen(s));
        
        finish_ = std::uninitialized_copy(s, s+strlen(s), start_);
        end_of_storage_ = finish_;
    }

/*****************************
 *
 * brief: copy constructor, 
 *
 ****************************/
    myString(const std::string& str)
    :start_(nullptr)
    ,finish_(nullptr)
    ,end_of_storage_(nullptr)
    {
        std::cout << "myString() called" << std::endl;
    }
};








#endif
