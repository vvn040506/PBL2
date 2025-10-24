#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Mylist.h"
#include "Person.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// Forward declaration

class Person;

template <typename T>
class HashTable{
private:
    unsigned int capacity;
    unsigned int size;
public:
    Mylist<T> *buckets;
    HashTable(const unsigned int&);
    ~HashTable();
    unsigned int getCapacity();
    int hash_function(const string&);
    void insert(const string&, const T&);
    Node<T>* search(const T&);  
    void show();
    void show(const string&);
};

// Template implementations
template <typename T>
unsigned int HashTable<T>::getCapacity(){
    return capacity;
}

template <typename T>
HashTable<T>::HashTable(const unsigned int& capacity){
    buckets = new Mylist<T>[capacity];
    this->capacity = capacity;
    this->size = 0;
}

template <typename T>
HashTable<T>::~HashTable(){
    delete[] buckets;
}

template <typename T>
int HashTable<T>::hash_function(const string& key){
    return stoll(key) % this->capacity;
}

template <typename T>
void HashTable<T>::insert(const string& key, const T& value){
    int pos = hash_function(key);
    buckets[pos].push_back(value);
    size++;
}

template <typename T>
Node<T>* HashTable<T>::search(const T& key){  
    int pos = hash_function(key);
    return buckets[pos].getNodeByValue(key); 
}

template <typename T>
void HashTable<T>::show(){
    for(int i = 0; i < this->capacity; i++){
       if(buckets[i].IsEmpty()) continue;
       else buckets[i].print();
    }
}

template <typename T>
void HashTable<T>::show(const string& key){
    int pos = hash_function(key);
    Node<T> *temp = buckets[pos].getNodeByValue(key); 
    if(temp != nullptr) {
        cout << "Found at position: " << pos << endl;
    } else {
        cout << "Khong tim thay" << endl;
    }
}

void searchByCCCD(const string& cccd, HashTable<Person>& ds);
Person& getByCCCD(const string& cccd, HashTable<Person>& ds);
// Chuyển các hàm non-template sang file .cpp

#endif
