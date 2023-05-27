//
// Created by Santy on 20/05/2023.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

template <typename T, int Order>
class BPlusTree{
public:
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

    /**
     * @brief Verifies if a key exists in the tree
     * @param key Key to be looked for
     * @return true if the key was found, false otherwise
     */
    bool SearchKey(T key);

    /**
     * @brief Inserts a key in the tree
     * @param key Key to be inserted
     */
    void InsertKey(T key);

    /**
     * @brief Deletes a key in the tree
     * @param key Key to be deleted from the tree
     * @return true if the key was deleted, false otherwise
     */
    bool DeleteKey(T key);

    /**
     * @brief Prints the tree
     */
    void Print() const;

    /**
     * @brief Verifies if the tree is empty
     * @return true if the tree is empty, false otherwise
     */
    bool Empty() const;

    /**
     * @brief Clears all the elements in the tree
     */
    void Clear();
private:
    struct Node{
        bool isLeaf; /**< Indicates if the node is a leaf */
        int numKeys; /**< Number of keys in the node */
        T keys[Order - 1]; /**< Array of keys in the node */
        Node * children[Order]; /**< Array of pointers to the children of this node */
        Node * nextLeaf; /**< Pointer to the next leaf node */

        //TODO check if this constructor is okay
        Node(){
            isLeaf = false;
            numKeys = 0;
        }

    }*root;
    /**
 * @brief Internal method for inserting a key in the tree
 * @param node Node where the recursive call will start
 * @param key Key to be inserted in the tree
 */
    void InsertInternal(Node * node, T key);
    /**
     * @brief Internal method for searching a key in the tree
     * @param node Node where the recursive call will start
     * @param key Key to be inserted in the tree
     * @return true if the key was found, false otherwise
     */
    bool SearchInternal(Node * node, T key);
    /**
     * @brief Internal method for deleting a key in the tree
     * @param node Node where the recursive call will start
     * @param key Key to be deleted from the tree
     * @return true if the key was deleted, false otherwise
     */
    bool DeleteInternal(Node *node, T key);
    /**
     * @brief Splits the keys of the child node into two nodes
     * @param parentNode Pointer to the parent of the child node
     * @param childIndex Index of the child to be split
     */
    void SplitChild(Node * parentNode, int childIndex);
    /**
     * @brief Merges the keys of two children
     * @param parentNode Pointer to the parent of the child node
     * @param childIndex Index of the child to be merged
     */
    void MergeChildren(Node * parentNode, int childIndex);
    /**
     * @brief Adjusts the keys of the root if needed
     */
    void AdjustRoot();
};

#include "B+Tree.tpp"

#endif //B_TREE_B_TREE_H
