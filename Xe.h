#pragma once
#include"Violation.h"
#include<string.h>
#include"pair.hpp"
#include"Mylist.h"
using namespace std;
class Xe{
    protected:
        string thanhPho;
        string loaiXe;
        string bienSo;
        // bool daDongPhat;
        static int tongTienPhat;
    public:
        Xe();
        Xe(string&, string&, string&); 
        ~Xe();
        static Mylist<Pair> dsMaVung;
        
        string getbienSo() const;
        string getTP() const;
        string getLS() const;
        // int& gettongTienPhat();
        // void dongPhat() const;
        static void docFileMaVung(const string&);
        virtual void themLoi(const string&, const string&, const string&) = 0;
        virtual void dongPhat(const string&, const string&) = 0;
        virtual void docFileMucPhat(const string&) = 0;
        Xe& operator = (const Xe& other);
        virtual void display() = 0;

        void setBienSo(const string&);
        void setThanhPho(const string&);

        void truyenDSVP(const string&);
};
