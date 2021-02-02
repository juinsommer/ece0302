#include "bitset.cpp"
#include <iostream>

int main() {
    Bitset b;
    b.set(2);
    b.toggle(2);

    for(int i = 0; i < 8; i++)
        std::cout << (int)b.getPtr()[i] << " ";

    return 0;  
}