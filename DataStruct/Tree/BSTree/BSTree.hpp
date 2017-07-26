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

    DataType m_key;     // 节点的值
    Node *lchild;       // 指向节点的左孩子
    Node *rchild;       // 指向节点的右孩子
    Node *parent;       // 指向节点的双亲
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

    void preOrder();        //前序遍历二叉树
    void inOrder();         //中序遍历二叉树
    void postOrder();       //后序遍历二叉树
    void layerOrder();      //层次遍历二叉树

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
