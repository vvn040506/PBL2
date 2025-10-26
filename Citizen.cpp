#include"HashTable.h"
#include"Person.h"
#include "pair.hpp"
#include <iostream>
#include <string>
#include "HashFunction.h"
#include "Xe.h"
#include "Person.h"
#include "Citizen.h"
using namespace std;

Citizen :: Citizen(){}
Citizen :: Citizen(const string&){}
Citizen :: ~Citizen(){}

void Citizen :: menu(){
    system("cls");
        cout << "========================================" << endl;
        cout << "           MENU NGUOI DAN               " << endl;
        cout << "========================================" << endl;
        cout << "1. Xem thong ke tong quan" << endl;
        cout << "2. Tra cuu xe theo bien so" << endl;
        cout << "3. Tra cuu theo CCCD" << endl;
        cout << "0. Quay lai" << endl;
        cout << "========================================" << endl;
        cout << "Nhap lua chon: ";
}