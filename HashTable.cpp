#include "HashTable.h"
#include "Person.h"
#include <iostream>
using namespace std;

void searchByCCCD(const string& cccd, HashTable<Person>& ds){
    int pos = ds.hash_function(cccd);
    
    for(Node<Person> *x = ds.buckets[pos].begin(); x != nullptr; x = x->getnext()) {
        if(x->getdata().getCCCD() == cccd){
            Person &p = x->refgetdata();
            cout << p;
            return ;  
        }
    }
    
    cout << "khong tim thay cccd " << cccd << endl;
}

Person& getByCCCD(const string& cccd, HashTable<Person>& ds) {
    int pos = ds.hash_function(cccd);
    for (Node<Person>* x = ds.buckets[pos].begin(); x != nullptr; x = x->getnext()) {
        if (x->getdata().getCCCD() == cccd)  
            return x->refgetdata();  //
    }
    throw runtime_error("Khong tim thay CCCD");
}
