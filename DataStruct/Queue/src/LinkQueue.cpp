#include <iostream>
#include "LinkQueue.hpp"


namespace queue
{

LinkQueue::LinkQueue()
:m_head(nullptr), m_rear(nullptr), m_length(0u)
{
    m_head = new Node(0u);
    m_rear = m_head;

    m_length = 0u;

    std::cout << __func__ << "() "<< "head address: " << m_head << std::endl;
}


LinkQueue::~LinkQueue()
{
    while (m_head->next != nullptr)
    {
        Node *removed_node = m_head->next;
        m_head->next = m_head->next->next;

        delete removed_node;
    }
}

void LinkQueue::push(DataType data)
{
    Node *newnode = new Node(data);

    m_rear->next = newnode;
    m_rear = newnode;

    m_length += 1u;
}


void LinkQueue::pop()
{
    if (m_head->next == nullptr)
    {
        std::cout << __func__ << "() "<< "Error: queue is Null" << std::endl;
        return;
    }

    Node *removed_node = m_head->next;
    m_head->next = m_head->next->next;

    if (removed_node->next == nullptr)
        m_rear = m_head;

    delete removed_node;

    m_length -= 1u;
}


DataType LinkQueue::front() const
{
    if (m_head->next == nullptr)
    {
        std::cout << __func__ << "() "<< "Error: queue is Null" << std::endl;
        return -1;
    }

    return m_head->next->data;
}

DataType LinkQueue::back() const
{
    if (m_head->next == nullptr)
    {
        std::cout << __func__ << "() "<< "Error: queue is Null" << std::endl;
        return -1;
    }

    return m_rear->data;

}

Listlength LinkQueue::size()
{
    return m_length;

}

bool LinkQueue::isEmpty()
{
    if ((m_head->next == nullptr) || (m_length == 0))
        return true;

    return false;
}

void LinkQueue::printfQueue() const
{
    if (m_head->next == nullptr)
    {
        std::cout << __func__ << "() "<< "Error: queue is Null" << std::endl;
        return;
    }

    Node *printnode = m_head->next;

    while (printnode != nullptr)
    {
        std::cout << __func__ << "() "<< "Node value:" << printnode->data << "    Next node address: " << printnode->next << std::endl;

        printnode = printnode->next;
    }

}

}
