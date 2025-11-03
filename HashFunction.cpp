#include "HashFunction.h"
#include "Xe.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Motor.h"
#include "main1.h"
using namespace std;

vehicleshash::vehicleshash() : size1(100), size2(100), size3(100) {
    cachedtongsoXe = 0;
    cachedMotor = 0;
    cachedCar = 0;
    cachedMotorViPham = 0;
    cachedCarViPham = 0;
    cachedtongsoXeViPham = 0;
    cachedtienPhat = 0;
    cachedtienPhatMotor = 0;
    cachedtienPhatCar = 0;
    
    // Khởi tạo thêm
    cachedtienDaDong = 0;
    cachedtienChuaDong = 0;
    cachedtienDaDongMotor = 0;
    cachedtienChuaDongMotor = 0;
    cachedtienDaDongCar = 0;
    cachedtienChuaDongCar = 0;
    cachedsoLoiDaDong = 0;
    cachedsoLoiChuaDong = 0;

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
    cachedMotorViPham = 0;
    cachedCarViPham = 0;
    cachedtienPhat = 0;
    cachedtienPhatMotor = 0;
    cachedtienPhatCar = 0;
    
    // Khởi tạo thêm
    cachedtienDaDong = 0;
    cachedtienChuaDong = 0;
    cachedtienDaDongMotor = 0;
    cachedtienChuaDongMotor = 0;
    cachedtienDaDongCar = 0;
    cachedtienChuaDongCar = 0;
    cachedsoLoiDaDong = 0;
    cachedsoLoiChuaDong = 0;

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
    if (loaiXe == "Motor") cachedMotor++;
        else cachedCar++;
    
    if (a->dsLoi.size() > 0) {  
        cachedtongsoXeViPham++;
    
        if (loaiXe == "Motor") {
            cachedMotorViPham++;
        } else {
            cachedCarViPham++;
        }   
    }   
        
    Node<Pair>* loiNode = a->dsLoi.begin();
    while (loiNode != nullptr) {
        string tenLoi = loiNode->getdata().key;
        bool trangThaiDong = loiNode->getdata().State;  // Lấy trạng thái đóng phạt
        
        long long tienPhat = 0;
        Node<Violation>* v = a->danhSachMucPhat.begin();

        while (v != nullptr) {
            if (v->getdata().getLoiViPham() == tenLoi) {
                tienPhat = v->getdata().getMucPhat();
                break;
            }
            v = v->getnext();
        }
        
        // Cập nhật tổng tiền phạt
        cachedtienPhat += tienPhat;
        if (loaiXe == "Motor") {
            cachedtienPhatMotor += tienPhat;
        } else {
            cachedtienPhatCar += tienPhat;
        }
        
        // Cập nhật theo trạng thái đóng phạt
        if (trangThaiDong) {
            cachedtienDaDong += tienPhat;
            cachedsoLoiDaDong++;
            if (loaiXe == "Motor") {
                cachedtienDaDongMotor += tienPhat;
            } else {
                cachedtienDaDongCar += tienPhat;
            }
        } else {
            cachedtienChuaDong += tienPhat;
            cachedsoLoiChuaDong++;
            if (loaiXe == "Motor") {
                cachedtienChuaDongMotor += tienPhat;
            } else {
                cachedtienChuaDongCar += tienPhat;
            }
        }
        
        // Cập nhật thống kê lỗi
        bool timThay = false;
        Node<thongkeLoi>* current = cachedthongkeLoi.begin();
        while (current != nullptr) {
            if (current->refgetdata().tenLoi == tenLoi) {
                current->refgetdata().soLan++;
                if (trangThaiDong) {
                    current->refgetdata().soDaDong++;
                } else {
                    current->refgetdata().soChuaDong++;
                }
                timThay = true;
                break;
            }
            current = current->getnext();
        }

        if (!timThay) {
            thongkeLoi tkLoi(tenLoi, 1);
            if (trangThaiDong) {
                tkLoi.soDaDong = 1;
                tkLoi.soChuaDong = 0;
            } else {
                tkLoi.soDaDong = 0;
                tkLoi.soChuaDong = 1;
            }
            cachedthongkeLoi.push_back(tkLoi);
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

void vehicleshash::thongke(){
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
    cout << "  - Da dong phat:        " << cachedsoLoiDaDong << " loi" << endl;
    cout << "  - Chua dong phat:      " << cachedsoLoiChuaDong << " loi" << endl;
    cout << "Tong tien phat:          " << cachedtienPhat << " VND" << endl;
    cout << "  - Da thu:              " << cachedtienDaDong << " VND" << endl;
    cout << "  - Chua thu:            " << cachedtienChuaDong << " VND" << endl;
    pause();
}

void vehicleshash::thongkeMotorvsCar(){
    cout << "\n========================================" << endl;
    cout << "        THONG KE MOTOR vs CAR           " << endl;
    cout << "========================================" << endl;
    
    cout << "\nSO LUONG XE:" << endl;
    cout << "  Motor: " << cachedMotor << " xe" << endl;
    cout << "  Car:   " << cachedCar << " xe" << endl;
    
    cout << "\nXE VI PHAM:" << endl;
    cout << "  Motor: " << cachedMotorViPham << " / " << cachedMotor << " xe" << endl;
    cout << "  Car:   " << cachedCarViPham << " / " << cachedCar << " xe" << endl;
    
    cout << "\nTIEN PHAT:" << endl;
    cout << "  Motor: " << cachedtienPhatMotor << " VND" << endl;
    cout << "    + Da thu:  " << cachedtienDaDongMotor << " VND" << endl;
    cout << "    + Chua thu: " << cachedtienChuaDongMotor << " VND" << endl;
    cout << "  Car:   " << cachedtienPhatCar << " VND" << endl;
    cout << "    + Da thu:  " << cachedtienDaDongCar << " VND" << endl;
    cout << "    + Chua thu: " << cachedtienChuaDongCar << " VND" << endl;
    cout << "  Tong:  " << cachedtienPhat << " VND" << endl;
    
    cout << "========================================" << endl;
}

void vehicleshash::thongketheoLoi(){
    cout << "\n========================================" << endl;
    cout << "      THONG KE THEO LOI VI PHAM        " << endl;
    cout << "========================================" << endl;
    
    if (cachedthongkeLoi.size() == 0) {
        cout << "\nChua co loi vi pham nao!" << endl;
        cout << "========================================" << endl;
        return;
    }
    
    int tongSoLoi = 0;
    Node<thongkeLoi>* current = cachedthongkeLoi.begin();
    while (current != nullptr) {
        tongSoLoi += current->getdata().soLan;
        current = current->getnext();
    }
    
    cout << "\nTong so loi vi pham: " << tongSoLoi << endl;
    cout << "  - Da dong phat: " << cachedsoLoiDaDong << " loi" << endl;
    cout << "  - Chua dong phat: " << cachedsoLoiChuaDong << " loi" << endl;
    cout << "\nChi tiet:" << endl;
    
    current = cachedthongkeLoi.begin();
    while (current != nullptr) {
        cout << "  - " << current->getdata().tenLoi 
             << ": " << current->getdata().soLan << " lan";
        cout << " (Da dong: " << current->getdata().soDaDong 
             << ", Chua dong: " << current->getdata().soChuaDong << ")" << endl;
        current = current->getnext();
    }
    
    cout << "========================================" << endl;
}

void vehicleshash::thongkeTheoTrangThai(){
    cout << "\n========================================" << endl;
    cout << "    THONG KE THEO TRANG THAI DONG PHAT " << endl;
    cout << "========================================" << endl;
    
    cout << "\nDA DONG PHAT:" << endl;
    cout << "  So loi: " << cachedsoLoiDaDong << endl;
    cout << "  Tong tien thu: " << cachedtienDaDong << " VND" << endl;
    cout << "    + Motor: " << cachedtienDaDongMotor << " VND" << endl;
    cout << "    + Car:   " << cachedtienDaDongCar << " VND" << endl;
    
    cout << "\nCHUA DONG PHAT:" << endl;
    cout << "  So loi: " << cachedsoLoiChuaDong << endl;
    cout << "  Tong tien can thu: " << cachedtienChuaDong << " VND" << endl;
    cout << "    + Motor: " << cachedtienChuaDongMotor << " VND" << endl;
    cout << "    + Car:   " << cachedtienChuaDongCar << " VND" << endl;
    
    double tiLeDaDong = (cachedtienPhat > 0) ? 
        (double)cachedtienDaDong / cachedtienPhat * 100 : 0;
    cout << "\nTi le thu phat: " << tiLeDaDong << "%" << endl;
    
    cout << "========================================" << endl;
}