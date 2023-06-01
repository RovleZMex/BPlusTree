#include <iostream>
#include "B+Tree.h"

int main() {

    BPlusTree<int, 3> tree;

    tree.insert(3);
    tree.print();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
