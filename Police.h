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
        string pass;
    public:
        static HashTable<Pair>* dsPolice;
        Police();
        Police(const string&,const string&);
        ~Police();
        string getID();
        static void showPoliceWork(const string&);
        static void addPoliceWork(const string& id_police, const string& bienso, const string& ngay);
        static Mylist<Pair> getPoliceWork(const string& id);
        
        void menu() override;
        void themloiXe(vehicleshash* Hash);
        void dongPhat(vehicleshash* Hash);
        void themxeMoi(vehicleshash* Hash);
        bool dangNhap(const string& i, const string& p);
        
};
void themXeVaoPerson(const string& cccd, const string& bienSo, const string& ten, 
                     const string& sdt, const string& diachi, int loai);
Xe* taoXeMoi(const string& bienSo, int loai);
void capNhatFileCCCD(const string& cccd, const string& bienSo);
void capNhatFileBienSo(Xe* xe);                   

#include "Person.h"