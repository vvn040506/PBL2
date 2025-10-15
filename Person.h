#ifndef PERSON_H
#define PERSON_H
#include"Xe.h"
#include"Mylist.h"
#include"HashFunction.h"
#include"pair.hpp"
#include <iostream>
#include <string>
#include<limits.h>
#include<sstream>
using namespace std;

class Person {
private:
    string cccd;
    string ten;
    string diachi;
    string sdt;
    vehicleshash hash_xe;
public:
    Person() : cccd(""), ten(""),  hash_xe(34, 100, 1000) {}
    Person(const string &cccd, const string &ten, const string& sdt, const string& d) 
        : cccd(cccd), ten(ten), sdt(sdt), diachi(d), hash_xe(100, 100, 1000){ 
    }

    string getCCCD() const { return cccd; }
    string getTen() const { return ten; }

    void setCCCD(const string& newCCCD) { cccd = newCCCD; }
    void setTen(const string& newTen) { ten = newTen; }
    void setDiaChi(const string& diaChi) {diachi = diaChi; }
    void setSdt(const string& s) {sdt = s;} 

    bool operator==(const Person& other) const {
        return this->cccd == other.cccd;
    }

    bool operator!=(const Person& other) const {
        return this->cccd != other.cccd;
    }

    friend istream& operator >> (istream& in, Person& p){
    cout << "Nhap cccd: ";
    getline(in >> ws, p.cccd);  // ws = bỏ khoảng trắng + newline thừa

    cout << "Nhap ten nguoi vp: ";
    getline(in, p.ten);
    return in;
    }

    void nhapTT(){
        cout << "Nhap cccd: "; cin >> cccd;
        cout << "Nhap ten nguoi vp: "; 
        cin.ignore();
        getline(cin, ten);
    }

    friend ostream& operator<<(ostream& os, const Person& p) {
        os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << ", Sdt: " << p.sdt << ", Dia chi: " << p.diachi << "]" << endl;
        os << "Danh sach xe vi pham:" << endl;
        
        // Duyệt qua tất cả các bucket trong hash table
        for (int i = 0; i < p.hash_xe.get1(); ++i) {
            for (int j = 0; j < p.hash_xe.get2(); ++j) {
                for (int k = 0; k < p.hash_xe.get3(); ++k) {
                    // Lấy danh sách xe tại bucket [i][j][k]
                    Node<Motor>* current = p.hash_xe.table[i][j][k].begin();
                    while (current != nullptr) {
                        os << "  - ";
                        current->getdata().display();  // Hiển thị thông tin xe
                        current = current->getnext();
                    }
                }
            }
        }
        return os;
    }

    void setXe(vehicleshash& xe){
        hash_xe = xe; 
    }

    // Hoặc nếu muốn copy dữ liệu
    // void setXe(const vehicleshash& xe){
    //     hash_xe = xe;
    // }

    vehicleshash& getXe(){
        return hash_xe;
    }

