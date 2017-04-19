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

    void constructTree(const DataType *begin, const DataType *end); // 用数组值构建树
    bool insertNode(DataType key);                                  // 插入节点
//    void removeNode(DataType key);

    void preOrder();        //前序遍历二叉树
    void inOrder();         //中序遍历二叉树
    void postOrder();       //后序遍历二叉树
    void layerOrder();      //层次遍历二叉树

    int height(Node *root);
    int findMaxLenBetter(Node *root);

public:
    Node *m_root;

private:
};


}


#endif // _BSTREE_HPP_
