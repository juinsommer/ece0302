#include "Database.hpp"

template <typename T>
Database<T>::Database(): numItems(0) {}

template <typename T>
bool Database<T>::isEmpty() {
    return (data.isEmpty() && search1.isEmpty() && search2.isEmpty());
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() {
    return data.getLength();
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, const T& item) {

    if(!contains(key1) && !contains(key2)) {
        data.insert(++numItems, item);

        search1.insert(key1, numItems);
        search2.insert(key2, numItems);

        keyChain.push_back(key1); //push keys to keyChain vector 
        keyChain.push_back(key2); //to assist other method functionality
        return true;
    }
    return false;
}

template <typename T>
bool Database<T>::remove(std::string key) {
    
    if(isEmpty()) throw std::range_error("DataBase is empty. Cannot remove item.\n");

    if(contains(key)) {
        int item, index = 0;
        for(auto i : keyChain) {
            if(i == key)
                break;
            index++;
        }
        if(index == keyChain.size()) throw std::range_error("Item to remove not found.\n");
    
        if(index == 0 || index % 2 == 0) { //if index is even, its pair must right after 
            search1.retrieve(key, item);
            search1.remove(key);
            search2.remove(keyChain[index + 1]);
            keyChain.erase(keyChain.begin() + index);
            keyChain.erase(keyChain.begin() + index + 1);
        }
        else { //if index is odd, its pair must be before it
            search2.retrieve(key, item);
            search1.remove(keyChain[index - 1]);
            search2.remove(key);
            keyChain.erase(keyChain.begin() + index);
            keyChain.erase(keyChain.begin() + index - 1);
        }
        --numItems;
        data.remove(item);
        return true;
    }
    
    return false;
}

template <typename T>
void Database<T>::clear() {
    for(int i = 0; i < keyChain.size(); i++) {
           if(i == 0 || i % 2 == 0) 
               search1.remove(keyChain[i]);
       }
    for(int i = 0; i < keyChain.size(); i++) {
           if(i % 2 != 0)
               search2.remove(keyChain[i]);
       }
    data.clear();
    keyChain.clear();
}

template <typename T>
T Database<T>::getValue(std::string key) {
    int item;
    if(search1.retrieve(key, item))
        return data.getEntry(item);

    if(search2.retrieve(key, item))
        return data.getEntry(item);

    else
        throw std::range_error("item not found\n");
}

template <typename T>
bool Database<T>::contains(std::string key) {
    int item;
    if(!search1.isEmpty()) {
        if(search1.retrieve(key, item))
            return true;
    } 

    if(!search2.isEmpty()) {
        if(search2.retrieve(key, item))
            return true;
    }

    return false;
}

template <typename T>
std::vector<T> Database<T>::getAllEntries(int keyIndex) {
    std::vector<T> allEntries;
    int item;
   
    if(keyIndex == 1) {
       for(int i = 0; i < keyChain.size(); i++) {
           if(i == 0 || i % 2 == 0) {
               search1.retrieve(keyChain[i], item);
               allEntries.push_back(data.getEntry(item));
           }
       }
    }
    if(keyIndex == 2) {
        for(int i = 0; i < keyChain.size(); i++) {
           if(i % 2 != 0) {
               search2.retrieve(keyChain[i], item);
               allEntries.push_back(data.getEntry(item));
           }
       }
    }
    
    return allEntries; 
}