#include<iostream>
#include "BinaryTree.hpp"

using namespace binarytree;

int main(int argc, char* argv[])
{
    BinaryTree tree0;
    tree0.findMaxLen(tree0.m_root);

    BinaryTree tree1;
    tree1.buildTreeWithLeftAndRight();
    tree1.findMaxLen(tree1.m_root);
    int tree1_length = tree1.findMaxLenBetter(tree1.m_root);
    std::cout << "tree1 max length:" << tree1.getMaxLen() << std::endl;
    std::cout << "tree1 max length:" << tree1_length << std::endl;

    BinaryTree tree2;
    tree2.buildTreeWithLeft();
    tree2.findMaxLen(tree2.m_root);
    int tree2_length = tree2.findMaxLenBetter(tree2.m_root);
    std::cout << "tree2 max length:" << tree2.getMaxLen() << std::endl;
    std::cout << "tree2 max length:" << tree2_length << std::endl;

    return 0;
}
