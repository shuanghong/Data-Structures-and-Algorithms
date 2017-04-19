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

    DataType m_key;     // �ڵ��ֵ
    Node *pLeft;       // ָ��ڵ������
    Node *pRight;       // ָ��ڵ���Һ���

    LengthType nMaxLeft;    // �������������
    LengthType nMaxRight;   // �������������
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
