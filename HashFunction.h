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
        int soDaDong;     
        int soChuaDong;   

        thongkeLoi() : tenLoi(""), soLan(0), soDaDong(0), soChuaDong(0){}
        thongkeLoi(const string& a, int b) : tenLoi(a), soLan(b), soDaDong(0), soChuaDong(0){}
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
    int cachedMotorViPham;
    int cachedCarViPham;
    
    long long cachedtienPhat;
    long long cachedtienPhatCar;
    long long cachedtienPhatMotor;
    
    // Thêm: thống kê theo trạng thái đóng phạt
    long long cachedtienDaDong;
    long long cachedtienChuaDong;
    long long cachedtienDaDongMotor;
    long long cachedtienChuaDongMotor;
    long long cachedtienDaDongCar;
    long long cachedtienChuaDongCar;
    
    int cachedsoLoiDaDong;
    int cachedsoLoiChuaDong;
    
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
    void thongkeMotorvsCar();
    void thongketheoLoi();
    void thongkeTheoTrangThai();  // Thêm: hàm thống kê theo trạng thái
};

string generatePlate(int index);
void saveToFile(vehicleshash& hash, const string& filename);

#endif