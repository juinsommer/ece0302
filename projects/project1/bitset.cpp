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

    length = value.length();
    bitset = new u_int8_t [size()];

    for(int i = 0; i < size(); i++) {
        if(value[i] == '0')
            bitset[i] = 0;
        else if(value[i] == '1')
            bitset[i] = 1;
        else {
            
            bitset[i] = 0;
            validation = false;
        }
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
    val = bitset[index - 1];
    bitset[index - 1] = !val;
}

bool Bitset::test(intmax_t index) { 

   validation = (index <= 0 || index -1 > length) ? false : true;
   checkBit = (bitset[index -1] != 1 ) ? false : true;
   return checkBit;
 }

std::string Bitset::asString() const {

    std::string tempStr = "";
    for(int i = 0; i < size(); i++) {
        if(bitset[i] == 0)
            tempStr.append("0");
        else if(bitset[i] == 1)
            tempStr.append("1");
        else
            tempStr.append(" ");
    }
    return tempStr;
}