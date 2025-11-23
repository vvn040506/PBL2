#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H

#include <QString>
#include "Mylist.h"
#include <QFile>

class Xe;

class thongkeLoi{
public:
    QString tenLoi;
    int soLan;
    int soDaDong;
    int soChuaDong;

    thongkeLoi() : tenLoi(""), soLan(0), soDaDong(0), soChuaDong(0){}
    thongkeLoi(const QString& a, int b) : tenLoi(a), soLan(b), soDaDong(0), soChuaDong(0){}
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

public:
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

    Mylist<Xe*> ***table;
    int get1() const { return size1; }
    int get2() const { return size2; }
    int get3() const { return size3; }

    vehicleshash();
    vehicleshash(int size1, int size2, int size3);
    ~vehicleshash();

    int Hash_number(const QString& plate);
    int Hash_province(const QString& plate);
    int Hash_type(const QString& plate);

    void insertToHash(Xe* a);
    Xe* find(const QString& a);
    void thongke();
    void thongkeMotorvsCar();
    void thongketheoLoi();
    void thongkeTheoTrangThai();
};

QString generatePlate(int index);
void saveToFile(vehicleshash& hash, const QString& filename);

#endif // HASHFUNCTION_H
