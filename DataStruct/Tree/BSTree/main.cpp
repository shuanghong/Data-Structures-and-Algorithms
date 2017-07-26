#include<iostream>
#include "BSTree.hpp"

using namespace binarysearchtree;

int main(int argc, char* argv[])
{
    std::vector<DataType> keys0 = {3, 1, 2, 4, 6, 5};
    BSTree tree0;
    tree0.buildTree(keys0, InsertMode::Recursion);
    tree0.showTree();

    std::vector<DataType> keys1= {3, 1, 2, 4, 6, 5};
    BSTree tree1;
    tree1.buildTree(keys1, InsertMode::Iteration);
    tree1.showTree();

    return 0;
}
