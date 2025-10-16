#ifndef HASHFUNCTION_H
#define HASHFUNCTION_H

#include <iostream>
#include <string>
#include "Mylist.h"
#include <fstream>
using namespace std;

class Motor;

class vehicleshash{
private:
    int size1;
    int size2;
    int size3;
public:
    Mylist<Motor> ***table;
    int get1() const { return size1; }
    int get2() const { return size2; }
    int get3() const { return size3; }

    vehicleshash();
    vehicleshash(int size1, int size2, int size3);
    ~vehicleshash();

    int Hash_number(const string& plate);
    int Hash_province(const string& plate);
    int Hash_type(const string& plate);
    
    void insertToHash(const Motor& a);
    Motor* find(const string& a);
};

// Khai báo các hàm non-member
string generatePlate(int index);
void saveToFile(vehicleshash& hash, const string& filename);

#endif