#include"Xe.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<ctime>
#include<iomanip>
using namespace std;
int Xe::tongTienPhat = 0;
Mylist<Pair> Xe::dsMaVung;
Xe::Xe(){
    thanhPho = bienSo = " ";
}
Xe::Xe(string &tp, string& ls, string &bs) : thanhPho(tp), loaiXe(ls), bienSo(bs) {}
Xe::~Xe(){
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

string Xe::getLS() const{
    return loaiXe;
}

Xe& Xe::operator = (const Xe& other){
    this->bienSo = other.bienSo;
    this->thanhPho = other.thanhPho;
    return *(this);
}

void Xe::setBienSo(const string& bs) {
    bienSo = bs;
}

void Xe::setThanhPho(const string& tp) {
    thanhPho = tp;
}

void Xe::truyenDSVP(const string& tenfile){
    
}

void Xe::themLoi(const string& loiVP, const string& ngayVP){
    dsLoi.push_back(Pair(loiVP, ngayVP));
    int tienPhat = 0;
    
    for(Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            tienPhat = x->getdata().getMucPhat();
        }
    }
    
    cout << "Tien phat cua " << loiVP << " la: " << fixed << setprecision(0) << tienPhat << endl;
    tongTienPhat += tienPhat;
}