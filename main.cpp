#include<iostream>
#include<string.h>
#include<limits>
#include"HashTable.h"
#include"HashFunction.h"
#include"Person.h"
#include"Motor.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void NhapTTNguoiVPMoi(HashTable<Person> &ds){
    Person p;
    p.nhapTT();
    ds.insert(p.getCCCD(), p);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    HashTable<Person> dsNguoi(10);
    vehicleshash dsXe(100, 100, 1000);

    cout << "=== NHAP THONG TIN XE THU 1 ===" << endl;
    Motor *myMotor = new Motor();
    myMotor->docFileMaVung("mavung.txt");
    cin >> *myMotor;  
    myMotor->docFileMucPhat("Motor.txt");
    myMotor->themLoi("vuot den do", "11/10/2025");

    cout << "=== NHAP THONG TIN XE THU 2 ===" << endl;
    Motor *myMotor1 = new Motor();
    myMotor1->docFileMaVung("mavung.txt");
    cin >> *myMotor1;  
    myMotor1->docFileMucPhat("Motor.txt");
    myMotor1->themLoi("vuot toc do", "12/10/2025");
    dsXe.insertToHash(*myMotor);
    dsXe.insertToHash(*myMotor1);
    Person p("048206005231", "Tran Le Minh", 100, 100, 1000);
    p.setXe(dsXe);

    try {
        Person *p = &getByCCCD("048206005231", dsNguoi);
        vehicleshash dsXe(34, 100, 1000);
        dsXe.insertToHash(*myMotor);
        
        if (p != nullptr) {
            p->setXe(dsXe);
            dsXe.insertToHash(*myMotor1);
            cout << "Da gan xe cho nguoi: " << p->getTen() << endl;
        }
        
        searchByCCCD("048206005231", dsNguoi);
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
    
    // Giải phóng bộ nhớ
    delete myMotor;
    delete myMotor1;
    
    system("pause"); 
    return 0;
}
// g++ main.cpp Violation.cpp Xe.cpp Motor.cpp -o main.exe
