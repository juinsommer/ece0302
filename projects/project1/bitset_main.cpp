#include "bitset.cpp"
#include <iostream>

int main() {
    Bitset b("300333333");
    std::cout << b.asString();

    for(int i = 0; i < 15; i++)
       // std::cout << (int)b.getPtr()[i];
    return 0;  
}