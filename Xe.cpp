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
    soLoi = 0;
}

Xe::Xe(string &tp, string& ls, string &bs,int soLoi) : thanhPho(tp), loaiXe(ls), bienSo(bs), soLoi(soLoi) {}

Xe::~Xe(){}

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
            Pair p(thanhPho, maVung,true);
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

int Xe :: getsoLoi(){
    return soLoi;
}

int &Xe::gettongTienPhat(){
    return tongTienPhat;
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
void Xe::docFileMucPhat(const string& tenFile){
    ifstream fs(tenFile);
    if(!fs.is_open()){
        cout << "Khong the mo file " << tenFile << endl;
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

        Violation p(id, tenLoi, mucPhat,true);
        Xe::danhSachMucPhat.push_back(p);
    }
    fs.close();
}
void Xe::themLoi(const string& loiVP, const string& ngayVP){
    dsLoi.push_back(Pair(loiVP, ngayVP,false));
    int tienPhat = 0;
    
    for(Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            x->getdata().setState(false);
            tienPhat = x->getdata().getMucPhat();
        }
    }
    
    cout << "Tien phat cua " << loiVP << " la: " << fixed << setprecision(0) << tienPhat << endl;
    tongTienPhat += tienPhat;
    soLoi++;
}

void Xe::dongPhat(const string& loiVP, const string& ngayVP){
    int tienPhat = 0;
    for(Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            tienPhat = x->getdata().getMucPhat();
            x->getdata().setState(false);
        }
    }
    tongTienPhat -= tienPhat;
    if(tongTienPhat == 0) cout << "Hoan tat dong phat" << endl;
    soLoi--;
}

void Xe :: display(){
    cout << "Bien so xe: " << bienSo << endl;
    cout << "DS Loi: " << endl;
    for(Node<Pair> *x = dsLoi.begin(); x != dsLoi.end(); x = x->getnext())
        cout << x->getdata().key << " - " << x->getdata().value << endl;
}

void Xe :: truyxuatLoi(){
    if (dsLoi.size() == 0) {
        cout << "\nKhong co loi vi pham!" << endl;
        cout << "========================================" << endl;
        return;
    }
    
    cout << "\nDanh sach loi vi pham:" << endl;
    cout << "----------------------------------------" << endl;
    cout << left << setw(5) << "STT" 
         << setw(30) << "Loi vi pham" 
         << setw(15) << "Ngay vi pham"
         << setw(15) << "Tien phat" << endl;
    cout << "----------------------------------------" << endl;
    
    int stt = 1;
    long long tongTien = 0;
    
    Node<Pair>* loiNode = dsLoi.begin();
    while (loiNode != nullptr) {
        string tenLoi = loiNode->getdata().key;
        string ngayVP = loiNode->getdata().value;
        
        int tienPhat = 0;
        Node<Violation>* v = danhSachMucPhat.begin();
        while (v != nullptr) {
            if (v->getdata().getLoiViPham() == tenLoi) {
                tienPhat = v->getdata().getMucPhat();
                break;
            }
            v = v->getnext();
        }
        
        cout << left << setw(5) << stt++
             << setw(30) << tenLoi
             << setw(15) << ngayVP
             << setw(15) << tienPhat << " VND" << endl;
        
        if (loiNode->getdata().State == true )tongTien += tienPhat;

        if (loiNode->getdata().State) {
            cout << " - [DA DONG PHAT]" << endl;
        } else {
            cout << " - [CHUA DONG PHAT]" << endl;
        }
        loiNode = loiNode->getnext();
    }
    
    cout << "----------------------------------------" << endl;
    cout << "Tong tien phat: " << tongTien << " VND" << endl;
    cout << "========================================" << endl;
}

void Xe :: setloaiXe(const string& lx){
    loaiXe = lx;
}