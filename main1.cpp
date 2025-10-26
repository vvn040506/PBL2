#include "main1.h"
#define link D:\C++\PBL2\Data

vehicleshash* hashtableXe = nullptr;
HashTable<Person>* hashtableNguoi = nullptr;
Mylist<Violation> dsMucPhatMotor;
Mylist<Violation> dsMucPhatCar;

string ghepFile(const string& Link, const string& File){
    return Link + File;
}

// INPUT FILE
string Link = "D:\\C++\\PBL2\\Data\\";
string finalMaVung = ghepFile(Link,"mavung.txt");
string finalMotor = ghepFile(Link,"Motor.txt");
string finalCar = ghepFile(Link,"Car.txt");
string finalCCCD = ghepFile(Link,"cccd.txt");
string finalbienSo = ghepFile(Link,"bienso.txt");



void pause() {
    cout << "\nNhan phim bat ky de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void khoiTaoHeThong() {
    
system("cls");
    cout << "========================================" << endl;
    cout << "        KHOI TAO HE THONG               " << endl;
    cout << "========================================" << endl;
    
    try {
        hashtableXe = new vehicleshash(5, 5, 50);
        cout << "[OK] Da tao hash table xe" << endl;
        
        hashtableNguoi = new HashTable<Person>(1000);
        cout << "[OK] Da tao hash table nguoi" << endl;
        string Link = "D:\\C++\\PBL2\\Data\\";
        string finalMaVung = ghepFile(Link,"mavung.txt");
        
        
        Xe::docFileMaVung(finalMaVung);
        if (Xe::dsMaVung.size() > 0) {
            cout << "[OK] Da doc ma vung: " << Xe::dsMaVung.size() << " tinh/thanh" << endl;
        } else {
            cout << "[LOI] Khong doc duoc ma vung!" << endl;
        }
        
        readDSLoi(dsMucPhatMotor, finalMotor);
        cout << "[OK] Da doc muc phat Motor: " << dsMucPhatMotor.size() << " loai" << endl;
        
        readDSLoi(dsMucPhatCar, finalCar);
        cout << "[OK] Da doc muc phat Car: " << dsMucPhatCar.size() << " loai" << endl;
        
        cout << "\n[HOAN TAT] He thong da san sang!" << endl;
    } catch (const std::exception& e) {
        cout << "Loi khoi tao: " << e.what() << endl;
        pause();
        return;
    }
    
    cout << "\nBan co muon doc du lieu tu file cccd.txt va bienso.txt? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        // Kiểm tra sự tồn tại của file
        ifstream cccdFile(finalCCCD), biensoFile(finalbienSo);
        if (!cccdFile.is_open() || !biensoFile.is_open()) {
            cout << "Loi: Khong tim thay file cccd.txt hoac bienso.txt." << endl;
            if (!cccdFile.is_open()) cout << "File cccd.txt khong ton tai." << endl;
            if (!biensoFile.is_open()) cout << "File bienso.txt khong ton tai." << endl;
            cccdFile.close();
            biensoFile.close();
            
            cout << "\nBan co muon tao du lieu mau tu file? (y/n): ";
            char createChoice;
            cin >> createChoice;
            cin.ignore();
            
            if (createChoice == 'y' || createChoice == 'Y') {
                cout << "Nhap so luong nguoi muon tao (de xuat: 100-500): ";
                int soLuong;
                cin >> soLuong;
                cin.ignore();
                
                cout << "Dang tao du lieu mau..." << endl;
                DataGenerator::taoDuLieuMau(finalCCCD, finalbienSo, soLuong);
                cout << "Da tao xong du lieu mau!" << endl;
            } else {
                pause();
                return;
            }
        }
        cccdFile.close();
        biensoFile.close();
        
        cout << "Bat dau doc du lieu. Vui long doi..." << endl;
        
        try {

            DataGenerator::docFileBienSo(finalbienSo, hashtableXe);
            DataGenerator::docFileCCCD(finalCCCD, *hashtableNguoi);
                     
            cout << "\n[THANH CONG] Doc du lieu thanh cong!" << endl;
            
        } catch (const std::exception& e) {
            cout << "Loi khi doc du lieu: " << e.what() << endl;
        }
    }
    pause();
}


void congAn_XemThongKe() {
    system("cls");
    cout << "\n=== MENU THONG KE (CONG AN) ===\n";
    cout << "1. Thong ke tong quan\n";
    cout << "2. Thong ke Motor vs Car\n";
    cout << "3. Thong ke theo loi vi pham\n";
    cout << "0. Quay lai\n";
    cout << "Nhap lua chon: ";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch (choice) {
        case 1:
            system("cls");
            hashtableXe->thongke();
            pause();
            break;
        case 2:
            system("cls");
            cout << "Chuc nang dang phat trien..." << endl;
            pause();
            break;
        case 3:
            system("cls");
            cout << "Chuc nang dang phat trien..." << endl;
            pause();
            break;
        case 0:
            return;
        default:
            cout << "Lua chon khong hop le!" << endl;
            pause();
    }
}


void menuCongAn() {
    int choice;
    Police *p = new Police();
    do {
        p->menu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                hashtableXe->thongke();
                break;
            case 2:
                p->timXe(hashtableXe);
                break;
            case 3:
                p->themloiXe(hashtableXe);
                break;
            case 4:
                p->xoaloiXe(hashtableXe);
                break;
            case 5:
                p->themxeMoi(hashtableXe);
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le!" << endl;
                pause();
        }
    } while (true);
}


void menuNguoiDan() {
    do {
        int choice;
        
        Citizen* c = new Citizen;
        c->menu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                hashtableXe->thongke();
                break;
            case 2:
                c->timXe(hashtableXe);
                break;
            case 3:
                c->truyvanCCCD(hashtableNguoi);
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le!" << endl;
                pause();
        }
    } while (true);
}

// ===== MENU HOME =====
void menuHome() {
    int choice;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "   HE THONG QUAN LY XE BI PHAT NGUOI    " << endl;
        cout << "========================================" << endl;
        cout << "1. Dang nhap Cong an" << endl;
        cout << "2. Dang nhap Nguoi dan" << endl;
        cout << "3. Thoat" << endl;
        cout << "========================================" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                menuCongAn();
                break;
            case 2:
                menuNguoiDan();
                break;
            case 3:
                cout << "\n========================================" << endl;
                cout << "  Cam on ban da su dung he thong!     " << endl;
                cout << "             Tam biet!                 " << endl;
                cout << "========================================" << endl;
                return;
            default:
                cout << "Lua chon khong hop le!" << endl;
                pause();
        }
    } while (true);
}
