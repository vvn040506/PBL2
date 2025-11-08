#ifndef MAIN1_H
#define MAIN1_H

#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "Motor.h"
#include "Car.h"
#include "HashFunction.h"
#include "Person.h"
#include "Citizen.h"
#include "HashTable.h"
#include "DataGenerator.h"

using namespace std;

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern Mylist<Violation> dsMucPhatMotor;
extern Mylist<Violation> dsMucPhatCar;


void pause();
void khoiTaoHeThong();
void menuHome();
void menuCongAn();
void menuNguoiDan();
string ghepFile(const string&, const string&);


#endif