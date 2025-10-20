#pragma once
#include "Xe.h" 
#include "Mylist.h"
#include "pair.hpp"
#include <iostream>
#include <string>
using namespace std;

class Car: public Xe{
    private:
        static long long tongTienPhat;
    public:
        Car();
        ~Car();
        
        long long& gettongTienPhat();
        void truyxuatLoi() override;
        void display() override;


        friend istream& operator >> (istream&, Car&);
        friend ostream& operator << (ostream&, Car&);
};

#include "Police.h"

