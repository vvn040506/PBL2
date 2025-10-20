#pragma once
#include "Xe.h" 
#include "Mylist.h"
#include "pair.hpp"
#include <iostream>
#include <string>
using namespace std;
class Motor: public Xe{
    private:
        static long long tongTienPhat;
    public:
        Motor();
        ~Motor();
        
        long long& gettongTienPhat();
        void display() override;
        void truyxuatLoi() override;


        friend istream& operator >> (istream&, Motor&);
        friend ostream& operator << (ostream&, Motor&);
};

#include "Police.h"
