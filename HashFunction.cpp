#include "HashFunction.h"
#include "Xe.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Motor.h"
using namespace std;



vehicleshash::vehicleshash() : size1(100), size2(100), size3(100) {
    cachedtongsoXe = 0;
    cachedMotor = 0;
    cachedCar = 0;
    cachedtongsoXeViPham = 0;
    cachedtienPhat = 0;

    table = new Mylist<Xe*>**[size1];
    for (int i = 0; i < size1; ++i) {
        table[i] = new Mylist<Xe*>*[size2];
        for (int j = 0; j < size2; ++j)
            table[i][j] = new Mylist<Xe*>[size3];
    }
}

vehicleshash::vehicleshash(int size1, int size2, int size3) : size1(size1), size2(size2), size3(size3){

    cachedtongsoXe = 0;
    cachedMotor = 0;
    cachedCar = 0;
    cachedtongsoXeViPham = 0;
    cachedtienPhat = 0;

    table = new Mylist<Xe*>**[size1];
    for (int i = 0; i < size1; ++i) {
        table[i] = new Mylist<Xe*>*[size2];
        for (int j = 0; j < size2; ++j)
            table[i][j] = new Mylist<Xe*>[size3];
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
    for (int i = 0; i < 2 && i < plate.length(); i++) {
        if (isdigit(plate[i])) {
            num = num * 10 + (plate[i] - '0');
        }
    }
    return num % size1;
}

int vehicleshash::Hash_type(const string& plate){
    int num = 0;
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

void vehicleshash::insertToHash(Xe* a){
    int p = Hash_province(a->getbienSo());
    int t = Hash_type(a->getbienSo());
    int n = Hash_number(a->getbienSo());

    table[p][t][n].push_back(a);

    cachedtongsoXe++;
    string loaiXe = a->getLS();
    if (loaiXe == "Motor") {cachedMotor++;}
        else cachedCar++;
    int soLoi = a->getsoLoi();
        if (soLoi > 0) {
            cachedtongsoXeViPham++;
        }
        
    Node<Pair>* loiNode = a->dsLoi.begin();
    while (loiNode != nullptr) {
        string tenLoi = loiNode->getdata().key;
        
        long long tienPhat = 0;
        Node<Violation>* v = a->danhSachMucPhat.begin();

        while (v != nullptr) {
            if (v->getdata().getLoiViPham() == tenLoi) {
                tienPhat = v->getdata().getMucPhat();
                break;
            }
            v = v->getnext();
        }
        
        
        
        cachedtienPhat += tienPhat; 
        
        bool timThay = false;
        Node<thongkeLoi>* current = cachedthongkeLoi.begin();
        while (current != nullptr) {
            if (current->refgetdata().tenLoi == tenLoi) {
                current->refgetdata().soLan++;
                timThay = true;
                break;
            }
            current = current->getnext();
        }


            if (!timThay) {
                cachedthongkeLoi.push_back(thongkeLoi(tenLoi, 1));
            }
            
            loiNode = loiNode->getnext();
        }

}

Xe* vehicleshash::find(const string& a){
    int p = Hash_province(a);
    int t = Hash_type(a);
    int n = Hash_number(a);

    Node<Xe*>* current = table[p][t][n].begin();

    while (current != nullptr){
        if (current->getdata()->getbienSo() == a)
            return (current->refgetdata());
        current = current->getnext();
    }
    return nullptr;
}

/*string generatePlate(int index) {
    string provinces[] = {"29", "30", "31", "35", "33", "23", "2", "12", "21", "32"};
    string types[] = {"A1","AC","AB", "B2", "C1", "D1"};
    
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
                Node<Xe*>* current = hash.table[i][j][k].begin();
                while (current != nullptr) {
                    out << current->getdata().getbienSo() << endl;
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
}*/

void vehicleshash :: thongke(){
    cout << "      THONG KE TONG QUAN HE THONG      " << endl;
    cout << "========================================" << endl;
        
    cout << "Tong so xe:              " << cachedtongsoXe << endl;
    cout << "  - Xe may (Motor):      " << cachedMotor << endl;
    cout << "  - O to (Car):          " << cachedCar << endl;
    cout << "Tong xe da vi pham:      " << cachedtongsoXeViPham << endl;
        
    int tongSoLoi = 0;
        Node<thongkeLoi>* current = cachedthongkeLoi.begin();
        while (current != nullptr) {
            tongSoLoi += current->getdata().soLan;
            current = current->getnext();
        }

    cout << "Tong so loi vi pham:     " << tongSoLoi << endl;
    cout << "Tong tien phat:          " << cachedtienPhat << " VND" << endl;
}