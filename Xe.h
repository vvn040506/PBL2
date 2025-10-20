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
        static int tongTienPhat ;
        int soLoi;
    public:
        Xe();
        Xe(string&, string&, string&,int); 
        ~Xe();
        static Mylist<Pair> dsMaVung;
        Mylist<Pair> dsLoi;
        Mylist<Violation> danhSachMucPhat;
        
        string getbienSo() const;
        string getTP() const;
        string getLS() const;
        int getsoLoi();
        // int& gettongTienPhat();
        // void dongPhat() const;
        static void docFileMaVung(const string&);
        void themLoi(const string&, const string&) ;
        void dongPhat(const string&, const string&) ;
        void docFileMucPhat(const string&);
        Xe& operator = (const Xe& other);
        virtual void display();
        virtual void truyxuatLoi();
        
        void setThanhPho(const string&);
        void setBienSo(const string&);
        void setloaiXe(const string&);
        int& gettongTienPhat();
        void truyenDSVP(const string&);
};
