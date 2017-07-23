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

/*brief: 构建二叉树, 采用自上而下、从左到右的顺序构造, 遇到-1或者'#'表示空结点.
 *       实现分两步, 第一步为每个结点分配存储空间, 第二步将不为空的结点串联起来.
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
    //i 索引当前结点, j 索引左结点和右结点
    for (int i=0, j=0; i<nodesize && j<nodesize; i++)
    {
        //如果每个结点均有效,则每i次循环j移动两个位置,
        //如{1,2,3,4,5},1的左右结点是2,3; 2的左右结点是4,5
        if (treenode[i] != nullptr)
        {
            if ((j + 1) < nodesize)
            {
                j += 1;
                treenode[i]->pLeft = treenode[j];//pLeft可能为空, 如{1,-1...}
            }
            if ((j + 1) < nodesize)
            {
                j += 1;
                treenode[i]->pRight = treenode[j];
            }
        }
        //如果结点为空,要看空结点的位置, 二叉树结点最多有两个,分奇偶位置,根节点、左结点、右结点、左结点...
        //i为奇数,如{1,-1,3,4,5}, 空结点为左结点,其后面的右结点3的左右结点是4,5. j不变; 再如{1,-1,3,-1,5,6}
        //i为偶数,{1,2,-1,4,5,6,7},空结点为右结点, 其前面的左结点4的左右结点是6，7. j仍不变
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

/*brief: 打印二叉树, 参考二叉树的层次遍历
 *       1. 首先把二叉树根结点存入队列
 *       2. 对手结点出队列并打印之, 再把它的左右子结点分别存入队列
 *       3. 重复上面操作, 直至队列为空
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
    // 递归遍历到叶子节点, 或者是空树.
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


int BinaryTree::findMaxLenBetter()
{
    return findMaxLenBetter(this->m_root);
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

// 计算树的高度
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
        if (pRoot->pLeft != nullptr)    // 节点有左子树, 继续遍历
            destory(pRoot->pLeft);
        if (pRoot->pRight != nullptr)    // 左子树遍历完, 继续遍历
            destory(pRoot->pRight);

        delete pRoot;               // 左右子树都为空, 即叶子节点, 释放内存
        pRoot = nullptr;
    }


}

}
