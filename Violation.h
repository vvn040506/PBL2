#ifndef VIOLATION_H
#define VIOLATION_H

#include <QString>
#include "Mylist.h"

class Violation {
private:
    int id_loi;
    QString loiViPham;
    int mucPhat;
    bool State;
public:
    Mylist<Violation> list;
    Violation(const int&, const QString&, const int&,bool);
    ~Violation();
    void display();
    int getID();
    QString getLoiViPham();
    int getMucPhat();
    void setLoiViPham(const QString& name);
    void setMucPhat(const double& fine);
    bool getState();
    void setState(bool);
    friend void readDSLoi(Mylist<Violation>& list, const QString& filename);
};

#endif // VIOLATION_H
