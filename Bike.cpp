#include<bits/stdc++.h>
#include"Vehicle.h"
#include"Bike.h"

using namespace std;

Bike::Bike(){
    type = "xe may";
}

void Bike::display(){
    cout << "Ten chu so huu phuong tien: " << owner << endl;
    plate.insert(3, ".");
    cout << "Bien so xe: " << plate << endl;
    cout << "Loai phuong tien: " << type << endl;
}