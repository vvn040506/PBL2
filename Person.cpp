#include "Person.h"
#include "Motor.h"
#include "HashFunction.h"
#include "HashTable.h"
#include "Xe.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Constructor implementations
Person::Person() : cccd(""), ten(""){
    hash_xe = new vehicleshash(10, 10, 100);
}

Person::Person(const string &cccd, const string &ten, const string& sdt, const string& d) 
    : cccd(cccd), ten(ten), sdt(sdt), diachi(d) { 
            hash_xe = new vehicleshash(10, 10, 100);

}

// Operator implementations
bool Person::operator==(const Person& other) const {
    return this->cccd == other.cccd;
}

bool Person::operator!=(const Person& other) const {
    return this->cccd != other.cccd;
}

// Friend function implementations
istream& operator >> (istream& in, Person& p){
    cout << "Nhap cccd: ";
    getline(in >> ws, p.cccd);  

    cout << "Nhap ten nguoi vp: ";
    getline(in, p.ten);
    return in;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << ", Sdt: " << p.sdt << ", Dia chi: " << p.diachi << "]" << endl;
    os << "Danh sach xe vi pham:" << endl;
    
    for (int i = 0; i < p.hash_xe->get1(); ++i) {
        for (int j = 0; j < p.hash_xe->get2(); ++j) {
            for (int k = 0; k < p.hash_xe->get3(); ++k) {
                
                Node<Xe*>* current = p.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    os << "  - ";
                    current->getdata()->display();  
                    current = current->getnext();
                }
            }
        }
    }
    return os;
}

void Person::nhapTT(){
    cout << "Nhap cccd: "; cin >> cccd;
    cout << "Nhap ten nguoi vp: "; 
    cin.ignore();
    getline(cin, ten);
}

void Person::setXe(vehicleshash* xe){
    if (hash_xe != nullptr) {
        delete hash_xe;
    }
    hash_xe = xe; 
}

vehicleshash* Person::getXe(){
    return hash_xe;
}

void Person::phanTichBienSo(const string& bienSo, Xe& Xe) {
    size_t dash1 = bienSo.find('-');
    size_t dash2 = bienSo.find('-', dash1 + 1);
    
    if (dash1 != string::npos && dash2 != string::npos) {
        string maTP = bienSo.substr(0, dash1);
        string loaiXe = bienSo.substr(dash1 + 1, dash2 - dash1 - 1);
        
        Xe.setBienSo(bienSo);
        
        for (Node<Pair>* x = Xe::dsMaVung.begin(); x != nullptr; x = x->getnext()) {
            if (x->getdata().value == maTP) {
                Xe.setThanhPho(x->getdata().key);
                break;
            }
        }
    }
}

void Person::docFileDanhSach(const string& filename, HashTable<Person>& dsNguoi) {
    ifstream fs(filename);
    if (!fs.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }

    cout << "Mo file thanh cong: " << filename << endl;
    string line;
    int lineCount = 0;

    while (getline(fs, line)) {
        lineCount++;
        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        Mylist<string> tokens;
        while (ss >> token) tokens.push_back(token);

        if (tokens.IsEmpty()) continue;

        cout << "\n--- Dong " << lineCount << " ---" << endl;

        string cccd = tokens.begin()->getdata();
        tokens.pop_front();
        cout << "CCCD: " << cccd << endl;

        Mylist<Pair> danhSachXe;
        Node<string>* cur = tokens.begin();
        while (cur != nullptr) {
            string loai = cur->getdata();
            Node<string>* next = cur->getnext();

            if ((loai == "Motor" || loai == "Car") && next != nullptr) {
                string bienSo = next->getdata();
                danhSachXe.push_back(Pair(loai, bienSo));
                cur = next->getnext();
            } else {
                break;
            }
        }

        Mylist<string> thongTinConLai;
        while (cur != nullptr) {
            thongTinConLai.push_back(cur->getdata());
            cur = cur->getnext();
        }

        if (thongTinConLai.size() < 3) {
            cout << "-> Thieu thong tin, bo qua dong nay\n";
            continue;
        }

        int n = thongTinConLai.size();
        Node<string>* p = thongTinConLai.begin();
        string arr[100];
        int idx = 0;
        while (p != nullptr && idx < 100) {
            arr[idx++] = p->getdata();
            p = p->getnext();
        }

        int posSDT = -1;
        for (int i = idx - 1; i >= 0; --i) {
            bool allDigit = true;
            for (char c : arr[i]) {
                if (!isdigit(c)) { allDigit = false; break; }
            }
            if (allDigit) { posSDT = i; break; }
        }

        if (posSDT == -1) {
            cout << "-> Khong tim thay SDT, bo qua dong nay\n";
            continue;
        }

        string ten = "";
        for (int i = 0; i < posSDT; ++i) {
            if (!ten.empty()) ten += " ";
            ten += arr[i];
        }

        string sdt = arr[posSDT];

        string diachi = "";
        for (int i = posSDT + 1; i < idx; ++i) {
            if (!diachi.empty()) diachi += " ";
            diachi += arr[i];
        }

        cout << "Ten: " << ten << "\nSDT: " << sdt << "\nDia chi: " << diachi << endl;

        Person pnew(cccd, ten, sdt, diachi);

        for (Node<Pair>* x = danhSachXe.begin(); x != danhSachXe.end(); x = x->getnext()) {
            if (x->getdata().key == "Motor") {
                Motor m;
                m.setBienSo(x->getdata().value);
                phanTichBienSo(x->getdata().value, m);
                pnew.getXe()->insertToHash(&m);
            }
        }

        dsNguoi.insert(cccd, pnew);
        cout << "-> Da them " << ten << " vao HashTable" << endl;
    }

    cout << "\n=== KET THUC DOC FILE ===" << endl;
    fs.close();
}

Person& getByCCCD(const string& cccd, HashTable<Person>& ds) {
    int pos = ds.hash_function(cccd);
    
    Node<Person>* x = ds.buckets[pos].begin();
    while (x != nullptr) {
        if (x->getdata().getCCCD() == cccd) {
            return x->refgetdata();
        }
        x = x->getnext();
    }
    
    throw runtime_error("Khong tim thay CCCD " + cccd);
}