    vehicleshash* getXePtr(){
        return &hash_xe;
    }
    static void phanTichBienSo(const string& bienSo, Motor& motor) {
        size_t dash1 = bienSo.find('-');
        size_t dash2 = bienSo.find('-', dash1 + 1);
        
        if (dash1 != string::npos && dash2 != string::npos) {
            string maTP = bienSo.substr(0, dash1);
            string loaiXe = bienSo.substr(dash1 + 1, dash2 - dash1 - 1);
            
            motor.setBienSo(bienSo);
            
            // Tìm tên thành phố từ mã vùng
            for (Node<Pair>* x = Xe::dsMaVung.begin(); x != nullptr; x = x->getnext()) {
                if (x->getdata().value == maTP) {
                    motor.setThanhPho(x->getdata().key);
                    break;
                }
            }
        }
    }
    static void docFileDanhSach(const string& filename, HashTable<Person>& dsNguoi) {
    try {
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
            cout << "\n--- Xu ly dong " << lineCount << " ---" << endl;
            cout << "Noi dung: " << line << endl;
            
            if (line.empty()) {
                cout << "-> Dong rong, bo qua" << endl;
                continue;
            }

            stringstream ss(line);
            string token;
            Mylist<string> tokens;
            
            // Tách tất cả tokens
            while (ss >> token) {
                tokens.push_back(token);
            }

            if (tokens.size() < 5) {
                cout << "-> Khong du tokens, bo qua" << endl;
                continue;
            }

            // Lấy CCCD đầu tiên
            string cccd = tokens.begin()->getdata();
            cout << "CCCD: " << cccd << endl;
            tokens.pop_front();

            Mylist<Pair> danhSachXe;
            string ten = "", sdt = "", diaChi = "";

            // Đọc các cặp loại xe + biển số
            Node<string>* current = tokens.begin();
            bool isReadingVehicles = true;
            
            while (current != nullptr && isReadingVehicles) {
                string loaiXe = current->getdata();
                current = current->getnext();
                
                if (current != nullptr && (loaiXe == "Motor" || loaiXe == "Car")) {
                    string bienSo = current->getdata();
                    cout << "Xe: " << loaiXe << " - " << bienSo << endl;
                    danhSachXe.push_back(Pair(loaiXe, bienSo));
                    current = current->getnext();
                } else {
                    // Bắt đầu phần thông tin cá nhân
                    ten = loaiXe;  // Từ này là tên đầu tiên
                    isReadingVehicles = false;
                    cout << "Bat dau thong tin ca nhan" << endl;
                }
            }

            // Đọc thông tin cá nhân
            if (current != nullptr) {
                // Đọc tiếp phần còn lại của tên
                string temp = ten;
                while (current != nullptr) {
                    string nextToken = current->getdata();
                    // Kiểm tra nếu là số điện thoại (chỉ chứa số)
                    bool isPhone = true;
                    for (char c : nextToken) {
                        if (!isdigit(c)) {
                            isPhone = false;
                            break;
                        }
                    }
                    
                    if (isPhone && sdt.empty()) {
                        sdt = nextToken;
                        cout << "SDT: " << sdt << endl;
                    } else if (!sdt.empty()) {
                        // Phần còn lại là địa chỉ
                        if (diaChi.empty()) {
                            diaChi = nextToken;
                        } else {
                            diaChi += " " + nextToken;
                        }
                    } else {
                        // Tiếp tục đọc tên
                        if (temp.empty()) {
                            temp = nextToken;
                        } else {
                            temp += " " + nextToken;
                        }
                    }
                    current = current->getnext();
                }
                ten = temp;
            }

            cout << "Thong tin ca nhan:" << endl;
            cout << "  Ten: " << ten << endl;
            cout << "  SDT: " << sdt << endl;
            cout << "  Dia chi: " << diaChi << endl;

            // Tạo Person và thêm xe
            if (!cccd.empty() && !ten.empty()) {
                cout << "Tao Person: " << cccd << " - " << ten << endl;
                Person p(cccd, ten, sdt, diaChi);
                
                // Thêm các xe vào Person
                int xeCount = 0;
                for (Node<Pair>* xeNode = danhSachXe.begin(); xeNode != nullptr; xeNode = xeNode->getnext()) {
                    Pair xePair = xeNode->getdata();
                    if (xePair.key == "Motor") {
                        cout << "Them Motor: " << xePair.value << endl;
                        Motor motor;
                        motor.setBienSo(xePair.value);
                        // Phân tích biển số để lấy thông tin
                        phanTichBienSo(xePair.value, motor);
                        p.getXe().insertToHash(motor);
                        xeCount++;
                    }
                }
                
                // Thêm Person vào HashTable
                cout << "Them vao HashTable: " << cccd << " - " << ten << " - " << xeCount << " xe" << endl;
                dsNguoi.insert(cccd, p);
                cout << "-> THEM THANH CONG" << endl;
            } else {
                cout << "-> LOI: Thieu thong tin ca nhan" << endl;
            }
        }
        
        cout << "\n=== KET THUC DOC FILE ===" << endl;
        cout << "Tong so dong da doc: " << lineCount << endl;
        fs.close();
    }
    catch (const exception& e) {
        cout << "LOI NGHIEM TRONG trong docFileDanhSach: " << e.what() << endl;
    }
}
};

#endif
