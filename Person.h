#ifndef PERSON_H
#define PERSON_H

#include"HashFunction.h"
#include"HashTable.h"
#include <iostream>
#include <string>
#include <limits.h>
#include <sstream>
#include <fstream>
using namespace std;

class Xe;
extern string Link;
extern string finalMaVung;
extern string finalMotor;
extern string finalCar;
extern string finalCCCD;
extern string finalbienSo;

template<typename T> class HashTable;

class Person {
private:
    string cccd;
    string ten;
    string diachi;
    string sdt;
    vehicleshash* hash_xe;
    HashTable<Person>* hash_nguoi;

public:
    Person();
    virtual ~Person(){
        if (hash_xe != nullptr) {
        delete hash_xe;
    }
    }
    Person(const Person& other);
    Person(const string &cccd, const string &ten, const string& sdt, const string& d);
    
    string getCCCD() const { return cccd; }
    string& getCCCD() { return cccd; }
    string getTen() const { return ten; }
    string getDiaChi() const { return diachi; }
    string getSdt() const { return sdt; }

    void setCCCD(const string& newCCCD) { cccd = newCCCD; }
    void setTen(const string& newTen) { ten = newTen; }
    void setDiaChi(const string& diaChi) { diachi = diaChi; }
    void setSdt(const string& s) { sdt = s; } 

    Person& operator=(const Person& other);
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;

    friend istream& operator >> (istream& in, Person& p);
    friend ostream& operator<<(ostream& os, const Person& p);

    void nhapTT();
    void setXe(vehicleshash* xe);
    vehicleshash* getXe();
    void timXe(vehicleshash* hash);
    
    static void phanTichBienSo(const string& bienSo, Xe& Xe);
    static void docFileDanhSach(const string& filename, HashTable<Person>& dsNguoi);
    void truyvanCCCD(HashTable<Person>* hash);
    virtual void menu();

};



#endif