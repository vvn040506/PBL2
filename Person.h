#ifndef PERSON_H
#define PERSON_H

#include "HashFunction.h"
#include "HashTable.h"
#include <QString>

class Xe;

template<typename T> class HashTable;

class Person {
private:
    QString cccd;
    QString ten;
    QString sdt;
    QString diachi;


public:
    Person();
    virtual ~Person();
    Person(const Person& other);
    Person(const QString& cccd, const QString& ten, const QString& sdt, const QString& d);
    vehicleshash* hash_xe;
    HashTable<Person>* hash_nguoi;

    QString getCCCD() const { return cccd; }
    QString& getCCCD() { return cccd; }
    QString getTen() const { return ten; }
    QString getDiaChi() const { return diachi; }
    QString getSdt() const { return sdt; }

    void setCCCD(const QString& newCCCD) { cccd = newCCCD; }
    void setTen(const QString& newTen) { ten = newTen; }
    void setDiaChi(const QString& diaChi) { diachi = diaChi; }
    void setSdt(const QString& s) { sdt = s; }

    Person& operator=(const Person& other);
    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;

    friend QDebug operator<<(QDebug debug, const Person& p);

    void nhapTT();
    void setXe(vehicleshash* xe);
    vehicleshash* getXe();
    void timXe(vehicleshash* hash);

    static void phanTichBienSo(const QString& bienSo, Xe& xe);
    static void docFileDanhSach(const QString& filename, HashTable<Person>& dsNguoi);
    void truyvanCCCD(HashTable<Person>* hash);
    // virtual void menu();
};

#endif // PERSON_H
