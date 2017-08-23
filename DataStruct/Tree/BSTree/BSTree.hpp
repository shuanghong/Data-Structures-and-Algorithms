#ifndef _BSTREE_HPP_
#define _BSTREE_HPP_

#include<cstdint>
#include<vector>

namespace binarysearchtree
{

enum class Mode: uint32_t
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

    void buildTree(std::vector<DataType> &nodes, Mode mode);
    void showTree(void);
    Node* search(DataType key, Mode mode);

//    void removeNode(DataType key);

    void preOrder(Mode mode);        //ǰ�����������
    void inOrder(Mode mode);         //�������������
    void postOrder(Mode mode);       //�������������
    void layerOrder();      //��α���������

private:
    Node* insertByRecursion(Node *node, DataType key);
    bool insertByIteration(DataType key);
    void showTree(Node *root);
    Node* searchByRecursion(Node *node, DataType key);
    Node* searchByIteration(Node *node, DataType key);

    int height(Node *node);

    void preOrderByRecursion(Node *node);
    void preOrderByIteration(Node *node);
    void inOrderByRecursion(Node *node);
    void inOrderByIteration(Node *node);
    void postOrderByRecursion(Node *node);
    void postOrderByIteration(Node *node);



private:
    Node *m_root;
};


}

#endif // _BSTREE_HPP_
