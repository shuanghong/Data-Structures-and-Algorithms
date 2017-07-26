#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include<cstdint>
#include<vector>

namespace binarysearchtree
{

enum class InsertMode: uint32_t
{
    Recursion= 0,
    Iteration,
    Invalid
};

using DataType = char;

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

    void buildTree(std::vector<DataType> &nodes, InsertMode mode);
    void showTree(void);

//    void removeNode(DataType key);

    void preOrder();        //ǰ�����������
    void inOrder();         //�������������
    void postOrder();       //�������������
    void layerOrder();      //��α���������

private:
    Node* insertByRecursion(Node *node, DataType key);
    bool insertByIteration(DataType key);
    void showTree(Node *root);

    int height(Node *node);

private:
    Node *m_root;
};


}

#endif // _BSTREE_HPP_
