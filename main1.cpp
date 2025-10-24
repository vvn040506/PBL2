#include "main1.h"

// ===== ĐỊNH NGHĨA BIẾN TOÀN CỤC =====
vehicleshash* hashtableXe = nullptr;
HashTable<Person>* hashtableNguoi = nullptr;
Mylist<Violation> dsMucPhatMotor;
Mylist<Violation> dsMucPhatCar;

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
        
        Xe::docFileMaVung("mavung.txt");
        if (Xe::dsMaVung.size() > 0) {
            cout << "[OK] Da doc ma vung: " << Xe::dsMaVung.size() << " tinh/thanh" << endl;
        } else {
            cout << "[LOI] Khong doc duoc ma vung!" << endl;
        }
        
        readDSLoi(dsMucPhatMotor, "Motor.txt");
        cout << "[OK] Da doc muc phat Motor: " << dsMucPhatMotor.size() << " loai" << endl;
        
        readDSLoi(dsMucPhatCar, "car.txt");
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
        ifstream cccdFile("cccd.txt"), biensoFile("bienso.txt");
        if (!cccdFile.is_open() || !biensoFile.is_open()) {
            cout << "Loi: Khong tim thay file cccd.txt hoac bienso.txt." << endl;
            if (!cccdFile.is_open()) cout << "File cccd.txt khong ton tai." << endl;
            if (!biensoFile.is_open()) cout << "File bienso.txt khong ton tai." << endl;
            cccdFile.close();
            biensoFile.close();
            
            // Hỏi có muốn tạo dữ liệu mẫu không
            cout << "\nBan co muon tao du lieu mau? (y/n): ";
            char createChoice;
            cin >> createChoice;
            cin.ignore();
            
            if (createChoice == 'y' || createChoice == 'Y') {
                cout << "Nhap so luong nguoi muon tao (de xuat: 100-500): ";
                int soLuong;
                cin >> soLuong;
                cin.ignore();
                
                cout << "Dang tao du lieu mau..." << endl;
                DataGenerator::taoDuLieuMau("cccd.txt", "bienso.txt", soLuong);
                cout << "Da tao xong du lieu mau!" << endl;
            } else {
                pause();
                return;
            }
        }
        cccdFile.close();
        biensoFile.close();

        cout << "Nhap so luong ban ghi muon doc (nhap 0 de doc tat ca): ";
        int soLuong;
        cin >> soLuong;
        cin.ignore();
        
        cout << "Bat dau doc du lieu. Vui long doi..." << endl;
        
        try {
            // Đọc file cccd.txt
            DataGenerator::docFileBienSo("bienso.txt", hashtableXe);
            DataGenerator::docFileCCCD("cccd.txt", *hashtableNguoi);
            
            // Đọc file bienso.txt            
            cout << "\n[THANH CONG] Doc du lieu thanh cong!" << endl;
            
            // Hiển thị thống kê ngay sau khi load
            cout << "\n=== THONG KE SAU KHI TAI DU LIEU ===" << endl;
            hashtableXe->thongke();
            
        } catch (const std::exception& e) {
            cout << "Loi khi doc du lieu: " << e.what() << endl;
        }
    }
    pause();
}


// ===== MENU CÔNG AN =====

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
            // hashtableXe->thongKeMotorVsCar();
            cout << "Chuc nang dang phat trien..." << endl;
            pause();
            break;
        case 3:
            system("cls");
            // hashtableXe->thongKeTheoLoi(dsMucPhatMotor);
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
        system("cls");
        cout << "========================================" << endl;
        cout << "           MENU CONG AN                 " << endl;
        cout << "========================================" << endl;
        cout << "1. Xem thong ke tong quan" << endl;
        cout << "2. Tim xe theo bien so" << endl;
        cout << "3. Them loi vi pham cho xe" << endl;
        cout << "4. Xoa loi vi pham (neu ghi nham)" << endl;
        cout << "5. Them xe moi vao he thong" << endl;
        cout << "0. Quay lai" << endl;
        cout << "========================================" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                congAn_XemThongKe();
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

// ===== MENU NGƯỜI DÂN =====

void nguoiDan_XemThongKe() {
    system("cls");
    hashtableXe->thongke();
    pause();
}

void nguoiDan_TraCuuXe() {
    system("cls");
    cout << "\n=== TRA CUU XE THEO BIEN SO ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashtableXe->find(bienSo);
    if (xe) {
        xe->truyxuatLoi();
    } else {
        cout << "\nKhong tim thay xe co bien so: " << bienSo << endl;
    }
    
    pause();
}

void nguoiDan_TraCuuCCCD() {
    system("cls");
    cout << "\n=== TRA CUU THEO CCCD ===\n";
    
    cout << "Nhap so CCCD: ";
    string cccd;
    getline(cin, cccd);
    
    try {
        Person &p = getByCCCD(cccd, *hashtableNguoi);
        cout << "\n--- THONG TIN CHU XE ---" << endl;
        cout << p;
    } catch (const exception& e) {
        cout << "\nKhong tim thay CCCD: " << cccd << endl;
    }
    
    pause();
}

void menuNguoiDan() {
    int choice;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "           MENU NGUOI DAN               " << endl;
        cout << "========================================" << endl;
        cout << "1. Xem thong ke tong quan" << endl;
        cout << "2. Tra cuu xe theo bien so" << endl;
        cout << "3. Tra cuu theo CCCD" << endl;
        cout << "0. Quay lai" << endl;
        cout << "========================================" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        
        Citizen* c = new Citizen;
        switch (choice) {
            case 1:
                nguoiDan_XemThongKe();
                break;
            case 2:
                nguoiDan_TraCuuXe();
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
