#ifndef HASHTABLE_H
#define HASHTABLE_H
#include"Mylist.h"
#include"Person.h"
#include<iostream>
using namespace std;

template <typename T>
class HashTable{
    private:
        Mylist<T> *buckets;
        unsigned int capacity;
        unsigned int size;
    public:
        HashTable(const unsigned int&);
        ~HashTable();
        int hash_function(const string&);
        void insert(const string&, const T&);
        Node<T> search(const T&);
        void show();
        void show(const string&);
        friend void searchByCCCD(const string& cccd, HashTable<Person>& ds);
        friend Person& getByCCCD(const string& cccd, HashTable<Person>& ds);
};

template <typename T>
HashTable<T>::HashTable(const unsigned int& capacity){
    buckets = new Mylist<T>[capacity];
    this->capacity = capacity;
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
}

template <typename T>
Node<T> HashTable<T>::search(const T& key){
    int pos = hash_function(key);
    return *(buckets[pos]->getNodeByValue(key)); 
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
    Node<T> *temp = buckets[pos].getNodeByValue();
    cout << temp->getdata() << endl;
}

void searchByCCCD(const string& cccd, HashTable<Person>& ds){
    int pos = ds.hash_function(cccd);
    
    for(Node<Person> *x = ds.buckets[pos].begin(); x != ds.buckets[pos].end(); x = x->getnext()) {
        if(x->getdata().getCCCD() == cccd){
            cout << x->getdata();
            return;  
        }
    }
    
    cout << "khong tim thay cccd " << cccd << endl;
}

Person& getByCCCD(const string& cccd, HashTable<Person>& ds){
    int pos = ds.hash_function(cccd);
    
    for(Node<Person> *x = ds.buckets[pos].begin(); x != ds.buckets[pos].end(); x = x->getnext()) {
        if(x->getdata().getCCCD() == cccd){
            return x->refgetdata();
        }
    }
    
    throw runtime_error("Khong tim thay cccd " + cccd);
}
#endif