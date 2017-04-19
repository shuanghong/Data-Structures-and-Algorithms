#include<iostream>
#include "BSTree.hpp"

using namespace binarysearchtree;

int main(int argc, char* argv[])
{
    BSTree tree1;

    DataType keys[] = {3, 1, 2, 4, 6, 5};
    tree1.constructTree(std::begin(keys), std::end(keys));
    int tree1_length = tree1.findMaxLenBetter(tree1.m_root);
    std::cout << "tree1 max length:" << tree1_length << std::endl;
    return 0;
}
