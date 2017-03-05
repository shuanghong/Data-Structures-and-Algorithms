#ifndef _SINGLY_LINKED_LIST_HPP_
#define _SINGLY_LINKED_LIST_HPP_

#include<cstdint>

namespace singlylinkedlist
{

using DataType = uint32_t;

const DataType InvalidValue = -1;

struct Node
{
    Node(): m_data(InvalidValue), m_next(nullptr){}

    Node(DataType data): m_data(data), m_next(nullptr){}

    Node(DataType data, Node *node): m_data(data), m_next(node){}

    DataType m_data;
    Node *m_next;
};


using Listlength = uint32_t;

class SinglyLinkedList
{
public:
    SinglyLinkedList();
    
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    SinglyLinkedList(const SinglyLinkedList&&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&&) = delete;

    ~SinglyLinkedList();

    Node* createNode(const DataType value);
    Node* getNodeAtPosition(const Listlength position) const;
    Node* getNodeValue(const DataType value) const;

    bool insertNodeAtPosition(const DataType value, const Listlength position);
    bool insertNodeAtHead(const DataType value);
    bool insertNodeAtEnd(const DataType value);

    bool removeNode(const Listlength position);

    Node* reverseList(Node *head);

    bool isListEmpty() const;
    void printfList() const;
    void clearList();

    inline Listlength getListLength() const
    {
        return m_length;
    }

private:
    Listlength m_length;
    Node *m_head;
};

}

#endif
