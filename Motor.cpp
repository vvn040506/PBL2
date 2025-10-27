#include"Motor.h"
#include<iostream>
#include<string.h>
#include<fstream>    
#include<string>
#include<iomanip>
#include"pair.hpp"
using namespace std;
long long Motor::tongTienPhat = 0;
Motor::Motor(){
    thanhPho = " ";
    bienSo = " ";
    loaiXe = "Motor";
}
Motor::~Motor(){
    // cout << "Da hoan tat dong phat" << endl;
}
long long &Motor::gettongTienPhat(){
    return tongTienPhat;
}

void Motor::display(){
    cout << "loai xe : xe Motor " <<endl;
    Xe :: display();

}

istream& operator >> (istream& in, Motor& motor){
    cout << "Nhap Thanh pho/ Tinh cua xe dang ky: "; 
    getline(in, motor.thanhPho);
    
    string ma = "XX";  
    
    for(Node<Pair> *x = motor.dsMaVung.begin(); x != motor.dsMaVung.end(); x = x->getnext()){
        if(motor.thanhPho == x->getdata().key){
            ma = x->getdata().value;
            if(ma.length() > 2) ma = ma.substr(0, 2);
            break;
        }
    }
    
    cout << "Nhap ki hieu loai xe: "; getline(in, motor.loaiXe);

    cout << "Nhap bien so: "; 
    getline(in, motor.bienSo);
    
    motor.bienSo = ma + "-" + motor.loaiXe + "-" + motor.bienSo;  
 
    return in;
}

ostream& operator << (ostream& out, Motor& motor){
    out << "Bien so xe: " << motor.bienSo << endl;
    out << "DS loi da vi pham: " << endl;
    for(Node<Pair> *x = motor.dsLoi.begin(); x != motor.dsLoi.end(); x = x->getnext())
        out << x->getdata().key << " - " << x->getdata().value << endl;
    return out;
}

void Motor :: truyxuatLoi(){
    cout << "\n========================================" << endl;
    cout << "       TRUY VAN LOI VI PHAM Motor       " << endl;
    cout << "========================================" << endl;
    cout << "Bien so: " << bienSo << endl;
    cout << "Loai xe: Motor " << endl;
    Xe :: truyxuatLoi();
}

