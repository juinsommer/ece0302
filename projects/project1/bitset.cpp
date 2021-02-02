#include "bitset.hpp"
#include <iostream>

Bitset::Bitset(){ 

    bitset = (u_int8_t*)calloc(8, sizeof(u_int8_t));
    length = 8;
 }
Bitset::Bitset(intmax_t size) {

   length = size;
   validation = (size <= 0) ? false : true;
   bitset = (u_int8_t*)calloc(size, sizeof(u_int8_t));
}

Bitset::Bitset(const std::string & value) {

    bits = value;
    bitset = (u_int8_t*)malloc(length * sizeof(u_int8_t));

    for(int i = 0; i < value.length(); i++) {

        if(value[i] != '0' || value[i] != '1')
            validation = false;

        *(bitset + i) = value[i];
    }
}

Bitset::~Bitset() { free(bitset); }

intmax_t Bitset::size() const { return length; }

bool Bitset::good() const { return validation; }

void Bitset::set(intmax_t index) {
    validation = (index <= 0 || index -1 > length) ? false : true;
    bitset[index - 1] = 1;
}

void Bitset::reset(intmax_t index) {
    validation = (index <= 0 || index -1 > length) ? false : true;
    bitset[index - 1] = 0;
}

void Bitset::toggle(intmax_t index) {
    validation = (index <= 0 || index -1 > length) ? false : true;
    int val;
    bitset[index - 1] = !val;
}

bool Bitset::test(intmax_t index) { 

   validation = (bitset[index -1] != 1 ) ? false : true;
   return validation;
 }

std::string Bitset::asString() const { return bits; }

u_int8_t* Bitset::getPtr() { return bitset; }