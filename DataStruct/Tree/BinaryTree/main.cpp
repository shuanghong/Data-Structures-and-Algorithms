#include<iostream>
#include "BinaryTree.hpp"

using namespace binarytree;

int main(int argc, char* argv[])
{
    std::vector<DataType> nodes0 = {1,-1,3,4,-1,5,6}; //{1,2,-1,-1,5,6,7,8,9};//{1,-1,3,4,5,6,7,8,9};//{1,2,-1,4,5,6,7,8,9};//{1,-1,3,-1,5,-1,6};
    BinaryTree tree0;
    tree0.buildTree(nodes0, BuildMode::LayerFirst);
    tree0.showTree();

    tree0.findMaxLen();
    int tree0_length = tree0.findMaxLenBetter();
    std::cout << "tree0 max length:" << tree0.getMaxLen() << std::endl;
    std::cout << "tree0 max length:" << tree0_length << std::endl;


    std::vector<DataType> nodes1 = {'A','#','C','#','E','#','G','H'};
    BinaryTree tree1;
    tree1.buildTree(nodes1, BuildMode::LayerFirst);
    tree1.showTree();

    tree1.findMaxLen();
    int tree1_length = tree1.findMaxLenBetter();
    std::cout << "tree1 max length:" << tree1.getMaxLen() << std::endl;
    std::cout << "tree1 max length:" << tree1_length << std::endl;

    return 0;
}
