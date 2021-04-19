
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "binary_search_tree.hpp"
#include "list.hpp"
#include <string>
#include <vector>

template <typename T>
class Database
{
public:
  Database();

  // determine if the database is empty
  bool isEmpty();

  // return current number of entries
  std::size_t getNumberOfEntries();

  // insert entry 
  bool add(std::string key1, std::string key2, const T& item);

  // removes both keys and the data
  bool remove(std::string key);

  // remove all entries
  void clear();

  // retrieve the value of the entry associated with the input key
  T getValue(std::string key);

  // return true if an entry exists associated with the input key
  bool contains(std::string key);

  // return all entries in search key order: 
  // sort by key1 if keyIndex==1, key2 if keyIndex==2
  // key1 and key2 should be consistent with the add method parameters
  std::vector<T> getAllEntries(int keyIndex);

private:
  int numItems;
  std::vector<std::string> keyChain;
  List<T> data;
  BinarySearchTree<std::string, int> search1, search2;
};

#include "Database.tpp"
#endif // _DATABASE_H_
