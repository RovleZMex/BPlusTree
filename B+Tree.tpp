//
// Created by Santy on 20/05/2023.
//

#include "B+Tree.h"

template<typename T, int Order>
BPlusTree<T, Order>::BPlusTree() {
    root = nullptr;
}

template<typename T, int Order>
BPlusTree<T, Order>::~BPlusTree() {
    Clear();
}

template<typename T, int Order>
BPlusTree<T, Order>::BPlusTree(const BPlusTree &other) {
     *this = other;
}

template<typename T, int Order>
BPlusTree<T, Order> &BPlusTree<T, Order>::operator=(const BPlusTree &other) {
    if(this == *other) return *this;

    return *this;
}

template<typename T, int Order>
bool BPlusTree<T,Order>::SearchKey(T key) {
    return SearchInternal(root, key);
}

template<typename T, int Order>
void BPlusTree<T, Order>::InsertKey(T key) {
    InsertInternal(root, key);
}

template<typename T, int Order>
bool BPlusTree<T, Order>::DeleteKey(T key) {
    return DeleteInternal(root, key);
}

template<typename T, int Order>
void BPlusTree<T, Order>::Print() const {
    //TODO implement print algorithm
}

template<typename T, int Order>
bool BPlusTree<T, Order>::Empty() const {
    return root == nullptr;
}

template<typename T, int Order>
void BPlusTree<T, Order>::Clear() {
    //TODO implement clearing algorithm
}

template<typename T, int Order>
void BPlusTree<T, Order>::InsertInternal(BPlusTree::Node *node, const T key) {
    //TODO implement inserting algorithm
}

template<typename T, int Order>
bool BPlusTree<T, Order>::SearchInternal(BPlusTree::Node *node, const T key) {
    //TODO implement searching algorithm
    return false;
}

template<typename T, int Order>
bool BPlusTree<T, Order>::DeleteInternal(BPlusTree::Node *node, const T key) {
    //TODO implement deleting algorithm
    return false;
}

template<typename T, int Order>
void BPlusTree<T, Order>::SplitChild(BPlusTree::Node *parentNode, int childIndex) {
    //TODO implement split algorithm
}

template<typename T, int Order>
void BPlusTree<T, Order>::MergeChildren(BPlusTree::Node *parentNode, int childIndex) {
    //TODO implement merging algorithm
}

template<typename T, int Order>
void BPlusTree<T, Order>::AdjustRoot() {
    //TODO implement adjusting root algorithm
}

