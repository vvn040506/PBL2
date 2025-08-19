#include<bits/stdc++.h>
#include<iostream>
#include"Vehicle.h"

using namespace std;

istream& operator >> (istream &in, Vehicle& p){
    cout << "Nhap bien so xe vi pham: "; in >> p.licensePlate;
    cout << "Nhap ten chu xe vi pham: "; in.ignore(); getline(in, p.name);
    cout << "Nhap ngay sinh cua chu xe vi pham: "; in >> p.birth;
    
    cout << "Nhap loi vi pham: "; in.ignore(); getline(in, p.punish);

    if(p.birth[2] != '/') p.birth =  "0" + p.birth;
    if(p.birth[4] == '/') p.birth.insert(3, "0");

    while(p.licensePlate.length() < 5){
        p.licensePlate = "0" + p.licensePlate;
    } 
    // Bike* bikePtr = dynamic_cast<Bike*>(&p);
    // if (bikePtr) bikePtr->setVehicle();
    return in;
}

ostream& operator << (ostream &out, Vehicle p){
    out << "Thong tin ve xe vi pham: " << endl;
    out << "Bien so xe: " << p.licensePlate << endl;
    out << "Ten chu so huu xe: " << p.name << endl;
    out << "Ngay sinh cua chu so huu xe: " << p.birth << endl;
    out << "Loai xe vi pham: " << p.vehicle << endl;
    out << "Loi vi pham: " << p.punish << endl;
    p.dong_phat();
    // out << "So tien phat phai dong: ";
    return out;
}

typedef struct NodeInfo{
    Vehicle p;
    struct NodeInfo *next;
} *Node;

typedef struct HashTableInfo{
    unsigned int capacity;
    Node *T;
} *HashTable;

//tạo HashTable
HashTable createHashTable(unsigned int capacity){
    HashTable H = (HashTable) malloc(sizeof(struct HashTableInfo));
    if(H == NULL) return NULL;
    H->T = (Node*) malloc(sizeof(Node) * capacity);
    if(H->T == NULL) return NULL;
    for(int i = 0; i < capacity; i++)
        H->T[i] = (Node) malloc(sizeof(struct NodeInfo));
    
    H->capacity = capacity;
    return H;
}

HashTable create_Hash_Table(unsigned int capacity){
    HashTable H = new HashTableInfo;
    H->capacity = capacity;
    H->T = new Node[capacity];
    for(int i = 0; i < capacity; i++){
        H->T[i] = new NodeInfo;
        H->T[i]->next = nullptr;
    }
    return H;
}

int hash_function(int key, HashTable H){
    return key % H->capacity;
}

//thêm xe phạt

void add(Vehicle p, HashTable H){
    Node newNode = new NodeInfo;
    newNode->p = p;
    int pos = hash_function(p.getLicensePlate(), H);
    newNode->next = H->T[pos]->next;
    H->T[pos]->next = newNode;
}