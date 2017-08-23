#include<iostream>
#include<cstdio>
#include<assert.h>
#include<queue>
#include<stack>

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
 *       2. 队首结点出队列并打印之, 再把它的左右子结点()分别存入队列
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


void BSTree::preOrder(Mode mode)
{
    assert(mode != Mode::Invalid);

    if (mode == Mode::Recursion)
    {
        printf("%s() by recursion, keys: ", __func__);
        preOrderByRecursion(this->m_root);
    }
    else if (mode == Mode::Iteration)
    {
        printf("%s() by iteration, keys: ", __func__);
        preOrderByIteration(this->m_root);
    }
}

/*brief: 先序遍历---递归方式
 *       1. 先访问根节点(打印)
 *       2. 再递归访问左子树
 *       3. 再递归访问右子树
 */
void BSTree::preOrderByRecursion(Node *node)
{
    if (node == nullptr)    //递归结束
        return;

    printf("%d ", node->m_key);   //先访问根节点(打印),再访问左子树,再访问右子树
    preOrderByRecursion(node->lchild);
    preOrderByRecursion(node->rchild);

#if 0  //另外一种实现
    if (node != nullptr)
    {
        printf("%d ", node->m_key);

        if (node->lchild != nullptr)    // 不判断也行,函数会多调用一次
            preOrderByRecursion(node->lchild);
        if (node->rchild != nullptr)
            preOrderByRecursion(node->rchild);
    }
#endif
}

/*brief: 先序遍历---迭代方式
 * 先访问根结点,然后再分别遍历左孩子和右孩子. 孩子结点,也可看做是根结点.
 * 访问完之后,若其左孩子不为空,按相同规则访问它的左子树;当访问完左子树时, 再访问它的右子树.
 * 其处理过程如下：
 *       1. 先将根节点入栈
 *       2. 判断栈是否为空,若不为空,取栈顶元素cur访问并出栈. 然后先将cur的右子节点入栈,再将cur的左子节点入栈.
 *       3. 重复2直到栈为空
 */
void BSTree::preOrderByIteration(Node *node)
{
    if (node == nullptr)
        return;

    std::stack<Node*> tree_stack;
    tree_stack.push(node);

    Node *current = nullptr;
    while(!tree_stack.empty())
    {
        current = tree_stack.top();
        printf("%d ", current->m_key);
        tree_stack.pop();

        if (current->rchild != nullptr)
            tree_stack.push(current->rchild);
        if (current->lchild != nullptr)
            tree_stack.push(current->lchild);
    }
}

void BSTree::inOrder(Mode mode)
{
    assert(mode != Mode::Invalid);

    if (mode == Mode::Recursion)
    {
        printf("%s() by recursion, keys: ", __func__);
        inOrderByRecursion(this->m_root);
    }
    else if (mode == Mode::Iteration)
    {
        printf("%s() by iteration, keys: ", __func__);
        inOrderByIteration(this->m_root);
    }
}

void BSTree::inOrderByRecursion(Node *node)
{
    if (node == nullptr)
        return;

    inOrderByRecursion(node->lchild);
    printf("%d ", node->m_key);
    inOrderByRecursion(node->rchild);
}

/*brief: 中序遍历---迭代方式
 * 对于任一根结点,先遍历其左孩子,而左孩子结点又可以看做另一根结点,然后继续遍历其左孩子结点,直到遇到左孩子结点为空的结点才进行访问.
 * 过程如下, 对于给定的二叉树根节点R
 *		1. 若其左孩子不为空，循环将R以及R左子树中的所有节点的左孩子入栈；
 *      2. 取栈顶元素cur,访问cur并将cur出栈. 再对cur的右子节点进行步骤1的处理；
 *      3. 重复1和2的操作，直到cur为空并且栈为空
 */
void BSTree::inOrderByIteration(Node *node)
{
    if (node == nullptr)
        return;

    std::stack<Node*> tree_stack;
    Node *current = node;
    while(!tree_stack.empty()  || current != nullptr)
    {
        while(current != nullptr)
        {
            tree_stack.push(current);
            current = current->lchild;  //找最左结点
        }

        current = tree_stack.top();
        tree_stack.pop();
        printf("%d ", current->m_key); //访问左孩子为空的节点

        current = current->rchild;      //转向右孩子
    }
}

void BSTree::postOrder(Mode mode)
{
    assert(mode != Mode::Invalid);

    if (mode == Mode::Recursion)
    {
        printf("%s() by recursion, keys: ", __func__);
        postOrderByRecursion(this->m_root);
    }
    else if (mode == Mode::Iteration)
    {
        printf("%s() by iteration, keys: ", __func__);
        postOrderByIteration(this->m_root);
    }
}

void BSTree::postOrderByRecursion(Node *node)
{
    if (node == nullptr)    //递归结束
        return;

    postOrderByRecursion(node->lchild);
    postOrderByRecursion(node->rchild);

    printf("%d ", node->m_key);
}

/*brief: 后序遍历---迭代方式
 * 要保证根结点在左孩子和右孩子访问之后才能访问,因此对于任一结点R
 *       1. 先将R入栈, 如果R不存在左孩子和右孩子, 则可以直接访问它并出栈；
 *       2. 如果R存在左孩子或者右孩子,但是其左孩子和右孩子都已被访问过了,则同样可以直接访问该结点并出栈.
 *       3. 若非上述两种情况,则将R的右孩子和左孩子依次入栈,这样就保证了左孩子在右孩子前面被访问
 */
void BSTree::postOrderByIteration(Node *node)
{
    if (node == nullptr)
        return;

    std::stack<Node*> tree_stack;
    tree_stack.push(node);

    Node *current = nullptr;
    Node *pre = nullptr;

    while(!tree_stack.empty())
    {
        current = tree_stack.top();

        if ((current->lchild == nullptr && current->rchild == nullptr)  // 不存在左孩子和右孩子
            || (pre != nullptr &&(pre == current->lchild || pre == current->rchild)) // 左孩子和右孩子都已被访问过了
           )
        {
            printf("%d ", current->m_key); //访问节点
            tree_stack.pop();

            pre = current;  // 保存当前结点
        }
        else
        {
            if (current->rchild != nullptr)
                tree_stack.push(current->rchild);
            if (current->lchild != nullptr)
                tree_stack.push(current->lchild);
        }


    }
}


}
