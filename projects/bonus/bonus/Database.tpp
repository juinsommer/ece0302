#include "Database.hpp"

template <typename T>
Database<T>::Database(): numItems(0) {}

template <typename T>
bool Database<T>::isEmpty() {
    return (data.isEmpty());
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
        firstKey = key1;
        secondKey = key2;
        return true;
    }
    return false;
}

template <typename T>
bool Database<T>::remove(std::string key) {

    if(contains(key)) {
        int item;
        if(search1.retrieve(key, item)) {
            data.remove(item);
            search1.remove(key);
        }
        if(search2.retrieve(key, item)) {
            data.remove(item);
            search2.remove(key);
        }
        return true;
    }
    
    return false;
}

template <typename T>
void Database<T>::clear() {
    search1.destroy();
    search2.destroy();
    data.clear();
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
    if(keyIndex == 1) {
        int item;
        search1.retrieve(firstKey, item);
        for(int i = 1; i <= numItems; i++)
            allEntries[i] = data.getEntry(i);

        search1.treeSort(allEntries, numItems);
    }
    return allEntries; 
}