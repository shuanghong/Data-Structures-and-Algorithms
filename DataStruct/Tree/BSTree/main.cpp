#include<iostream>
#include "BSTree.hpp"

using namespace binarysearchtree;

int main(int argc, char* argv[])
{
    std::vector<DataType> keys0 = {3, 1, 2, 4, 6, 5};
    BSTree tree0;
    tree0.buildTree(keys0, Mode::Recursion);
//    tree0.showTree();
    tree0.search(6, Mode::Recursion);

    std::vector<DataType> keys1= {3, 1, 2, 4, 6, 5};
    BSTree tree1;
    tree1.buildTree(keys1, Mode::Iteration);
//    tree1.showTree();
//    tree1.search(7, Mode::Recursion);
    tree1.search(7, Mode::Iteration);
    tree1.search(6, Mode::Iteration);

    tree0.preOrder(Mode::Recursion);
    printf("\n");
    tree0.preOrder(Mode::Iteration);
    printf("\n");

    tree0.inOrder(Mode::Recursion);
    printf("\n");
    tree0.inOrder(Mode::Iteration);
    printf("\n");

    tree0.postOrder(Mode::Recursion);
    printf("\n");
    tree0.postOrder(Mode::Iteration);
    return 0;
}
