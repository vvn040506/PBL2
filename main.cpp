#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "Motor.h"
#include "Car.h"
#include "HashFunction.h"
#include "Person.h"
#include "HashTable.h"
#include "DataGenerator.h"
#include "main1.h"
using namespace std;

int main() {
    // Banner chào mừng
    cout << "========================================" << endl;
    cout << "                                        " << endl;
    cout << "               PBL2                     " << endl;
    cout << "        DO AN CO SO LAP TRINH           " << endl;
    cout << "                                        " << endl;
    cout << "     VO VIET NHAT - TRAN LE MINH        " << endl;
    cout << "                                        " << endl;
    cout << "========================================" << endl;
    //pause();
    
    // Khởi tạo hệ thống
    khoiTaoHeThong();
    
    // Vào menu chính
    menuHome();
    
    // Dọn dẹp bộ nhớ
    if (hashtableXe != nullptr) {
        delete hashtableXe;
    }
    if (hashtableNguoi != nullptr) {
        delete hashtableNguoi;
    }
    
    return 0;

}