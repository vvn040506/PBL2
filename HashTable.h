#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Mylist.h"
#include <QString>
#include <stdexcept>

class Person;

template <typename T>
class HashTable {
private:
    unsigned int capacity;
    unsigned int size;

public:
    Mylist<T> *buckets;
    HashTable(const unsigned int& capacity);
    ~HashTable();
    unsigned int getCapacity();
    int hash_function(const QString& key);
    void insert(const QString& key, const T& value);
    Node<T>* search(const T& key);
    void show();
    void show(const QString& key);
};

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
int HashTable<T>::hash_function(const QString& key){
    bool ok;
    long long num = key.toLongLong(&ok);
    if (ok) {
        return num % this->capacity;
    } else {
        int hash = 0;
        for (int i = 0; i < key.length(); ++i) {
            hash = (hash * 31 + key[i].unicode()) % this->capacity;
        }
        return hash;
    }
}

template <typename T>
void HashTable<T>::insert(const QString& key, const T& value){
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
        if(buckets[i].isEmpty()) continue;
        else buckets[i].print();
    }
}

template <typename T>
void HashTable<T>::show(const QString& key){
    int pos = hash_function(key);
    Node<T> *temp = buckets[pos].getNodeByValue(key);
    if(temp != nullptr) {
        qDebug() << "Found at position: " << pos;
    } else {
        qDebug() << "Khong tim thay";
    }
}

void searchByCCCD(const QString& cccd, HashTable<Person>& ds);
Person& getByCCCD(const QString& cccd, HashTable<Person>& ds);

#endif // HASHTABLE_H
