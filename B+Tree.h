//
// Created by Santy on 20/05/2023.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

class BPlusTree{

    /**
     * @brief Class Constructor
     */
    BPlusTree();

    /**
     * @brief Class Destructor
     */
    ~BPlusTree();

    /**
     * @brief Copies Constructor
     * @param other Tree to be copied
     */
    BPlusTree(const BPlusTree& other);

    /**
     * @brief Assign operator overload
     * @param other The tree that is being assigned
     * @return A reference to the current tree
     */
    BPlusTree& operator=(const BPlusTree &other);

};

#endif //B_TREE_B_TREE_H
