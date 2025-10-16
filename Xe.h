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
        Mylist<Pair> dsLoi;
        Mylist<Violation> danhSachMucPhat;
        
        string getbienSo() const;
        string getTP() const;
        string getLS() const;
        // int& gettongTienPhat();
        // void dongPhat() const;
        static void docFileMaVung(const string&);
        virtual void themLoi(const string&, const string&) ;
        virtual void dongPhat(const string&, const string&) ;
        virtual void docFileMucPhat(const string&);
        Xe& operator = (const Xe& other);
        virtual void display();

        void setBienSo(const string&);
        void setThanhPho(const string&);

        void truyenDSVP(const string&);
};
