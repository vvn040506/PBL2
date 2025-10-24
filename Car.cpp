
#include"Car.h"
#include<iostream>
#include<string.h>
#include<fstream>    
#include<string>
#include<iomanip>
#include"pair.hpp"
using namespace std;
long long Car::tongTienPhat = 0;
Car::Car(){
    thanhPho = " ";
    bienSo = " ";
    loaiXe = "Car";
}
Car::~Car(){

}
long long &Car::gettongTienPhat(){
    return tongTienPhat;
}

void Car::display(){
    cout << "loai xe : xe oto " <<endl;
    Xe :: display();

}


istream& operator >> (istream& in, Car& Car){
    cout << "Nhap Thanh pho/ Tinh cua xe dang ky: "; 
    getline(in, Car.thanhPho);
    
    string ma = "XX";  
    
    for(Node<Pair> *x = Car.dsMaVung.begin(); x != Car.dsMaVung.end(); x = x->getnext()){
        if(Car.thanhPho == x->getdata().key){
            ma = x->getdata().value;
            if(ma.length() > 2) ma = ma.substr(0, 2);
            break;
        }
    }
    
    cout << "Nhap loai xe: "; getline(in, Car.loaiXe);

    cout << "Nhap bien so: "; 
    getline(in, Car.bienSo);
    
    Car.bienSo = ma + "-" + Car.loaiXe + "-" + Car.bienSo;  
    // if(Car.bienSo.length() >= 7) {
    //     Car.bienSo.insert(2, "A");
    //     Car.bienSo.insert(3, "-");   
    //     Car.bienSo.insert(7, ".");   
    // }
    return in;
}

ostream& operator << (ostream& out, Car& Car){
    out << "Bien so xe: " << Car.bienSo << endl;
    out << "DS loi da vi pham: " << endl;
    for(Node<Pair> *x = Car.dsLoi.begin(); x != Car.dsLoi.end(); x = x->getnext())
        out << x->getdata().key << " - " << x->getdata().value << endl;
    return out;
}

void Car :: truyxuatLoi(){
    cout << "\n========================================" << endl;
    cout << "       TRUY VAN LOI VI PHAM O TO       " << endl;
    cout << "========================================" << endl;
    cout << "Bien so: " << bienSo << endl;
    cout << "Loai xe: O to (Car)" << endl;
    Xe :: truyxuatLoi();
}