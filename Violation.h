//Vi phạm
#pragma once
#include<iostream>
#include<string>
#include"Mylist.h"
using namespace std;
class Violation{
    private:
        int id_loi;
        string loiViPham;
        int mucPhat;
        bool State;
    public:
        Mylist<Violation> list;
        Violation(const int&, const string&, const int&,bool); 
        ~Violation();
        void display();
        int getID();
        string getLoiViPham() ;
        int getMucPhat();
        bool getState();
        void setState(bool);

        void setLoiViPham(const string&);
        void setMucPhat(const double&);
        friend void readDSLoi(Mylist<Violation> &, const string&);
        
};
