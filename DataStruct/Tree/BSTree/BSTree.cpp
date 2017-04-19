#include<iostream>

#include "BSTree.hpp"

namespace binarysearchtree
{

BSTree::BSTree()
: m_root(nullptr)
{

}

BSTree::~BSTree()
{

}

void BSTree::constructTree(const DataType *begin, const DataType *end)
{
    while (begin != end)
        insertNode(*begin++);
}

/*
* brief: 插入节点
* 根据二叉查找树的定义, 左子树上所有的节点值小于它的根节点值, 右子树上所有节点的值均大于它的根节点的值, 不存在key重复的节点
* 则插入过程是: 若原二叉查找树为空, 则直接插入; 若要插入的节点 key 小于根结点 key，则插入到左子树中, 若插入的节点 key 大于根结点 key，则插入到右子树中.

* 返回值: 1 插入成功, 0 插入失败, 原树里以后相同的 key 存在.
*/
bool BSTree::insertNode(DataType key)
{
    Node *newnode = new Node(key);

    if (m_root == nullptr)
    {
        m_root = newnode;
        return true;
    }

    Node *parentnode = nullptr;
    Node *tempnode = m_root;

    // 从 root 开始查找插入节点的合适位置, 即它的父节点
    while(tempnode != nullptr)
    {
        parentnode = tempnode;

        if (key == tempnode->m_key)
        {
            std::cout << __func__  << "() " << "Insert failed, same key:" << key << " already exists" << std::endl;
            return false;
        }

        if (key < tempnode->m_key)
        {
            tempnode = tempnode->lchild;
        }
        else
        {
            tempnode = tempnode->rchild;
        }
    }

    if (key < parentnode->m_key)
        parentnode->lchild = newnode;       // 新节点是其父节点的左孩
    else
        parentnode->rchild = newnode;       // 新节点是其父节点的右孩


    newnode->parent = parentnode;           // 更新新节点的父节点

    return true;
}




// 计算树的高度
int BSTree::height(Node *pRoot)
{
	if(pRoot == nullptr)
		return 0;

	return std::max(height(pRoot->lchild), height(pRoot->rchild)) + 1;
}

int BSTree::findMaxLenBetter(Node *pRoot)
{
    if(pRoot == nullptr)
    {
//        std::cout <<  __func__ << "() " << "root is null!" << std::endl;
        return 0;
    }

	int lmax = findMaxLenBetter(pRoot->lchild); // 左子树中的最大距离
	int rmax = findMaxLenBetter(pRoot->rchild); // 右子树中的最大距离

	int lh = 0, rh = 0;

	if(pRoot->lchild != nullptr)
    {
		lh = height(pRoot->lchild);                 // 左子树最远的叶子节点与根节点的距离
	}

	if(pRoot->rchild != nullptr)
    {
		rh = height(pRoot->rchild);         		// 右子树最远的叶子节点与根节点的距离
	}

	return std::max(std::max(lmax, rmax), lh + rh);
}







}
