#include <iostream>
#include <cstddef>
#include <cassert>

#include "SinglyLinkedList.hpp"

namespace singlylinkedlist
{

SinglyLinkedList::SinglyLinkedList()
:m_length(0u), m_head(nullptr)
{
    m_head = new Node();
}


SinglyLinkedList::~SinglyLinkedList()
{
    std::cout << std::endl << __func__  << "() " << std::endl;
    clearList();

    delete m_head;
}


Node* SinglyLinkedList::createNode(const DataType value)
{
    Node *newnode = new(std::nothrow) Node(value);

    if (newnode == nullptr)
    {
        std::cout << __func__ << "() " << "Error: memory allocation failed for new Node" << std::endl;
        assert(0);
    }

    return newnode;
}

Node* SinglyLinkedList::getNodeAtPosition(const Listlength position) const
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

Node* SinglyLinkedList::getNodeValue(const DataType value) const
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

bool SinglyLinkedList::insertNodeAtPosition(const DataType value, const Listlength position)
{
    if ( position <= 0 || position > m_length + 1)
    {
        std::cout << __func__ << "() " << "Error: position out of list range" << std::endl;

        return false;
    }

    if (position == 1)
    {
        return insertNodeAtHead(value);
    }

    if (position == m_length + 1)
    {
        return insertNodeAtEnd(value);
    }

    Node *newnode = createNode(value);

    Node *prenode = getNodeAtPosition(position - 1);
    if (prenode == nullptr)
    {
        std::cout << __func__ <<"() " << "get node at position failed" << std::endl;
        
        return false;
    }

    newnode->m_next = prenode->m_next;
    prenode->m_next = newnode;

    m_length += 1;

    return true;
}

bool SinglyLinkedList::insertNodeAtHead(const DataType value)
{
    Node *newnode = createNode(value);

    newnode->m_next = m_head->m_next;
    m_head->m_next = newnode;

    m_length += 1;

    return true;
}

bool SinglyLinkedList::insertNodeAtEnd(const DataType value)
{
    Node *newnode = createNode(value);

    Node *lastnode = getNodeAtPosition(m_length);
    if (lastnode == nullptr)
    {
        std::cout << __func__ << "() " <<"get node at position failed" << std::endl;
        
        return false;
    }

    lastnode->m_next = newnode;

    std::cout << __func__ << "() " << "done, value:" << lastnode->m_next->m_data << std::endl;

    m_length += 1;
    return true;
}

bool SinglyLinkedList::removeNode(const Listlength position)
{
    if ( position <= 0 || position > m_length + 1)
    {
        std::cout << __func__ << "() "<< "Error: position out of list range" << std::endl;

        return false;
    }

    Node *prenode = getNodeAtPosition(position - 1);
    if (prenode == nullptr)
    {
        std::cout << __func__ <<"() " << "get node at position " << position <<  "failed" << std::endl;
        
        return false;
    }

    Node *removednode = prenode->m_next;
    prenode->m_next = prenode->m_next->m_next;
    
    delete removednode;
}


bool SinglyLinkedList::isListEmpty() const
{
    if ((m_head->m_next == nullptr) || (m_length == 0))
        return true;

    return false;
}

void SinglyLinkedList::printfList() const
{
    if (isListEmpty() == true)
    {
        std::cout << __func__  << "() " << "List is null" << std::endl;
    
        return;
    }

    std::cout << __func__ << "()" << std::endl;
    std::cout << "head node:" 
              << " value=" << m_head->m_data
              << " next=" << m_head->m_next
              << std::endl;

    Node *firstnode = m_head->m_next;

    std::cout << "first node:" 
              << " value=" << firstnode->m_data
              << " next=" << firstnode->m_next
              << std::endl;

    while(firstnode->m_next != nullptr)
    {
        firstnode = firstnode->m_next;

        std::cout << "next node:" 
                  << " value=" << firstnode->m_data
                  << " next=" << firstnode->m_next
                  << std::endl;
    }

/*
    std::cout << "last node:" 
              << "value=" << firstnode->m_data
              << "next=" << firstnode->m_next
              << std::endl;
*/

}

void SinglyLinkedList::clearList()
{
    if (isListEmpty() == true)
    {
        std::cout << __func__  << "() " << "List is null" << std::endl;
        return;
    }

    Listlength count = 1u;
    Node *removednode = nullptr;

    while (count <= m_length)
    {
        removednode = m_head->m_next;
        m_head->m_next = removednode->m_next;

        std::cout << __func__  << "()" 
                  << " Rremoved node, data: " << removednode->m_data 
                  << " next: " << removednode->m_next
                  << " Head node, next: " << m_head->m_next
                  << std::endl;

        if (m_head->m_next == nullptr) break;       // last node

        delete removednode;
        count += 1;
    } 

    m_length = 0;
    printfList();
}


}

