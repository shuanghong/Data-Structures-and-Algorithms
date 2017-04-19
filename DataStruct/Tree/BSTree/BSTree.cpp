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
* brief: ����ڵ�
* ���ݶ���������Ķ���, �����������еĽڵ�ֵС�����ĸ��ڵ�ֵ, �����������нڵ��ֵ���������ĸ��ڵ��ֵ, ������key�ظ��Ľڵ�
* ����������: ��ԭ���������Ϊ��, ��ֱ�Ӳ���; ��Ҫ����Ľڵ� key С�ڸ���� key������뵽��������, ������Ľڵ� key ���ڸ���� key������뵽��������.

* ����ֵ: 1 ����ɹ�, 0 ����ʧ��, ԭ�����Ժ���ͬ�� key ����.
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

    // �� root ��ʼ���Ҳ���ڵ�ĺ���λ��, �����ĸ��ڵ�
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
        parentnode->lchild = newnode;       // �½ڵ����丸�ڵ����
    else
        parentnode->rchild = newnode;       // �½ڵ����丸�ڵ���Һ�


    newnode->parent = parentnode;           // �����½ڵ�ĸ��ڵ�

    return true;
}




// �������ĸ߶�
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

	int lmax = findMaxLenBetter(pRoot->lchild); // �������е�������
	int rmax = findMaxLenBetter(pRoot->rchild); // �������е�������

	int lh = 0, rh = 0;

	if(pRoot->lchild != nullptr)
    {
		lh = height(pRoot->lchild);                 // ��������Զ��Ҷ�ӽڵ�����ڵ�ľ���
	}

	if(pRoot->rchild != nullptr)
    {
		rh = height(pRoot->rchild);         		// ��������Զ��Ҷ�ӽڵ�����ڵ�ľ���
	}

	return std::max(std::max(lmax, rmax), lh + rh);
}







}
