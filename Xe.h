#ifndef XE_H
#define XE_H

#include "Violation.h"
#include "pair.hpp"
#include "Mylist.h"
#include <QString>

class Xe {
protected:
    QString thanhPho;
    QString loaiXe;
    QString bienSo;
    QString Owner_id;
    static int tongTienPhat;
    int soLoi;
public:
    Xe();
    Xe(QString &id, QString& tp, QString& ls, QString& bs, int&);
    ~Xe();
    static Mylist<Pair> dsMaVung;
    Mylist<Pair> dsLoi;
    Mylist<Violation> danhSachMucPhat;

    QString getbienSo() const;
    QString getTP() const;
    QString getLS() const;
    QString getID() const;
    int getsoLoi();
    static void docFileMaVung(const QString& filename);
    void themLoi(const QString& loiVP, const QString& ngayVP);
    void dongPhat(const QString& loiVP, const QString& ngayVP);
    void docFileMucPhat(const QString& tenFile);
    Xe& operator=(const Xe& other);
    virtual void display();
    virtual QString truyxuatLoi();
    QString truyxuatLoi_TomTat(Mylist<Violation>& masterViolationList);
    long long tinhTongTienPhatChuaDong(Mylist<Violation>& masterViolationList);

    void setThanhPho(const QString& tp);
    void setBienSo(const QString& bs);
    void setloaiXe(const QString& lx);
    void setOwner(const QString& cccd);
    int& gettongTienPhat();
    void truyenDSVP(const QString& filename);
    void setDanhSachMucPhat(const Mylist<Violation>& ds) {
        danhSachMucPhat = ds;
    }

    Mylist<Violation> getDanhSachMucPhat() const {
        return danhSachMucPhat;
    }
};

#endif // XE_H
