#include<iostream>
#include<queue>
#include<assert.h>
#include<cstdio>

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

void BinaryTree::buildTree(std::vector<DataType> &nodes, BuildMode mode)
{
    assert(mode < BuildMode::Invalid);

    if (mode == BuildMode::LayerFirst)
    {
        m_root = buildTreeByLayer(nodes);
    }
    else if (mode == BuildMode::DepthFirst)
    {
        int index = 0;
        m_root = buildTreeByDepth(m_root, nodes, index);
    }
}

/*brief: ����������, �������϶��¡������ҵ�˳����, ����-1����'#'��ʾ�ս��.
 *       ʵ�ַ�����, ��һ��Ϊÿ��������洢�ռ�, �ڶ�������Ϊ�յĽ�㴮������.
 */

Node* BinaryTree::buildTreeByLayer(std::vector<DataType> &nodes)
{
    int nodesize = nodes.size();

    Node **treenode = new Node *[nodesize];

    for (int i = 0; i < nodesize; ++i)
    {
        if (nodes[i] == '#' || nodes[i] == -1)
            treenode[i] = nullptr;
        else
            treenode[i] = new Node(nodes[i]);
    }
    //i ������ǰ���, j ����������ҽ��
    for (int i=0, j=0; i<nodesize && j<nodesize; i++)
    {
        //���ÿ��������Ч,��ÿi��ѭ��j�ƶ�����λ��,
        //��{1,2,3,4,5},1�����ҽ����2,3; 2�����ҽ����4,5
        if (treenode[i] != nullptr)
        {
            if ((j + 1) < nodesize)
            {
                j += 1;
                treenode[i]->pLeft = treenode[j];//pLeft����Ϊ��, ��{1,-1...}
            }
            if ((j + 1) < nodesize)
            {
                j += 1;
                treenode[i]->pRight = treenode[j];
            }
        }
        //������Ϊ��,Ҫ���ս���λ��, ������������������,����żλ��,���ڵ㡢���㡢�ҽ�㡢����...
        //iΪ����,��{1,-1,3,4,5}, �ս��Ϊ����,�������ҽ��3�����ҽ����4,5. j����; ����{1,-1,3,-1,5,6}
        //iΪż��,{1,2,-1,4,5,6,7},�ս��Ϊ�ҽ��, ��ǰ�������4�����ҽ����6��7. j�Բ���
        else
        {
        }
    }
    return *treenode;
}

Node* BinaryTree::buildTreeByDepth(Node *p, std::vector<DataType> &nodes, int &index)
{
    if (index >= nodes.size())
        return nullptr;

    if (nodes[index] == '#' || nodes[index] == -1)
    {
        index += 1;
        std::cout << "Current Node is null, next is: " << nodes[index] << std::endl;
        return nullptr;
    }

    p = new Node(nodes[index]);
    std::cout << "Node is:" << nodes[index] << std::endl;

    index += 1;
    p->pLeft = buildTreeByDepth(p->pLeft, nodes, index);
    p->pRight = buildTreeByDepth(p->pRight, nodes, index);

    return p;
}

void BinaryTree::showTree()
{
    showTree(this->m_root);
}

/*brief: ��ӡ������, �ο��������Ĳ�α���
 *       1. ���ȰѶ����������������
 *       2. ���ֽ������в���ӡ֮, �ٰ����������ӽ��ֱ�������
 *       3. �ظ��������, ֱ������Ϊ��
 */
void BinaryTree::showTree(Node *root)
{
    if (root == nullptr)
        return;

    std::queue<Node*> tree_queue;
    tree_queue.push(root);

    while(!tree_queue.empty())
    {
        Node *current_node = tree_queue.front();
        //std::cout << "current node is:" << current_node->m_key << std::endl;
        printf("current node is: %d\n",current_node->m_key);
        fflush(stdout);

        tree_queue.pop();
        if (current_node->pLeft != nullptr)
        {
            //std::cout << "left node is:" << current_node->pLeft->m_key << std::endl;
            printf("left node is: %d\n", current_node->pLeft->m_key);
            tree_queue.push(current_node->pLeft);
        }
        if (current_node->pRight != nullptr)
        {
            //std::cout << "right node is:" << current_node->pRight->m_key << std::endl;
            printf("right node is: %d\n", current_node->pRight->m_key);
            tree_queue.push(current_node->pRight);
        }

    }
}

void BinaryTree::findMaxLen()
{
    return findMaxLen(this->m_root);
}

void BinaryTree::findMaxLen(Node* pRoot)
{
    // �ݹ������Ҷ�ӽڵ�, �����ǿ���.
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


int BinaryTree::findMaxLenBetter()
{
    return findMaxLenBetter(this->m_root);
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

// �������ĸ߶�
int BinaryTree::height(Node *pRoot)
{
    if(pRoot == nullptr)
        return 0;

    return std::max(height(pRoot->pLeft), height(pRoot->pRight)) + 1;
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

}
