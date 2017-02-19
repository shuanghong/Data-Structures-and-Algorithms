#include <iostream>
#include "SinglyLinkedList.hpp"

using namespace singlylinkedlist;

int main(int argc, char* argv[])
{
    SinglyLinkedList list;
    list.printfList();

    list.insertNodeAtHead(1u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtHead(2u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtEnd(3u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtEnd(4u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtPosition(5u, 1u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtPosition(4u, 4u);
    list.printfList();
    std::cout << std::endl;

    list.insertNodeAtPosition(5u, 5u);
    list.printfList();
    std::cout << std::endl;

    list.removeNode(1u);
    list.printfList();
    std::cout << std::endl;

    list.removeNode(5u);
    list.printfList();
    std::cout << std::endl;

    Node *node1 = list.getNodeAtPosition(5u);
    if (node1 == nullptr)
    {
        std::cout << "Error: node1 is null" << std::endl;

        return -1;
    }
    std::cout << "node1: data = " << node1->m_data << " next = " << node1->m_next << std::endl;

/*
    Node *node2 = list.getNodeAtPosition(15u);
    if (node2 == nullptr)
    {
        std::cout << "Error: node2 is null" << std::endl;
        return -1;
    }
*/

    Node *node3 = list.getNodeValue(5u);
    if (node3 == nullptr)
    {
        std::cout << "Error: node3 is null" << std::endl;

        return -1;
    }
    std::cout << "node3: data = " << node3->m_data << " next = " << node3->m_next << std::endl;

/*
    Node *node4 = list.getNodeValue(15u);
    if (node4 == nullptr)
    {
        std::cout << "Error: node4 is null" << std::endl;

        return -1;
    }
*/

    return 0;
}
