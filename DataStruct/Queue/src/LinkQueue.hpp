#ifndef _LINK_QUEUE_HPP_
#define _LINK_QUEUE_HPP_

#include "Queue.hpp"

namespace queue
{


struct Node
{
    Node(DataType value): data(value), next(nullptr){}
    ~Node() = default;

    DataType data;
    Node *next;
};

class LinkQueue: public Queue
{

public:
    LinkQueue();
    
    LinkQueue(const LinkQueue&) = delete;
    LinkQueue& operator=(const LinkQueue&) = delete;
    LinkQueue(LinkQueue&&) = delete;
    LinkQueue& operator=(LinkQueue&&) = delete;

    ~LinkQueue();

    virtual void push(DataType data) override; 
    virtual void pop() override; 

    virtual DataType front() const override; 
    virtual DataType back() const override; 

    virtual Listlength size() override; 
    virtual bool isEmpty() override; 

    void printfQueue() const;
private:
    Listlength m_length;
    Node *m_head;
    Node *m_rear;

};


}

#endif
