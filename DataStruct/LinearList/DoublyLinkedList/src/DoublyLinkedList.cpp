
#include <iostream>
#include "DoublyLinkedList.hpp"

namespace doublylinkedlist
{

DoublyLinkedList::DoublyLinkedList()
:m_length(0), m_head(nullptr), m_tail(nullptr)
{
    m_head = new Node();
//    m_head->m_prior = nullptr;
//    m_head->m_next = nullptr;
    m_tail = m_head;
}

DoublyLinkedList::DoublyLinkedList(Listlength length)
:m_length(length), m_head(nullptr), m_tail(nullptr)
{
    m_head = new Node();
//    m_head->m_prior = nullptr;
//    m_head->m_next = nullptr;
    m_tail = m_head;

    for (Listlength i = 0u; i < m_length; i++)
    {
        Node newnode = new Node();

        std::cout << "please enter the No." << i+1 << "Node's data...";
        std::cin >> newnode->m_data;

        newnode->m_prior = m_tail;
        newnode->m_next = nullptr;

        m_tail->m_next = newnode;
        m_tail = newnode;
    }
}


DoublyLinkedList::~DoublyLinkedList()
{
    delete m_head;
    delete m_tail;

    m_length = 0u;
}

Node* DoublyLinkedList::createNode(DataType value)
{
    Node *newnode = new(std::nothrow) Node();

    if (newnode == nullptr)
    {
        std::cout << __func__ << "() " << "Error: memory allocation failed for new Node" << std::endl;
        assert(0);
    }


    newnode->m_data = value;
//  newnode->m_prior = nullptr;
//  newnode->m_next = nullptr;

    return newnode;
}

Node* DoublyLinkedList::getNodeAtPosition(const Listlength position) const
{
    if (isListEmpty() == true)
    {
        std::cout << __func__ << "() " << "Error: list is null" << std::endl;
        return nullptr;
    }

    if (position < 0 || position > m_length + 1)
    {
        std::cout << __func__  <<"() " << "Error: position out of list range" << std::endl;

        return nullptr;
    }
        
    if (position == 0)
    {
        std::cout << __func__  <<"() " << "Return head" << std::endl;

        return m_head;
    }

    if (position == m_length)
    {
        std::cout << __func__  <<"() " << "Return tail" << std::endl;

        return m_tail;
    }

    Node *prenode = m_head;

    Listlength count = 1u;
    while (count < position)
    {
        prenode = prenode->m_next;
        count += 1;
    } 

    std::cout << __func__  <<"() done." 
              << " position is " << position
              << " node address is " << prenode->m_next << std::endl;
    return prenode->m_next;
}


Node* DoublyLinkedList::getNodeValue(const DataType value) const
{
    if (isListEmpty() == true)
    {
        std::cout << __func__ << "() "<< "Error: list is null" << std::endl;
        return nullptr;
    }

    Listlength count = 1u;

    Node *firstnode = m_head->m_next;

    while (count < m_length)
    {
        if (firstnode->m_data == value)
          break;

        firstnode = firstnode->m_next;
        count += 1;
    }

    if (firstnode->m_next == nullptr)
    {
        std::cout << __func__ << "() " << "Error: cannot get node for value: " << value << std::endl;

        return nullptr;
    }

    return firstnode;
}


}

