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
    // ������Ҷ�ӽڵ�??? Ӧ�����жϿ�����!
    if(pRoot == nullptr)
    {
        std::cout <<  __func__ << "() " << "root is null!" << std::endl;
        return;
    }

    // ���������Ϊ�գ���ô�ýڵ����������Ϊ0
    if(pRoot -> pLeft == nullptr)
    {
        pRoot -> nMaxLeft = 0;
    }

    // ���������Ϊ�գ���ô�ýڵ���ұ������Ϊ0
    if(pRoot -> pRight == nullptr)
    {
        pRoot -> nMaxRight = 0;
    }

    // �����������Ϊ�գ��ݹ�Ѱ�������������
    if(pRoot -> pLeft != nullptr)
    {
        findMaxLen(pRoot -> pLeft);
    }

    // �����������Ϊ�գ��ݹ�Ѱ�������������
    if(pRoot -> pRight != nullptr)
    {
        findMaxLen(pRoot -> pRight);
    }

    // ������������ڵ����
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

    // ������������ڵ����
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

    // ���������
    if(pRoot -> nMaxLeft + pRoot -> nMaxRight > nMaxLen)
    {
        nMaxLen = pRoot -> nMaxLeft + pRoot -> nMaxRight;
    }
}

void BinaryTree::destory(Node* pRoot)
{
    if (pRoot != nullptr)
    {
        if (pRoot->pLeft != nullptr)    // �ڵ���������, ��������
            destory(pRoot->pLeft);
        if (pRoot->pRight != nullptr)    // ������������, ��������
            destory(pRoot->pRight);

        delete pRoot;               // ����������Ϊ��, ��Ҷ�ӽڵ�, �ͷ��ڴ�
        pRoot = nullptr;
    }


}

// �������ĸ߶�
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

	int lmax = findMaxLenBetter(pRoot->pLeft); // �������е�������
	int rmax = findMaxLenBetter(pRoot->pRight); // �������е�������

	int lh = 0, rh = 0;
	if(pRoot->pLeft != nullptr)
    {
		lh = height(pRoot->pLeft);                 // ��������Զ��Ҷ�ӽڵ�����ڵ�ľ���
	}
	if(pRoot->pRight != nullptr)
    {
		rh = height(pRoot->pRight);         		// ��������Զ��Ҷ�ӽڵ�����ڵ�ľ���
	}

	return std::max(std::max(lmax, rmax), lh + rh);
}





}
