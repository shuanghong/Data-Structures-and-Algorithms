#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include<cstdint>
#include<array>

namespace binarysearchtree
{
using DataType = uint32_t;

struct Node
{
    Node() = default;
    Node(DataType key)
    : m_key(key), lchild(nullptr), rchild(nullptr), parent(nullptr)
    {
    }

    DataType m_key;     // �ڵ��ֵ
    Node *lchild;       // ָ��ڵ������
    Node *rchild;       // ָ��ڵ���Һ���
    Node *parent;       // ָ��ڵ��˫��
};


class BSTree
{
public:
    BSTree();

    BSTree(const BSTree&) = delete;
    BSTree& operator=(const BSTree&) = delete;
    BSTree(BSTree&&) = delete;
    BSTree& operator=(BSTree&&) = delete;

    ~BSTree();

    void constructTree(const DataType *begin, const DataType *end); // ������ֵ������
    bool insertNode(DataType key);                                  // ����ڵ�
//    void removeNode(DataType key);

    void preOrder();        //ǰ�����������
    void inOrder();         //�������������
    void postOrder();       //�������������
    void layerOrder();      //��α���������

    int height(Node *root);
    int findMaxLenBetter(Node *root);

public:
    Node *m_root;

private:
};


}


#endif // _BSTREE_HPP_
