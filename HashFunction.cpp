#include "HashFunction.h"
#include "Xe.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Motor.h"
using namespace std;

vehicleshash::vehicleshash() : size1(100), size2(100), size3(100) {
    table = new Mylist<Xe>**[size1];
    for (int i = 0; i < size1; ++i) {
        table[i] = new Mylist<Xe>*[size2];
        for (int j = 0; j < size2; ++j)
            table[i][j] = new Mylist<Xe>[size3];
    }
}

vehicleshash::vehicleshash(int size1, int size2, int size3) : size1(size1), size2(size2), size3(size3){
    table = new Mylist<Xe>**[size1];
    for (int i = 0; i < size1; ++i) {
        table[i] = new Mylist<Xe>*[size2];
        for (int j = 0; j < size2; ++j)
            table[i][j] = new Mylist<Xe>[size3];
    }
}

vehicleshash::~vehicleshash() {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++)
            delete[] table[i][j];
        delete[] table[i];
    }
    delete[] table;
}

int vehicleshash::Hash_number(const string& plate) {
    string numberPart = "";
    // Tìm phần số sau dấu '-' cuối cùng
    size_t lastDash = plate.find_last_of('-');
    if (lastDash != string::npos) {
        numberPart = plate.substr(lastDash + 1);
    }
    
    int num = 0;
    for (char c : numberPart) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
    }
    return num % size3;
}

int vehicleshash::Hash_province(const string& plate){
    int num = 0;
    // Lấy 2 số đầu từ biển số (ví dụ: "43-AA-12345" -> 43)
    for (int i = 0; i < 2 && i < plate.length(); i++) {
        if (isdigit(plate[i])) {
            num = num * 10 + (plate[i] - '0');
        }
    }
    return num % size1;
}

int vehicleshash::Hash_type(const string& plate){
    int num = 0;
    // Tìm phần loại xe sau dấu '-' đầu tiên
    size_t firstDash = plate.find('-');
    if (firstDash != string::npos) {
        size_t secondDash = plate.find('-', firstDash + 1);
        if (secondDash != string::npos) {
            string typePart = plate.substr(firstDash + 1, secondDash - firstDash - 1);
            for (char c : typePart) {
                if (isalpha(c)) {
                    num = num * 31 + (toupper(c) - 'A' + 1);
                }
            }
        }
    }
    return num % size2;
}

void vehicleshash::insertToHash(const Xe& a){
    int p = Hash_province(a.getbienSo());
    int t = Hash_type(a.getbienSo());
    int n = Hash_number(a.getbienSo());

    table[p][t][n].push_back(a);
}

Xe* vehicleshash::find(const string& a){
    int p = Hash_province(a);
    int t = Hash_type(a);
    int n = Hash_number(a);

    Node<Xe>* current = table[p][t][n].begin();

    while (current != nullptr){
        if (current->getdata().getbienSo() == a)
            return &(current->refgetdata());
        current = current->getnext();
    }
    return nullptr;
}

// Hàm tạo biển số ngẫu nhiên
string generatePlate(int index) {
    string provinces[] = {"29", "30", "31", "35", "33", "23", "2", "12", "21", "32"};
    string types[] = {"A1", "B2", "C1", "D1"};
    
    // Khởi tạo seed cho random
    static bool seeded = false;
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }
    
    string province = provinces[rand() % 10];
    string type = types[rand() % 4];
    string number = to_string(10000 + (index % 90000));
    return province + "-" + type + "-" + number;
}

// Hàm lưu bảng băm vào file
void saveToFile(vehicleshash& hash, const string& filename) {
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }
    
    for (int i = 0; i < hash.get1(); ++i) {
        for (int j = 0; j < hash.get2(); ++j) {
            for (int k = 0; k < hash.get3(); ++k) {
                Node<Xe>* current = hash.table[i][j][k].begin();
                while (current != nullptr) {
                    out << current->getdata().getbienSo() << endl;
                    // Lưu danh sách lỗi nếu cần
                    Node<Pair>* loi = current->getdata().dsLoi.begin();
                    while (loi != nullptr) {
                        out << loi->getdata().key << "," << loi->getdata().value << endl;
                        loi = loi->getnext();
                    }
                    current = current->getnext();
                }
            }
        }
    }
    
    out.close();
    cout << "Da luu du lieu vao file " << filename << endl;
}