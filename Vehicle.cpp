#include<bits/stdc++.h>
#include<string>
#include<vector>
#include"Violation.h"
#include"Vehicle.h"

using namespace std;

Vehicle::Vehicle(){
    plate = owner = " ";
}

void Vehicle::setPlate(string plate){
    this->plate = plate;
}

void Vehicle::setOwner(string owner){
    this->owner = owner;
}

string Vehicle::getPlate(){
    return plate;
}

string Vehicle::getOwner(){
    return owner;
}

void Vehicle::addViolation(const Violation &v){
    violations.push_back(v);
}

double Vehicle::totalFine(){
    double tong = 0;
    for(auto &v: violations)
        tong += v.getFine();
    return tong;
}