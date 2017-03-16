#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_

#include <cstdint>

namespace queue
{

using DataType = uint32_t;
using Listlength = uint32_t;

class Queue
{

public: 
    Queue() = default;
    ~Queue() = default;

    virtual void push(DataType data) = 0; 
    virtual void pop() = 0; 

    virtual DataType front() const = 0 ; 
    virtual DataType back() const = 0 ; 

    virtual Listlength size() = 0; 
    virtual bool isEmpty() = 0; 

};


}



#endif
