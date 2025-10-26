#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H

#include <iostream>
#include <string>
#include "Mylist.h"
#include <fstream>

using namespace std;

class Xe;

class thongkeLoi{
    public:
        string tenLoi;
        int soLan;

        thongkeLoi() : tenLoi(""), soLan(0){}
        thongkeLoi(const string& a, int b) : tenLoi(a),soLan(b){}
        ~thongkeLoi(){}

        bool operator == (const thongkeLoi& tk) const {
            return tenLoi == tk.tenLoi;
        }
};

class vehicleshash{
private:
    int size1;
    int size2;
    int size3;

    int cachedtongsoXe;
    int cachedtongsoXeViPham;
    int cachedMotor;
    int cachedCar;
    long long cachedtienPhat;
    Mylist <thongkeLoi> cachedthongkeLoi;
public:
    Mylist<Xe*> ***table;
    int get1() const { return size1; }
    int get2() const { return size2; }
    int get3() const { return size3; }

    vehicleshash();
    vehicleshash(int size1, int size2, int size3);
    ~vehicleshash();

    int Hash_number(const string& plate);
    int Hash_province(const string& plate);
    int Hash_type(const string& plate);
    
    void insertToHash(Xe* a);
    Xe* find(const string& a);
    void thongke();
};

// Khai báo các hàm non-member
string generatePlate(int index);
void saveToFile(vehicleshash& hash, const string& filename);


#endif