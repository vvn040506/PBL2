#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <string>
#include <ctime>
#include <cstdlib>
#include "Motor.h"
#include "Car.h"
#include "HashFunction.h"
#include "Mylist.h"

using namespace std;

class DataGenerator {
public:
    // Sinh biển số ngẫu nhiên
    static string generateBienSo();
    
    // Sinh ngày ngẫu nhiên
    static string generateNgay();
    
    // Sinh số CCCD ngẫu nhiên
    static string generateCCCD();
    
    // Sinh số điện thoại ngẫu nhiên
    static string generateSDT();
    
    // Sinh tên ngẫu nhiên
    static string generateTen();
    
    // Sinh địa chỉ ngẫu nhiên
    static string generateDiaChi();
    
    // Tạo dữ liệu mẫu cho hệ thống
    //static void taoXeMau(vehicleshash* hashTable, Mylist<Violation>& dsMucPhat, int soLuong);
    static string generateLoi();
    static void taoXeMau(vehicleshash* hashTable, Mylist<Violation>& dsMucPhat, int soLuong, HashTable<Person>& dsNguoi);
    
    // Tạo dữ liệu mẫu vào file
    static void taoDuLieuMau(const string& cccdFile, const string& biensoFile, int soLuong);
    static void docFileCCCD(const string& filename, HashTable<Person>& dsNguoi);
    static void docFileBienSo(const string& filename, vehicleshash* hashtableXe);
    
    // Khởi tạo random seed
    static void initRandom();
};


#endif
