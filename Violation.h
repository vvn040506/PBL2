//Vi phạm
#pragma once
#include<iostream>
#include<string>
#include"Mylist.h"
using namespace std;
class Violation{
    private:
        int id_loi;
        string loiViPham; // lỗi vi phạm
        int mucPhat; // mức phạt tiền
    public:
        Mylist<Violation> list;
        Violation(const int&, const string&, const int&); 
        ~Violation();
        void display();
        int getID();
        string getLoiViPham() ;
        int getMucPhat();
        void setLoiViPham(const string&);
        void setMucPhat(const double&);
        friend void readDSLoi(Mylist<Violation> &, const string&);
};
