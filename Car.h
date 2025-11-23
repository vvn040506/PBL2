#ifndef CAR_H
#define CAR_H

#include "Xe.h"
#include "Mylist.h"
#include "pair.hpp"
#include <QString>

class Car: public Xe {
private:
    static long long tongTienPhat;
public:
    Car();
    ~Car();

    long long& gettongTienPhat();
    QString truyxuatLoi() override;
    void display() override;

    friend QDebug operator<<(QDebug debug, Car& car);
};

#endif // CAR_H
