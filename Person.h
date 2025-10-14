#ifndef PERSON_H
#define PERSON_H
#include"Xe.h"
#include"Mylist.h"
#include"HashFunction.h"
#include <iostream>
#include <string>
#include<limits.h>
using namespace std;

class Person {
private:
    string cccd;
    string ten;
    vehicleshash hash_xe;
public:
    Person() : cccd(""), ten(""),  hash_xe(34, 100, 1000) {}
    Person(const string &cccd, const string &ten, int size1, int size2, int size3) : cccd(cccd), ten(ten), hash_xe(size1, size2, size3){
    }

    string getCCCD() const { return cccd; }
    string getTen() const { return ten; }

    void setCCCD(const string& newCCCD) { cccd = newCCCD; }
    void setTen(const string& newTen) { ten = newTen; }

    bool operator==(const Person& other) const {
        return this->cccd == other.cccd;
    }

    bool operator!=(const Person& other) const {
        return this->cccd != other.cccd;
    }

    friend istream& operator >> (istream& in, Person& p){
    cout << "Nhap cccd: ";
    getline(in >> ws, p.cccd);  // ws = bỏ khoảng trắng + newline thừa

    cout << "Nhap ten nguoi vp: ";
    getline(in, p.ten);
    return in;
}

    void nhapTT(){
        cout << "Nhap cccd: "; cin >> cccd;
        cout << "Nhap ten nguoi vp: "; 
        cin.ignore();
        getline(cin, ten);
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
    os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << "]" << endl;
    os << "Danh sach xe:" << endl;
    
    // Duyệt qua tất cả các bucket trong hash table
    for (int i = 0; i < p.hash_xe.get1(); ++i) {
        for (int j = 0; j < p.hash_xe.get2(); ++j) {
            for (int k = 0; k < p.hash_xe.get3(); ++k) {
                // Lấy danh sách xe tại bucket [i][j][k]
                Node<Motor>* current = p.hash_xe.table[i][j][k].begin();
                while (current != nullptr) {
                    os << "  - ";
                    current->getdata().display();  // Hiển thị thông tin xe
                    current = current->getnext();
                }
            }
        }
    }
    return os;
}

void setXe(vehicleshash& xe){
    hash_xe = xe; 
}

// Hoặc nếu muốn copy dữ liệu
// void setXe(const vehicleshash& xe){
//     hash_xe = xe;
// }

vehicleshash& getXe(){
    return hash_xe;
}

vehicleshash* getXePtr(){
    return &hash_xe;
}
};

#endif
