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
string finalpolice = ghepFile(Link,"police.txt");



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
        
        
        Xe::docFileMaVung(finalMaVung);
        if (Xe::dsMaVung.size() > 0) {
            cout << "Da doc ma vung: " << Xe::dsMaVung.size() << " tinh/thanh" << endl;
        } else {
            cout << "Khong doc duoc ma vung!" << endl;
        }
        
        readDSLoi(dsMucPhatMotor, finalMotor);
        cout << "Da doc muc phat Motor: " << dsMucPhatMotor.size() << " loai" << endl;
        
        readDSLoi(dsMucPhatCar, finalCar);
        cout << "Da doc muc phat Car: " << dsMucPhatCar.size() << " loai" << endl;
        
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
        DataGenerator ::taoDuLieuMau(finalCCCD,finalbienSo,1000);
        ifstream cccdFile(finalCCCD);
        ifstream biensoFile(finalbienSo);
        ifstream policeFile(finalpolice);
    
        bool fileExist = cccdFile.is_open() && biensoFile.is_open() && policeFile.is_open();
        cccdFile.close();
        biensoFile.close();
        policeFile.close();
    
    if (!fileExist) {
        cout << "\nKhong tim thay file cccd.txt hoac bienso.txt!" << endl;
        cout << "Vui long tao du lieu truoc khi su dung he thong." << endl;
        pause();
        return;
    }
        
        try {
            DataGenerator::taoXeMau(hashtableXe, 0, *hashtableNguoi);
            docFilePolice(finalpolice);
            
            cout << "\n[THANH CONG] Doc du lieu thanh cong!" << endl;
            hashtableXe->thongke();
            
        } catch (const std::exception& e) {
            cout << "Loi khi doc du lieu: " << e.what() << endl;
        }
    }
}


void XemThongKe() {
    system("cls");
    cout << "\n=== MENU THONG KE ===\n";
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
            break;
        case 2:
            system("cls");
            hashtableXe->thongkeMotorvsCar();
            break;
        case 3:
            system("cls");
            hashtableXe->thongketheoLoi();
            break;
        case 0:
            return;
        default:
            cout << "Lua chon khong hop le!" << endl;
    }
}


void menuCongAn() {
    string i;
    string pass;
    Police *p = new Police();

    do{
        cout << "nhap c de thoat qua trinh dang nhap " << endl;
        string c;
        cin >> c;
        if (c=="c") break;
        cout << "ban chua dang nhap hoac nhap sai id/pass" <<endl;
        cout << "nhap id : " <<endl; cin >> i;
        cout << "nhap pass : " << endl; cin >> pass;
    } while (!(p->dangNhap(i,pass)));
    

    int choice;
    do {
        p->menu();
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                XemThongKe();
                break;
            case 2:
                p->timXe(hashtableXe);
                break;
            case 3:
                p->themloiXe(hashtableXe);
                break;
            case 4:
                p->dongPhat(hashtableXe);
                break;
            case 5:
                p->themxeMoi(hashtableXe);
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le!" << endl;
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
                XemThongKe();
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
        }
    } while (true);
}

void menuHome() {
    int choice;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "   HE THONG QUAN LY XE BI PHAT NGUOI    " << endl;
        cout << "========================================" << endl;
        cout << "1. Dang nhap Cong an (yeu cau dang nhap)" << endl;
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
