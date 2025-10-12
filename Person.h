#ifndef PERSON_H
#define PERSON_H
#include"Xe.h"
#include"Mylist.h"
#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string cccd;
    string ten;
    Mylist<Xe*> *myXe;
public:
    Person() : cccd(""), ten("") {
        myXe = new Mylist<Xe*>;
    }
    Person(const string &cccd, const string &ten) : cccd(cccd), ten(ten){
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
        cout << "Nhap cccd: "; in >> p.cccd;
        cout << "Nhap ten nguoi vp: "; 
        in.ignore();
        getline(in, p.ten);
        return in;
    }

    friend ostream& operator << (ostream& os, const Person& p) {
        os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << "]" << endl;
        for(Node<Xe*> *x = p.myXe->begin(); x != p.myXe->end(); x = x->getnext()){
            Xe *temp = x->getdata();
            temp->display();
        }
        return os;
    }
    void setXe(Mylist<Xe*>& xe){
        myXe = new Mylist<Xe*>(xe);
    }

    Mylist<Xe*>* getXe(){
        return myXe;
    }
};

#endif
