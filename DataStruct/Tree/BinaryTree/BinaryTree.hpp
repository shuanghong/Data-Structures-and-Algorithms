#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_

#include<cstdint>
#include<vector>

namespace binarytree
{

enum class BuildMode: uint32_t
{
    DepthFirst = 0,
    LayerFirst,
    Invalid
};

using DataType = char;
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

    void buildTree(std::vector<DataType> &nodes, BuildMode mode);
    void showTree(void);

    void findMaxLen(void);
    int findMaxLenBetter(void);

    inline LengthType getMaxLen() const
    {
        return nMaxLen;
    };

private:
    Node* buildTreeByDepth(Node *root, std::vector<DataType> &nodes, int &index);
    Node* buildTreeByLayer(std::vector<DataType> &nodes);

    void showTree(Node *root);
    void findMaxLen(Node *root);
    int findMaxLenBetter(Node *root);
    int height(Node *root);
    void destory(Node *root);

private:
    Node *m_root;
    LengthType nMaxLen;
};


}


#endif // _BSTREE_HPP_
