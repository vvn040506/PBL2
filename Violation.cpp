#include<bits/stdc++.h>
#include"Violation.h"

using namespace std;

Violation::Violation(){
    name = date = " ";
    fine = 0;
} 

void Violation::display(){
    cout << "Loi vi pham: " << name << " - " << " ngay vi pham: " << " - " << date << " muc phat tien" << fine << endl;
}

string Violation::getName(){
    return name;
}

string Violation::getDate(){
    return date;
}

double Violation::getFine(){
    return fine;
}

void Violation::setName(string name){
    this->name = name;
}

void Violation::setDate(string date){
    this->date = date;
}

void Violation::setFine(double fine){
    this->fine = fine;
}
