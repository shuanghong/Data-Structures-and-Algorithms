#include<iostream>

#include "BinaryTree.hpp"

namespace binarytree
{

BinaryTree::BinaryTree()
: m_root(nullptr), nMaxLen(0u)
{

}

BinaryTree::~BinaryTree()
{
    destory(m_root);
}


void BinaryTree::buildTreeWithLeftAndRight()
{
    Node *newnode0 = new Node(0u);
    m_root = newnode0;

    Node *newnode1 = new Node(1u);
    m_root->pLeft = newnode1;

    Node *newnode2 = new Node(2u);
    m_root->pLeft->pLeft = newnode2;

    Node *newnode3 = new Node(3u);
    m_root->pLeft->pLeft ->pLeft = newnode3;

    Node *newnode4 = new Node(4u);
    m_root->pRight = newnode4;

    Node *newnode5 = new Node(5u);
    m_root->pRight->pRight = newnode5;

    Node *newnode6 = new Node(6u);
    m_root->pRight->pRight->pRight = newnode6;
}

void BinaryTree::buildTreeWithLeft()
{
    Node *newnode0 = new Node(0u);
    m_root = newnode0;

    Node *newnode1 = new Node(1u);
    m_root->pLeft = newnode1;

    Node *newnode2 = new Node(2u);
    m_root->pLeft->pLeft = newnode2;

    Node *newnode3 = new Node(3u);
    m_root->pLeft->pRight = newnode3;

    Node *newnode4 = new Node(4u);
    m_root->pLeft->pLeft = newnode4;

    Node *newnode5 = new Node(5u);
    m_root->pLeft->pRight->pRight = newnode5;
}



void BinaryTree::findMaxLen(Node* pRoot)
{
    // 遍历到叶子节点??? 应该是判断空树吧!
    if(pRoot == nullptr)
    {
        std::cout <<  __func__ << "() " << "root is null!" << std::endl;
        return;
    }

    // 如果左子树为空，那么该节点的左边最长距离为0
    if(pRoot -> pLeft == nullptr)
    {
        pRoot -> nMaxLeft = 0;
    }

    // 如果右子树为空，那么该节点的右边最长距离为0
    if(pRoot -> pRight == nullptr)
    {
        pRoot -> nMaxRight = 0;
    }

    // 如果左子树不为空，递归寻找左子树最长距离
    if(pRoot -> pLeft != nullptr)
    {
        findMaxLen(pRoot -> pLeft);
    }

    // 如果右子树不为空，递归寻找右子树最长距离
    if(pRoot -> pRight != nullptr)
    {
        findMaxLen(pRoot -> pRight);
    }

    // 计算左子树最长节点距离
    if(pRoot -> pLeft != nullptr)
    {
        int nTempMax = 0;
        if(pRoot -> pLeft -> nMaxLeft > pRoot -> pLeft -> nMaxRight)
        {
            nTempMax = pRoot -> pLeft -> nMaxLeft;
        }
        else
        {
            nTempMax = pRoot -> pLeft -> nMaxRight;
        }
        pRoot -> nMaxLeft = nTempMax + 1;
    }

    // 计算右子树最长节点距离
    if(pRoot -> pRight != nullptr)
    {
        int nTempMax = 0;
        if(pRoot -> pRight -> nMaxLeft > pRoot -> pRight -> nMaxRight)
        {
            nTempMax = pRoot -> pRight -> nMaxLeft;
        }
        else
        {
            nTempMax = pRoot -> pRight -> nMaxRight;
        }
        pRoot -> nMaxRight = nTempMax + 1;
    }

    // 更新最长距离
    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
    {
        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
    }
}

void BinaryTree::destory(Node* pRoot)
{
    if (pRoot != nullptr)
    {
        if (pRoot->pLeft != nullptr)    // 节点有左子树, 继续遍历
            destory(pRoot->pLeft);
        if (pRoot->pRight != nullptr)    // 左子树遍历完, 继续遍历
            destory(pRoot->pRight);

        delete pRoot;               // 左右子树都为空, 即叶子节点, 释放内存
        pRoot = nullptr;
    }


}

// 计算树的高度
int BinaryTree::height(Node *pRoot)
{
	if(pRoot == nullptr)
		return 0;

	return std::max(height(pRoot->pLeft), height(pRoot->pRight)) + 1;
}

int BinaryTree::findMaxLenBetter(Node *pRoot)
{
    if(pRoot == nullptr)
        return 0;

	int lmax = findMaxLenBetter(pRoot->pLeft); // 左子树中的最大距离
	int rmax = findMaxLenBetter(pRoot->pRight); // 右子树中的最大距离

	int lh = 0, rh = 0;
	if(pRoot->pLeft != nullptr)
    {
		lh = height(pRoot->pLeft);                 // 左子树最远的叶子节点与根节点的距离
	}
	if(pRoot->pRight != nullptr)
    {
		rh = height(pRoot->pRight);         		// 右子树最远的叶子节点与根节点的距离
	}

	return std::max(std::max(lmax, rmax), lh + rh);
}





}
