#include"Xe.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
int Xe::tongTienPhat = 0;
Mylist<Pair> Xe::dsMaVung;
Xe::Xe(){
    thanhPho = bienSo = " ";
}
Xe::Xe(string &tp, string &bs){
    thanhPho = tp;
    bienSo = bs;
}
Xe::~Xe(){
    cout << "Da hoan tat dong phat";
}

void Xe::docFileMaVung(const string& filename) {
    ifstream fs(filename);
    if (!fs.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }
    
    string line;
    while (getline(fs, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string thanhPho, maVung;
        string temp;
        
        ss >> temp;
        thanhPho = temp;
        while (ss >> temp) {
            if (isdigit(temp[0])) {
                maVung = temp;
                break;
            } else {
                thanhPho += " " + temp;
            }
        }
        
        if (!maVung.empty()) {
            Pair p(thanhPho, maVung);
            dsMaVung.push_back(p);
        }
    }
    fs.close();
}
string Xe::getbienSo() const{
    return bienSo;
}

string Xe::getTP() const{
    return thanhPho;
}

Xe& Xe::operator = (Xe& other){
    this->bienSo = other.bienSo;
    this->thanhPho = other.thanhPho;
    return *(this);
}
