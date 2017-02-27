#ifndef _DOUBLY_LINKKED_LIST_HPP_
#define _DOUBLY_LINKKED_LIST_HPP_

namespace doublylinkedlist
{

using DataType = uint32_t;
const DataType InvalidValue = -1;

struct Node
{
    Node(): m_data(InvalidValue), m_prior(nullptr), m_next(nullptr){}
    Node(DataType data): m_data(data), m_prior(nullptr), m_next(nullptr){}

    DataType m_data;
    Node *m_prior;
    Node *m_next;
};

using Listlength = uint32_t;
class DoublyLinkedList
{
public:
    DoublyLinkedList();
    DoublyLinkedList(Listlength length);

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    DoublyLinkedList(const DoublyLinkedList&&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&&) = delete;

    ~DoublyLinkedList();

    Node* createNode(const DataType value);
    Node* getNodeAtPosition(const Listlength position) const;
    Node* getNodeValue(const DataType value) const;

    bool insertNodeAtPosition(const DataType value, const Listlength position);
    bool insertNodeAtHead(const DataType value);
    bool insertNodeAtEnd(const DataType value);

    bool removeNodeAtPosition(const Listlength position);
    bool removeNodeValue(const DataType value);

    bool isListEmpty() const;
    void printfList() const;
    void clearList();

    Listlength getListLength() const;

private:
    Listlength m_length;
    Node *m_head;
    Node *m_tail;
};

}


#endif
