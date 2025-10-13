#include"Motor.h"
#include<iostream>
#include<limits>
#include<fstream>    
#include<string>
#include<iomanip>
#include"pair.hpp"
using namespace std;
int Motor::tongTienPhat = 0;
Motor::Motor(){
    thanhPho = " ";
    bienSo = " ";
}
Motor::Motor(const Motor& other) : Xe(other),dsLoi(other.dsLoi),danhSachMucPhat(other.danhSachMucPhat){}
Motor::~Motor(){
    //if (tongTienPhat == 0) cout << "Da hoan tat dong phat";
}
int &Motor::gettongTienPhat(){
    return tongTienPhat;
}

void Motor::display(){
    cout << "Bien so xe: " << bienSo << endl;
    cout << "DS Loi: " << endl;
    for(Node<Pair> *x = dsLoi.begin(); x != dsLoi.end(); x = x->getnext())
        cout << x->getdata().key << " - " << x->getdata().value << endl;
}

void Motor::dongPhat(const string& loiVP, const string& ngayVP){
    int tienPhat = 0;
    for(Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            tienPhat = x->getdata().getMucPhat(); 
        break;}
    }
    dsLoi.erase(Pair(loiVP, ngayVP));
    tongTienPhat -= tienPhat;
    //if(tongTienPhat == 0) cout << "Hoan tat dong phat" << endl;
}

void Motor::docFileMucPhat(const string& tenFile){
    ifstream fs(tenFile);
    if(!fs.is_open()){
        cout << "Khong the mo file " << tenFile << endl;
        return;
    }
    string line;
    while (getline(fs, line)) {
        if (line.empty()) continue;
        
        size_t first_space = line.find(' '); 
        if (first_space == string::npos) continue;

        size_t last_space = line.find_last_of(' ');
        if (last_space == string::npos || last_space <= first_space) continue;

        string idStr = line.substr(0, first_space);
        string mucPhatStr = line.substr(last_space + 1);

        string tenLoi = line.substr(first_space + 1, last_space - (first_space + 1));
        
        int id = stoi(idStr);
        int mucPhat = stoi(mucPhatStr);

        Violation p(id, tenLoi, mucPhat);
        this->danhSachMucPhat.push_back(p);
    }
    fs.close();
}
void Motor::themLoi(const string& loiVP, const string& ngayVP){
    dsLoi.push_back(Pair(loiVP, ngayVP));

    if (this->danhSachMucPhat.begin() == nullptr) return;
    int tienPhat = 0;
    
    for(Node<Violation>* x = this->danhSachMucPhat.begin(); x != this->danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            tienPhat = x->getdata().getMucPhat();
        }
    }
    
    //cout << "Tien phat cua " << loiVP << " la: " << fixed << setprecision(0) << tienPhat << endl;
    tongTienPhat += tienPhat;
    
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
    
    cout << "Nhap bien so: "; 
    in >> motor.bienSo;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    motor.bienSo = ma + motor.bienSo;  
    if(motor.bienSo.length() >= 7) {
        motor.bienSo.insert(2, "A");
        motor.bienSo.insert(3, "-");   
        motor.bienSo.insert(7, ".");   
    }
    return in;
}

ostream& operator << (ostream& out, Motor& motor){
    out << "Bien so xe: " << motor.bienSo << endl;
    out << "DS loi da vi pham: " << endl;
    for(Node<Pair> *x = motor.dsLoi.begin(); x != motor.dsLoi.end(); x = x->getnext())
        out << x->getdata().key << " - " << x->getdata().value << endl;
    return out;
}
