#include<iostream>
#include<string.h>
#include<limits>
#include"HashTable.h"
#include"Person.h"
#include"Motor.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void NhapTTNguoiVPMoi(HashTable<Person> &ds){
    Person p;
    cin >> p;
    ds.insert(p.getCCCD(), p);
}

int main() {
    HashTable<Person> dsNguoi(10);
    NhapTTNguoiVPMoi(dsNguoi);
    Person *p = &getByCCCD("048206005231", dsNguoi);
    Mylist<Xe*> dsXe;   
    Motor *myMotor = new Motor();
    myMotor->docFileMaVung("mavung.txt");
    cin >> *myMotor;
    myMotor->docFileMucPhat("Motor.txt");
    myMotor->themLoi("vuot den do", "11/10/2025");
    dsXe.push_back(myMotor);
    clearInputBuffer();
    Motor *myMotor1 = new Motor();
    myMotor1->docFileMaVung("mavung.txt");
    cin >> *myMotor1;
    myMotor1->docFileMucPhat("Motor.txt");
    myMotor1->themLoi("vuot toc do", "12/10/2025");
    p->setXe(dsXe);
    dsXe.push_back(myMotor1);
    searchByCCCD("048206005231", dsNguoi);
    system("pause");
    return 0;
}
// g++ main.cpp Violation.cpp Xe.cpp Motor.cpp -o main.exe*/
