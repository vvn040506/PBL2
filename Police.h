#ifndef POLICE_H
#define POLICE_H

#include "Violation.h"
#include "Mylist.h"
#include "HashTable.h"
#include "Person.h"
#include "pair.hpp"
#include "HashFunction.h"
#include "Xe.h"
#include <QLineEdit>
#include <QString>

class Police : public Person {
private:
    QString id_police;
    QString pass;
    QLineEdit* createStyledLineEdit(const QString& placeholder);
public:
    static HashTable<Pair>* dsPolice;
    Police();
    Police(const QString&, const QString&);
    ~Police();
    QString getID();
    static void showPoliceWork(const QString& id);
    static void addPoliceWork(const QString& id_police, const QString& bienso, const QString& ngay);
    static Mylist<Pair> getPoliceWork(const QString& id);

    // void menu() override;
    void themloiXe(vehicleshash* Hash);
    void xoaloiXe(vehicleshash* Hash);
    void themxeMoi(vehicleshash* Hash);
    bool dangNhap(const QString& i, const QString& p);
};

void themXeVaoPerson(const QString& cccd, const QString& bienSo, const QString& ten,
                     const QString& sdt, const QString& diachi, int loai);
Xe* taoXeMoi(const QString& bienSo, int loai);
void capNhatFileBienSo(Xe* xe);
void capNhatFileCCCD(const QString& cccd, const QString& bienSo);


#endif // POLICE_H
