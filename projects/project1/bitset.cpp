//Bitset class implementation file
#include "bitset.hpp"
#include <iostream>

//*************************************************************************************************
//please comment on readability, comments, and efficiency of code and suggestions to make it better
//*************************************************************************************************

//default constructor to allocate memory for an array with 8 elements and initialize to 0;
Bitset::Bitset(){ 
    
    bitset = (u_int8_t*)calloc(8, sizeof(u_int8_t));//calloc to allocate memory for array and initialized elements to 0
    length = 8;
 }
//constructor to allocate memory for an array with number of elements specified by variable "size" and initialize to 0;
Bitset::Bitset(intmax_t size) {

   length = size;
   
   //conditional statement to check validity of bitset 
   //all conditional statements in this program serve same purpose
   validation = (size <= 0) ? false : true; 
   bitset = (u_int8_t*)calloc(size, sizeof(u_int8_t));
}

//constructor to allocate memory for an array by accepting a string and converting str into u_int8_t
Bitset::Bitset(const std::string & value) {

    length = value.length();
    
    bitset = (u_int8_t*)malloc(size() * sizeof(u_int8_t)); //use malloc for same purpose of calloc but doesn't initialize elements to 0

    //iterate through array and convert each char to fixed width int
    for(int i = 0; i < size(); i++) {

        if(value[i] == '0')
            bitset[i] = 0;

        else if(value[i] == '1')
            bitset[i] = 1;

        else {
            //case for input other than 1 or 0
            bitset[i] = NULL;
            validation = false;
        }
    }
}

Bitset::~Bitset() { free(bitset); } //frees memory from pointers allocated by malloc/calloc

intmax_t Bitset::size() const { return length; }

bool Bitset::good() const { return validation; } //returns a bool indicating bitset validity

//sets an element of the array to 1, indexed by variable "index" and checks validity of bitset (index is in range [0,N-1])
void Bitset::set(intmax_t index) {

    validation = (index <= 0 || index -1 > length) ? false : true;
    bitset[index - 1] = 1;
}

//resets the Nth bit in array to 0 and checks validity of bitset, indexed by "index"
void Bitset::reset(intmax_t index) {
    validation = (index <= 0 || index -1 > length) ? false : true;
    bitset[index - 1] = 0;
}

//toggles value of bit to its compliment at the index from argument 
void Bitset::toggle(intmax_t index) {
    validation = (index <= 0 || index -1 > length) ? false : true;
    int val;
    val = bitset[index - 1];
    bitset[index - 1] = !val;
}

//returns a bool indicating whether value of array at indexed element is 1
bool Bitset::test(intmax_t index) { 

   validation = (index <= 0 || index -1 > length) ? false : true;
   checkBit = (bitset[index -1] != 1 ) ? false : true;

   return checkBit;
 }

//returns the bitset as a string
std::string Bitset::asString() const {

    std::string tempStr = "";
    //iterates over array to appends each value as a char to empty temp str variable
    for(int i = 0; i < size(); i++) {

        if(bitset[i] == 0)
            tempStr.append("0");

        else if(bitset[i] == 1)
            tempStr.append("1");
            
        else
            tempStr.append(" "); //case for invalid input 
    }
    return tempStr;
}