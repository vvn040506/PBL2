#include<iostream>
#include"Police.h"
using namespace std;
HashTable<Pair>* Police::dsPolice = new HashTable<Pair>(1000);
Police::Police(){ id_police = " "; }

Police::Police(const string& id) : id_police(id) {}
Police::~Police() {}
string Police::getID() { return id_police; }

void Police::addPoliceWork(const string& id_police, const string& bienso, const string& ngay){
            if(dsPolice != nullptr){
                dsPolice->insert(id_police, Pair(bienso, ngay));
            }
        }
void Police::showPoliceWork(const string& id){
            int pos = dsPolice->hash_function(id);
            for(Node<Pair> *x = dsPolice->buckets[pos].begin(); x != dsPolice->buckets[pos].end(); x = x->getnext()){
                cout << "Da nhap vao bien so: " << x->getdata().key << " - Ngay: " << x->getdata().value << endl;
            }
        }
Mylist<Pair> Police::getPoliceWork(const string& id){
            if(dsPolice != nullptr){
                int pos = dsPolice->hash_function(id);
                return dsPolice->buckets[pos];
            }
            return Mylist<Pair>();
        }