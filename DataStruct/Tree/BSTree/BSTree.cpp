#include<iostream>
#include<cstdio>
#include<assert.h>
#include<queue>

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
/*
* brief: 用插入节点的方式构建二叉查找树, 插入有递归和迭代两种方法.
*
*
*/
void BSTree::buildTree(std::vector<DataType> &nodes, Mode mode)
{
    assert(mode != Mode::Invalid);

    if (mode == Mode::Recursion)
    {
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            m_root = insertByRecursion(this->m_root, *it);
        }
    }
    else if (mode == Mode::Iteration)
    {
        for (const auto &it : nodes)
        {
            insertByIteration(it);
        }
    }
}

/*
* brief: 递归方式插入节点
* 根据二叉查找树的定义, 插入节点key < 当前节点, 则插入到左子树中, 插入节点key > 当前节点, 则插入到右子树中.
* 如此递归下去, 最后会找到一个节点的左孩子或者右孩子为空, 则插入节点.
*
* 返回值: 根节点.
*/

Node* BSTree::insertByRecursion(Node *node, DataType key)
{
    if (node == nullptr)    //空树, 或者是递归到了某个节点的左/右孩子为空, 新建节点并把这个节点返回给某个节点的左/右孩子.
    {
        return new Node(key);
    }
     if (key > node->m_key)
         node->rchild = insertByRecursion(node->rchild, key);// 递归下去, 一直到右孩子为空时返回
     else if (key < node->m_key)
         node->lchild = insertByRecursion(node->lchild, key);// 递归下去, 一直到左孩子为空时返回
     else
         std::cout << __func__  << "() " << "Insert failed, same key:" << key << " already exists" << std::endl;

     return node;
}

/*
* brief: 迭代方式插入节点
* 1. 若原二叉查找树为空, 则直接插入; 
* 2. 寻找插入节点的位置, 也就是它的父节点.
*    若要插入的节点 key 小于节点 key，则插入到左子树中;
*    若插入的节点 key 大于节点 key，则插入到右子树中.

* 返回值: 1 插入成功, 0 插入失败, 原树里有相同的 key 存在.
*/
bool BSTree::insertByIteration(DataType key)
{
    Node *newnode = new Node(key);

    if (m_root == nullptr)
    {
        m_root = newnode;
        return true;
    }

    Node *parentnode = nullptr;
    Node *tempnode = m_root;

    // 从 root 开始查找插入节点的合适位置
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

Node *BSTree::search(DataType key, Mode mode)
{
    assert(mode != Mode::Invalid);

    if (mode == Mode::Recursion)
    {
        return searchByRecursion(this->m_root, key);
    }
    else if (mode == Mode::Iteration)
    {
        return searchByIteration(this->m_root, key);
    }

}

Node *BSTree::searchByRecursion(Node *node, DataType key)
{
    if (node == nullptr)    //空树.
    {
        printf("%s(), Tree is null or search failed, key: %d\n", __func__, key);
        return nullptr;
    }

    if (key == node->m_key)
    {
        printf("%s(), done, key: %d\n", __func__, key);
        return node;
    }
    else if (key > node->m_key)
        return searchByRecursion(node->rchild, key);// 递归下去
    else //(key < node->m_key)
        return searchByRecursion(node->lchild, key);// 递归下去
}

Node *BSTree::searchByIteration(Node *node, DataType key)
{
    if (node == nullptr)    //空树.
    {
        printf("%s(), Tree is null!!! key: %d\n", __func__);
        return nullptr;
    }

    Node *tempnode = node;

    while(tempnode != nullptr)
    {
        if (key == tempnode->m_key)
        {
            printf("%s(), done, key: %d\n", __func__, key);
            return tempnode;
        }
        else if (key > tempnode->m_key)
        {
            tempnode = tempnode->rchild;
        }
        else //(key < node->m_key)
        {
            tempnode = tempnode->lchild;
        }
    }
	// 运行到这里还没退出就是没找到key了
    printf("%s(), search failed, key: %d\n", __func__, key);
    return nullptr;
}

// 计算树的高度
int BSTree::height(Node *pRoot)
{
	if(pRoot == nullptr)
		return 0;

	return std::max(height(pRoot->lchild), height(pRoot->rchild)) + 1;
}

void BSTree::showTree()
{
    showTree(this->m_root);
}

/*brief: 打印二叉查找树, 参考层次遍历
 *       1. 首先把树根结点存入队列
 *       2. 对手结点出队列并打印之, 再把它的左右子结点()分别存入队列
 *       3. 重复上面操作, 直至队列为空
 */
void BSTree::showTree(Node *root)
{
    if (root == nullptr)
        return;

    std::queue<Node*> tree_queue;
    tree_queue.push(root);

    while(!tree_queue.empty())
    {
        Node *current_node = tree_queue.front();
        printf("current node is: %d\n",current_node->m_key);
        fflush(stdout);

        tree_queue.pop();
        if (current_node->lchild != nullptr)
        {
            printf("left node is: %d\n", current_node->lchild->m_key);
            tree_queue.push(current_node->lchild);
        }
        if (current_node->rchild != nullptr)
        {
            printf("right node is: %d\n", current_node->rchild->m_key);
            tree_queue.push(current_node->rchild);
        }
    }
}

}
