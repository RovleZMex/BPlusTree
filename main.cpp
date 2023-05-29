#include <iostream>
#include "B+Tree.h"

int main() {
    BTree t(4);
    t.insert(18);
    t.insert(20);
    t.insert(23);
    t.insert(8);
    t.insert(9);
    t.insert(10);
    t.insert(11);
    t.insert(15);
    t.insert(16);
    t.insert(17);
    t.insert(17);
    t.insert(17);
    t.insert(17);
    t.insert(17);
    t.insert(110);

    t.remove(110);

    bool look = t.search(17);

    if (look) std::cout << "Se encontró" << std::endl;
    else std::cout << "No se encontró" << std::endl;

    cout << "The B-tree is: \n";
    t.display();
}
