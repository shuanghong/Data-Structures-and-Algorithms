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
* brief: �ò���ڵ�ķ�ʽ�������������, �����еݹ�͵������ַ���.
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
* brief: �ݹ鷽ʽ����ڵ�
* ���ݶ���������Ķ���, ����ڵ�key < ��ǰ�ڵ�, ����뵽��������, ����ڵ�key > ��ǰ�ڵ�, ����뵽��������.
* ��˵ݹ���ȥ, �����ҵ�һ���ڵ�����ӻ����Һ���Ϊ��, �����ڵ�.
*
* ����ֵ: ���ڵ�.
*/

Node* BSTree::insertByRecursion(Node *node, DataType key)
{
    if (node == nullptr)    //����, �����ǵݹ鵽��ĳ���ڵ����/�Һ���Ϊ��, �½��ڵ㲢������ڵ㷵�ظ�ĳ���ڵ����/�Һ���.
    {
        return new Node(key);
    }
     if (key > node->m_key)
         node->rchild = insertByRecursion(node->rchild, key);// �ݹ���ȥ, һֱ���Һ���Ϊ��ʱ����
     else if (key < node->m_key)
         node->lchild = insertByRecursion(node->lchild, key);// �ݹ���ȥ, һֱ������Ϊ��ʱ����
     else
         std::cout << __func__  << "() " << "Insert failed, same key:" << key << " already exists" << std::endl;

     return node;
}

/*
* brief: ������ʽ����ڵ�
* 1. ��ԭ���������Ϊ��, ��ֱ�Ӳ���; 
* 2. Ѱ�Ҳ���ڵ��λ��, Ҳ�������ĸ��ڵ�.
*    ��Ҫ����Ľڵ� key С�ڽڵ� key������뵽��������;
*    ������Ľڵ� key ���ڽڵ� key������뵽��������.

* ����ֵ: 1 ����ɹ�, 0 ����ʧ��, ԭ��������ͬ�� key ����.
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

    // �� root ��ʼ���Ҳ���ڵ�ĺ���λ��
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
    if (node == nullptr)    //����.
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
        return searchByRecursion(node->rchild, key);// �ݹ���ȥ
    else //(key < node->m_key)
        return searchByRecursion(node->lchild, key);// �ݹ���ȥ
}

Node *BSTree::searchByIteration(Node *node, DataType key)
{
    if (node == nullptr)    //����.
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
	// ���е����ﻹû�˳�����û�ҵ�key��
    printf("%s(), search failed, key: %d\n", __func__, key);
    return nullptr;
}

// �������ĸ߶�
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

/*brief: ��ӡ���������, �ο���α���
 *       1. ���Ȱ��������������
 *       2. ���׽������в���ӡ֮, �ٰ����������ӽ��()�ֱ�������
 *       3. �ظ��������, ֱ������Ϊ��
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

/*brief: �������---�ݹ鷽ʽ
 *       1. �ȷ��ʸ��ڵ�(��ӡ)
 *       2. �ٵݹ����������
 *       3. �ٵݹ����������
 */
void BSTree::preOrderByRecursion(Node *node)
{
    if (node == nullptr)    //�ݹ����
        return;

    printf("%d ", node->m_key);   //�ȷ��ʸ��ڵ�(��ӡ),�ٷ���������,�ٷ���������
    preOrderByRecursion(node->lchild);
    preOrderByRecursion(node->rchild);

#if 0  //����һ��ʵ��
    if (node != nullptr)
    {
        printf("%d ", node->m_key);

        if (node->lchild != nullptr)    // ���ж�Ҳ��,����������һ��
            preOrderByRecursion(node->lchild);
        if (node->rchild != nullptr)
            preOrderByRecursion(node->rchild);
    }
#endif
}

/*brief: �������---������ʽ
 * �ȷ��ʸ����,Ȼ���ٷֱ�������Ӻ��Һ���. ���ӽ��,Ҳ�ɿ����Ǹ����.
 * ������֮��,�������Ӳ�Ϊ��,����ͬ�����������������;��������������ʱ, �ٷ�������������.
 * �䴦��������£�
 *       1. �Ƚ����ڵ���ջ
 *       2. �ж�ջ�Ƿ�Ϊ��,����Ϊ��,ȡջ��Ԫ��cur���ʲ���ջ. Ȼ���Ƚ�cur�����ӽڵ���ջ,�ٽ�cur�����ӽڵ���ջ.
 *       3. �ظ�2ֱ��ջΪ��
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

/*brief: �������---������ʽ
 * ������һ�����,�ȱ���������,�����ӽ���ֿ��Կ�����һ�����,Ȼ��������������ӽ��,ֱ���������ӽ��Ϊ�յĽ��Ž��з���.
 * ��������, ���ڸ����Ķ��������ڵ�R
 *		1. �������Ӳ�Ϊ�գ�ѭ����R�Լ�R�������е����нڵ��������ջ��
 *      2. ȡջ��Ԫ��cur,����cur����cur��ջ. �ٶ�cur�����ӽڵ���в���1�Ĵ���
 *      3. �ظ�1��2�Ĳ�����ֱ��curΪ�ղ���ջΪ��
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
            current = current->lchild;  //��������
        }

        current = tree_stack.top();
        tree_stack.pop();
        printf("%d ", current->m_key); //��������Ϊ�յĽڵ�

        current = current->rchild;      //ת���Һ���
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
    if (node == nullptr)    //�ݹ����
        return;

    postOrderByRecursion(node->lchild);
    postOrderByRecursion(node->rchild);

    printf("%d ", node->m_key);
}

/*brief: �������---������ʽ
 * Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ���,��˶�����һ���R
 *       1. �Ƚ�R��ջ, ���R���������Ӻ��Һ���, �����ֱ�ӷ���������ջ��
 *       2. ���R�������ӻ����Һ���,���������Ӻ��Һ��Ӷ��ѱ����ʹ���,��ͬ������ֱ�ӷ��ʸý�㲢��ջ.
 *       3. ���������������,��R���Һ��Ӻ�����������ջ,�����ͱ�֤���������Һ���ǰ�汻����
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

        if ((current->lchild == nullptr && current->rchild == nullptr)  // ���������Ӻ��Һ���
            || (pre != nullptr &&(pre == current->lchild || pre == current->rchild)) // ���Ӻ��Һ��Ӷ��ѱ����ʹ���
           )
        {
            printf("%d ", current->m_key); //���ʽڵ�
            tree_stack.pop();

            pre = current;  // ���浱ǰ���
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
