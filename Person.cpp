#include "Person.h"
#include "Motor.h"
#include "HashFunction.h"
#include "HashTable.h"
#include "Xe.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <limits>
#include "Motor.h"
#include "Car.h"
#include "DataGenerator.h"
#include "main1.h"
using namespace std;

// Constructor implementations
Person::Person() : cccd(""), ten(""){
    hash_xe = new vehicleshash(10, 10, 100);
}

Person::Person(const string &cccd, const string &ten, const string& sdt, const string& d) 
    : cccd(cccd), ten(ten), sdt(sdt), diachi(d) { 
            hash_xe = new vehicleshash(10, 10, 100);

}
Person::Person(const Person& other) 
    : cccd(other.cccd), ten(other.ten), sdt(other.sdt), diachi(other.diachi) {
    
    // Deep copy vehicleshash
    hash_xe = new vehicleshash(other.hash_xe->get1(), 
                               other.hash_xe->get2(), 
                               other.hash_xe->get3());
    
    // Copy tất cả xe từ hash table cũ sang mới
    for (int i = 0; i < other.hash_xe->get1(); ++i) {
        for (int j = 0; j < other.hash_xe->get2(); ++j) {
            for (int k = 0; k < other.hash_xe->get3(); ++k) {
                Node<Xe*>* current = other.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    // Clone xe (bạn cần implement clone method cho Xe)
                    Xe* xe = current->getdata();
                    Xe* newXe = new Xe(*xe); // Giả sử Xe có copy constructor
                    hash_xe->insertToHash(newXe);
                    current = current->getnext();
                }
            }
        }
    }
    
    hash_nguoi = nullptr; // Hoặc copy nếu cần
}

// Assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        // Xóa hash cũ
        if (hash_xe != nullptr) {
            delete hash_xe;
        }
        
        // Copy data
        cccd = other.cccd;
        ten = other.ten;
        sdt = other.sdt;
        diachi = other.diachi;
        
        // Deep copy hash
        hash_xe = new vehicleshash(other.hash_xe->get1(), 
                                   other.hash_xe->get2(), 
                                   other.hash_xe->get3());
        
        // Copy vehicles...
        for (int i = 0; i < other.hash_xe->get1(); ++i) {
            for (int j = 0; j < other.hash_xe->get2(); ++j) {
                for (int k = 0; k < other.hash_xe->get3(); ++k) {
                    Node<Xe*>* current = other.hash_xe->table[i][j][k].begin();
                    while (current != nullptr) {
                        Xe* newXe = new Xe(*current->getdata());
                        hash_xe->insertToHash(newXe);
                        current = current->getnext();
                    }
                }
            }
        }
    }
    return *this;
}

bool Person::operator==(const Person& other) const {
    return this->cccd == other.cccd;
}

bool Person::operator!=(const Person& other) const {
    return this->cccd != other.cccd;
}

istream& operator >> (istream& in, Person& p){
    cout << "Nhap cccd: ";
    getline(in >> ws, p.cccd);  

    cout << "Nhap ten nguoi vp: ";
    getline(in, p.ten);
    return in;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << ", Sdt: " << p.sdt << ", Dia chi: " << p.diachi << "]" << endl;
    os << "Danh sach xe vi pham:" << endl;
    
    for (int i = 0; i < p.hash_xe->get1(); ++i) {
        for (int j = 0; j < p.hash_xe->get2(); ++j) {
            for (int k = 0; k < p.hash_xe->get3(); ++k) {
                
                Node<Xe*>* current = p.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    os << "  - ";
                    current->getdata()->display();  
                    current = current->getnext();
                }
            }
        }
    }
    return os;
}

void Person::nhapTT(){
    cout << "Nhap cccd: "; cin >> cccd;
    cout << "Nhap ten nguoi vp: "; 
    cin.ignore();
    getline(cin, ten);
}

void Person::setXe(vehicleshash* xe){
    if (hash_xe != nullptr) {
        delete hash_xe;
    }
    hash_xe = xe; 
}

vehicleshash* Person::getXe(){
    return hash_xe;
}

void Person::phanTichBienSo(const string& bienSo, Xe& Xe) {
    size_t dash1 = bienSo.find('-');
    size_t dash2 = bienSo.find('-', dash1 + 1);
    
    if (dash1 != string::npos && dash2 != string::npos) {
        string maTP = bienSo.substr(0, dash1);
        string loaiXe = bienSo.substr(dash1 + 1, dash2 - dash1 - 1);
        
        Xe.setBienSo(bienSo);
        
        for (Node<Pair>* x = Xe::dsMaVung.begin(); x != nullptr; x = x->getnext()) {
            if (x->getdata().value == maTP) {
                Xe.setThanhPho(x->getdata().key);
                break;
            }
        }
    }
}


void Person :: timXe(vehicleshash* hash){
    system("cls");
    cout << "\n=== TIM KIEM XE THEO BIEN SO ===\n";
    
    cout << "Nhap bien so xe (VD: 29-A1-12345): ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hash->find(bienSo);
    if (xe) {
        xe->truyxuatLoi();
    } else {
        cout << "\nKhong tim thay xe co bien so: " << bienSo << endl;
    }
    pause();
}

void Person :: truyvanCCCD(HashTable<Person>* HashTable){
    system("cls");
    cout << "\n=== TRA CUU THEO CCCD ===\n";
    
    cout << "Nhap so CCCD: ";
    string cccd;
    getline(cin, cccd);
    
    try {
        Person &p = getByCCCD(cccd, *hashtableNguoi);
        cout << "\n--- THONG TIN CHU XE ---" << endl;
        cout << p;
    } catch (const exception& e) {
        cout << "\nKhong tim thay CCCD: " << cccd << endl;
    }
    
    pause();

}