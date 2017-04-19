#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_

#include<cstdint>

namespace binarytree
{
using DataType = uint32_t;
using LengthType = uint32_t;

struct Node
{
    Node() = default;
    Node(DataType key)
    : m_key(key), pLeft(nullptr), pRight(nullptr), nMaxLeft(0u), nMaxRight(0)
    {
    }

    DataType m_key;     // 节点的值
    Node *pLeft;       // 指向节点的左孩子
    Node *pRight;       // 指向节点的右孩子

    LengthType nMaxLeft;    // 左子树的最长距离
    LengthType nMaxRight;   // 右子树的最长距离
};


class BinaryTree
{
public:
    BinaryTree();

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;
    BinaryTree(BinaryTree&&) = delete;
    BinaryTree& operator=(BinaryTree&&) = delete;

    ~BinaryTree();

    void buildTreeWithLeftAndRight();
    void buildTreeWithLeft();

    void findMaxLen(Node *root);
    void destory(Node *root);
    inline LengthType getMaxLen() const
    {
        return nMaxLen;
    };

    int height(Node *root);
    int findMaxLenBetter(Node *root);

    Node *m_root;

private:
    LengthType nMaxLen;
};


}


#endif // _BSTREE_HPP_
