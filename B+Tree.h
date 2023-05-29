//
// Created by Santy on 20/05/2023.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

using namespace std;

class Node {
    int *keys;
    int order;
    Node **children;
    int numKeys;
    bool isLeaf;

public:
    Node(int t1, bool leaf1);

    void insertNonFull(int k);

    void splitChild(int i, Node *y);

    void display();

    Node *search(int key);

    friend class BTree;
};

class BTree {
public:
    explicit BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void display() {
        if (root != nullptr)
            root->display();
    }

    void insert(int k);

    bool search(int key);

    bool remove(int key);

private:
    Node *root;
    int t;

    bool remove(Node * node, int key);

    int findKey(Node * node, int key);

    void fill(Node * node, int index);

    void merge(Node * node, int index);

    void borrowFromPrev(Node * node, int index);

    void borrowFromNext(Node * node, int index);

    void removeFromLeaf(Node* node, int index);

    void removeFromNonLeaf(Node* node, int index);

    int getSucc(Node * node, int index);

    int getPred(Node * node, int index);

    Node * search(Node * node, int key);
};


#include "B+Tree.tpp"

#endif //B_TREE_B_TREE_H
