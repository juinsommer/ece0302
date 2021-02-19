#include<iostream>
#include "linked_list.hpp"

int main() {

    LinkedList<int> list;

    for(int i = 1; i <= 10; i++) {
        list.insert(i, i);
        // std::cout << list.getEntry(i) << " ";
    }

    list.insert(11, 0);

    for(int i = 1; i <= 11; i++)
        std::cout << list.getEntry(i) << " ";

    return 0;
}

