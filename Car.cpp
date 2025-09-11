#include<bits/stdc++.h>
#include"Vehicle.h"
#include"Car.h"

using namespace std;

Car::Car(){
    type = "";
}

void Car::display(){
    cout << "Ten chu so huu phuong tien: " << owner << endl;
    plate.insert(3, ".");
    cout << "Bien so xe: " << plate << endl;
    cout << "Loai phuong tien: " << type << endl;
}

void Car::setType(){
    chon: cout << "Chon loai xe" << endl;
    cout << "1. Xe con" << endl;
    cout << "2. Xe buyt" << endl;
    cout << "3. Xe khach" << endl;
    cout << "4. Xe tai" << endl;
    cout << "Nhap so de chon: ";
    int a; 
    if(a > 4 || a < 0){
        cout << "Chon lai";
        goto chon;
    }
    if(a == 1) type = "Xe con";
    else if(a == 2) type = "Xe buyt";
    else if(a == 3) type = "Xe khach";
    else type = "Xe tai";
}