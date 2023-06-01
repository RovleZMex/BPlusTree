//
// Created by Santy on 20/05/2023.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <iostream>

template <typename T, int Order>
class BPlusTree
{
public:
    BPlusTree();
    ~BPlusTree();
    BPlusTree(const BPlusTree &bPT);
    BPlusTree & operator=(const BPlusTree &bPT);
    void insert(T elemento);
    void remove(T elemento);
    bool find(T elemento) const;
    bool empty() const;
    void clear();
    void print() const;
private:
    struct Node
    {
        void **pointers;    /**> Array of pointers */
        T *keys;            /**> Array of the keys */
        Node *parent;
        bool leaf;
        int size;           /**> Number of keys */
        Node *next;         /**> Variable used for queue */

        Node()
        {
            pointers = new void*[Order];
            keys = new T[Order - 1];
            parent = NULL;
            leaf = false;
            size = 0;
            next = NULL;
        }
    } * root;

    /**> Key storage */
    struct Record
    {
        T value;
        Record(T v) : value(v) {}
    };
    /**> Basic functions */
    Node * insert(Node * root, T key, T value);
    Node * remove(Node *root, T key);
    Record * find(Node * root, T key, Node ** leafOut);
    void printTree(Node * const root);

    /**> Insert functions */
    Node * insertIntoNode(Node * root, Node * parent, int leftIndex, T key, Node * right);
    Node * insertIntoLeaf(Node * leaf, T key, Record * pointer);
    Node * insertIntoParent(Node * root, Node * left, T key, Node * right);
    Node * insertIntoNewRoot(Node * left, T key, Node * right);
    Node * insertIntoNodeAfterSplitting(Node * root, Node * parent, int leftIndex, T key, Node * right);
    Node * insertIntoLeafAfterSplitting(Node * root, Node * leaf, T key, Record * pointer);

    /**> Remove functions */
    Node * removeEntry(Node * root, Node *n, T key, void * pointer);
    Node * removeEntryFromNode(Node * n, T key, void * pointer);
    void destroyTreeNodes(Node * root);

    /**> Find functions */
    Node * findLeaf(Node * const root, T key);

    /**> Create functions */
    Node * makeLeaf();
    Node * startNewTree(T key, Record * tPointer);
    Record * makeRecord(T value);

    /**> Auxiliar functions */
    Node * adjustRoot(Node *root);
    Node * coalesceNodes(Node *root, Node *n, Node *neighbor, int neighborIndex, T kPrime);
    Node * redistributeNodes(Node *root, Node *n, Node *neighbor, int neighborIndex, int kPrimeIndex, T kPrime);
    int getNeighborIndex(Node *n);
    int getLeftIndex(Node * parent, Node * left) const;
    int cut(int length) const;
    int pathToRoot(Node * const root, Node * child);


    Node * queue;   /**> The queue is used in the print method */
    /** > Queue functions */
    void enqueue(Node * newNode);
    Node * dequeue();
};

#include "B+Tree.tpp"

#endif //B_TREE_B_TREE_H
