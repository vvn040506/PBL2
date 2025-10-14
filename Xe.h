#pragma once
#include"Violation.h"
#include<string.h>
#include"pair.hpp"
#include"Mylist.h"
using namespace std;
class Xe{
    protected:
        string thanhPho;
        string bienSo;
        // bool daDongPhat;
        static int tongTienPhat;
    public:
        Xe();
        Xe(string&, string&); 
        ~Xe();
        Xe(const Xe& other);
        static Mylist<Pair> dsMaVung;
 
        string getbienSo() const;
        string& getbienSo();
        void setbienSo();
        string getTP() const;
        int& gettongTienPhat() const;
        void dongPhat() const;
        Xe& operator = (const Xe& other);
        static void docFileMaVung(const string&);
        virtual void themLoi(const string&, const string&) = 0;
        virtual void dongPhat(const string&, const string&) = 0;
        virtual void docFileMucPhat(const string&) = 0;
        virtual void display() = 0;
};
