#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QString>
#include <QTime>
#include "Motor.h"
#include "Car.h"
#include "HashFunction.h"
#include "Mylist.h"
#include "Menu.h"

using namespace std;

class DataGenerator {
public:
    // Sinh biển số ngẫu nhiên
    static QString generateBienSo();

    // Sinh ngày ngẫu nhiên
    static QString generateNgay();

    // Sinh số CCCD ngẫu nhiên
    static QString generateCCCD();

    // Sinh số điện thoại ngẫu nhiên
    static QString generateSDT();

    // Sinh tên ngẫu nhiên
    static QString generateTen();

    // Sinh địa chỉ ngẫu nhiên
    static QString generateDiaChi();

    static bool generateState();
    static QString generatePolice();

    //static void taoXeMau(vehicleshash* hashTable, Mylist<Violation>& dsMucPhat, int soLuong);
    static QString generateLoi();
    static void taoXeMau(vehicleshash* hashTable, int soLuong, HashTable<Person>& dsNguoi);

    // Tạo dữ liệu mẫu vào file
    static void taoDuLieuMau(const QString& cccdFile, const QString& biensoFile, int soLuong);
    static void docFileCCCD(const QString& filename, HashTable<Person>& dsNguoi);
    static void docFileBienSo(const QString& filename, vehicleshash* hashtableXe);

    // Khởi tạo random seed
    static void initRandom();

    static double timTienPhat(const QString& tenLoi, Mylist<Violation>& dsMucPhat);
    static void phanTichLoiPham(const QString& loiPart, Xe* xe, bool isMotor);
};

void docFilePolice(const QString& filename);
#endif
