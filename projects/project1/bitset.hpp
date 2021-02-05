//Bitset class header file
#ifndef BITSET_HPP
#define BITSET_HPP

#include <string>

class Bitset {
public:

  //default constructor to allocate memory for an array with 8 elements and initialize to 0;
  Bitset();

  //constructor to allocate memory for an array with number of elements specified by variable "size" and initialize to 0;
  Bitset(intmax_t size);

  //constructor to allocate memory for an array by accepting a string and converting str into u_int8_t
  Bitset(const std::string & value);

  //custom desctructor that frees allocated memory from pointers
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  //returns number of elements in bitset array
  intmax_t size() const;

  //returns a bool indicating if the bitset array is valid
  bool good() const;

  //sets an element of the array to 1, indexed by variable "index" and checks validity of bitset (index is in range [0,N-1])
  void set(intmax_t index);

  //resets the Nth bit in array to 0 and checks validity of bitset, indexed by "index"
  void reset(intmax_t index);

  //toggles value of bit to its compliment at the index from argument 
  void toggle(intmax_t index);

  //returns a bool indicating whether value of array at indexed element is 1
  bool test(intmax_t index);

  //returns the bitset as a string
  std::string asString() const;

private:

  u_int8_t *bitset = NULL; //pointer to u_int8_t to store address of dynamically allocated bitset array
  int length = 0; //int to store length of bitset depending on constructor called
  bool validation = true; //bool to store if bitset is valid (within range [0 - N-1] and contains only 1's & 0's)
  bool checkBit = true; //bool to indicate test() success or failure

};
#endif