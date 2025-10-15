#pragma once
#include"Xe.h" 
#include"Mylist.h"
#include"Police.h"
#include<iostream>
#include<string>
#include"pair.hpp"
using namespace std;
class Motor: public Xe{
    private:
        static int tongTienPhat;
    public:
        Motor();
        ~Motor();
        Mylist<Pair> dsLoi;
        Mylist<Violation> danhSachMucPhat;

        int& gettongTienPhat();

        void themLoi(const string&, const string&, const string&) override;
        void dongPhat(const string&, const string&) override;
        void docFileMucPhat(const string&) override;
        void display() override;


        friend istream& operator >> (istream&, Motor&);
        friend ostream& operator << (ostream&, Motor&);
};
