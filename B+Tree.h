//
// Created by Santy on 20/05/2023.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

class BPlusTree {

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
    BPlusTree(const BPlusTree &other);

    /**
     * @brief Assign operator overload
     * @param other The tree that is being assigned
     * @return A reference to the current tree
     */
    BPlusTree &operator=(const BPlusTree &other);

private:
    static const int maxChildren = 3; /**< Maximum children a node can have **/

    struct Node {
        Node *children[maxChildren + 1] = {}; /**< Array of pointers to the children of the node**/
        bool isLeaf; /**< True if node is leaf, false otherwise**/
        Node *parent; /**< Pointer to the parent of the node **/
        Node *next; /**< Pointer to the right node in the same level **/
        Node *prev; /**< Pointer to the left node in the same level **/

        /**
         * @brief Node Constructor
         */
        Node() {
            isLeaf = false;
            parent = nullptr;
            next = nullptr;
            prev = nullptr;
        }

    } *root /**< Pointer to the root of the tree **/;
};

#endif //B_TREE_B_TREE_H
