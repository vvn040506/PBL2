#ifndef MOTOR_H
#define MOTOR_H

#include "Xe.h"
#include "Mylist.h"
#include "pair.hpp"
#include <QString>

class Motor: public Xe {
private:
    static long long tongTienPhat;
public:
    Motor();
    ~Motor();

    long long& gettongTienPhat();
    void display() override;
    QString truyxuatLoi() override;

    friend QDebug operator<<(QDebug debug, Motor& motor);
};

#endif // MOTOR_H
