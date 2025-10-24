#pragma once
#include"HashTable.h"
#include"Person.h"
#include "pair.hpp"
#include <iostream>
#include <string>
#include "HashFunction.h"
#include "Xe.h"

using namespace std;

//class Person;
//template<typename T> class HashTable;

class Police: public Person{
    private:
        string id_police;
    public:
        static HashTable<Pair>* dsPolice;
        Police();
        Police(const string&);
        ~Police();
        string getID();
        static void showPoliceWork(const string&);
        static void addPoliceWork(const string& id_police, const string& bienso, const string& ngay);
        static Mylist<Pair> getPoliceWork(const string& id);
        
        void menu();
        void themloiXe(vehicleshash* Hash);
        void xoaloiXe(vehicleshash* Hash);
        void themxeMoi(vehicleshash* Hash);
        
};

#include "Person.h"