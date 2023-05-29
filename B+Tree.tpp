//
// Created by Santy on 20/05/2023.
//

#include "B+Tree.h"

Node::Node(int t1, bool leaf1) {
    order = t1;
    isLeaf = leaf1;

    keys = new int[2 * order - 1];
    children = new Node *[2 * order];

    numKeys = 0;
}

void Node::display() {
    int i;
    for (i = 0; i < numKeys; i++) {
        if (!isLeaf)
            children[i]->display();
        cout << " " << keys[i];
    }

    if (!isLeaf)
        children[i]->display();
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new Node(t, true);
        root->keys[0] = k;
        root->numKeys = 1;
    } else {
        if (root->numKeys == 2 * t - 1) {
            Node *s = new Node(t, false);

            s->children[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else
            root->insertNonFull(k);
    }
}

void Node::insertNonFull(int k) {
    int i = numKeys - 1;

    if (isLeaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        numKeys = numKeys + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->numKeys == 2 * order - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}


void Node::splitChild(int i, Node *y) {
    Node *z = new Node(y->order, y->isLeaf);
    z->numKeys = order - 1;

    for (int j = 0; j < order - 1; j++)
        z->keys[j] = y->keys[j + order];

    if (!y->isLeaf) {
        for (int j = 0; j < order; j++)
            z->children[j] = y->children[j + order];
    }

    y->numKeys = order - 1;
    for (int j = numKeys; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[order - 1];
    numKeys = numKeys + 1;
}

bool BTree::search(int key) {
    if (root == nullptr)return false;
    return search(root, key);
}

bool BTree::remove(int key) {
    if (root == nullptr) return false;

    bool removed = remove(root, key);

    if (root->numKeys == 0) {
        Node *temp = root;
        if (root->isLeaf)
            root = nullptr;
        else
            root = root->children[0];
        delete temp;
    }

    return removed;
}

bool BTree::remove(Node *node, int key) {
    int index = findKey(node, key);
    if (index < node->numKeys && node->keys[index] == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, index);
        } else {
            removeFromNonLeaf(node, index);
        }
        return true;
    } else {
        if (node->isLeaf) return false;
    }
    bool flag = (index == node->numKeys);

    if (node->children[index]->numKeys < t) {
        fill(node, index);
    }

    if (flag && index > node->numKeys)
        return remove(node->children[index - 1], key);
    else
        return remove(node->children[index], key);
}

int BTree::findKey(Node *node, int key) {
    int index = 0;
    while (index < node->numKeys && node->keys[index] < key)
        index++;
    return index;
}

void BTree::fill(Node *node, int index) {
    if (index != 0 && node->children[index - 1]->numKeys >= t) {
        borrowFromPrev(node, index);
    } else if (index != node->numKeys && node->children[index + 1]->numKeys >= t) {
        borrowFromNext(node, index);
    } else {
        if (index != node->numKeys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

void BTree::merge(Node *node, int index) {
    Node *child = node->children[index];
    Node *sibling = node->children[index + 1];

    child->keys[t - 1] = node->keys[index];

    for (int i = 0; i < sibling->numKeys; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; ++i) {
            child->children[i + t] = sibling->children[i];
        }
    }

    for (int i = index + 1; i < node->numKeys; ++i) {
        node->keys[i - 1] = sibling->keys[i];
    }

    for (int i = index + 2; i < node->numKeys; ++i) {
        node->children[i - 1] = node->children[i];
    }

    child->numKeys += sibling->numKeys + 1;
    node->numKeys--;
    delete sibling;
}

void BTree::borrowFromPrev(Node *node, int index) {
    Node *child = node->children[index];
    Node *sibling = node->children[index - 1];

    // Mueve todas las claves en child una posición hacia adelante
    for (int i = child->numKeys - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    // Si child no es un nodo hoja, mueve todos los punteros C una posición hacia adelante
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    }

    // Establece la primera clave de child igual a la clave correspondiente en el nodo actual
    child->keys[0] = node->keys[index - 1];

    // Mueve la clave del hermano al nodo actual
    node->keys[index - 1] = sibling->keys[sibling->numKeys - 1];

    // Si sibling no es un nodo hoja, mueve el último puntero C de sibling a child
    if (!sibling->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];

    child->numKeys++;
    sibling->numKeys--;
}

void BTree::borrowFromNext(Node *node, int index) {
    Node *child = node->children[index];
    Node *sibling = node->children[index + 1];

    // Establece la última clave de child igual a la clave correspondiente en el nodo actual
    child->keys[child->numKeys] = node->keys[index];

    // Mueve la primera clave del hermano al nodo actual
    node->keys[index] = sibling->keys[0];

    // Mueve todas las claves en sibling una posición hacia atrás
    for (int i = 1; i < sibling->numKeys; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    // Si sibling no es un nodo hoja, mueve todos los punteros C una posición hacia atrás
    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; i++)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->numKeys++;
    sibling->numKeys--;
}

void BTree::removeFromLeaf(Node *node, int index) {
    // Elimina la clave del nodo hoja y mueve las claves restantes hacia la izquierda
    for (int i = index + 1; i < node->numKeys; i++)
        node->keys[i - 1] = node->keys[i];

    node->numKeys--;
}

void BTree::removeFromNonLeaf(Node *node, int index) {
    int k = node->keys[index];

    if (node->children[index]->numKeys >= t) {
        // Si el hijo que precede a la clave tiene al menos t claves,
        // se encuentra el predecesor y se reemplaza la clave por el predecesor,
        // luego se elimina el predecesor del subárbol adecuado
        int pred = getPred(node, index);
        node->keys[index] = pred;
        remove(node->children[index], pred);
    } else if (node->children[index + 1]->numKeys >= t) {
        // Si el hijo que sigue a la clave tiene al menos t claves,
        // se encuentra el sucesor y se reemplaza la clave por el sucesor,
        // luego se elimina el sucesor del subárbol adecuado
        int succ = getSucc(node, index);
        node->keys[index] = succ;
        remove(node->children[index + 1], succ);
    } else {
        // Si ambos hijos tienen menos de t claves, se fusiona la clave y los dos hijos en uno
        merge(node, index);
        remove(node->children[index], k);
    }
}

int BTree::getSucc(Node *node, int index) {
    // Se desciende por el subárbol más a la izquierda para encontrar el sucesor
    Node *cur = node->children[index + 1];
    while (!cur->isLeaf)
        cur = cur->children[0];
    return cur->keys[0];
}

int BTree::getPred(Node *node, int index) {
    // Se desciende por el subárbol más a la derecha para encontrar el predecesor
    Node *cur = node->children[index];
    while (!cur->isLeaf)
        cur = cur->children[cur->numKeys];
    return cur->keys[cur->numKeys - 1];
}

Node *BTree::search(Node *node, int key) {
    int idx = 0;
    while (idx < node->numKeys && key > node->keys[idx])
        ++idx;

    if (idx < node->numKeys && key == node->keys[idx])
        return node;

    if (node->isLeaf)
        return nullptr;

    return search(node->children[idx], key);
}

Node *Node::search(int key) {
    int i = 0;
    while (i < numKeys && key > keys[i]) {
        if (keys[i] == key) return this;
        i++;
    }
    if (isLeaf) return nullptr;
    return children[i]->search(key);
}

