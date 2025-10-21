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
using namespace std;

// ===== BIẾN TOÀN CỤC =====
vehicleshash* hashTableXe = nullptr;
HashTable<Person>* hashTableNguoi = nullptr;
Mylist<Violation> dsMucPhatMotor;
Mylist<Violation> dsMucPhatCar;

// ===== KHAI BÁO HÀM =====
void clearScreen();
void pause();
void khoiTaoHeThong();
void menuHome();
void menuCongAn();
void menuNguoiDan();

// ===== TIỆN ÍCH =====
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ===== KHỞI TẠO HỆ THỐNG =====
/*void khoiTaoHeThong() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        KHOI TAO HE THONG               " << endl;
    cout << "========================================" << endl;
    
    // 1. Tạo hash table xe
    hashTableXe = new vehicleshash(10, 10, 100);
    cout << "[OK] Da tao hash table xe" << endl;
    
    // 2. Tạo hash table người
    hashTableNguoi = new HashTable<Person>(1000);
    cout << "[OK] Da tao hash table nguoi" << endl;
    
    // 3. Đọc mã vùng
    Xe::docFileMaVung("mavung.txt");
    cout << "[OK] Da doc ma vung: " << Xe::dsMaVung.size() << " tinh/thanh" << endl;
    
    // 4. Đọc danh sách mức phạt Motor
    readDSLoi(dsMucPhatMotor, "Motor.txt");
    cout << "[OK] Da doc muc phat Motor: " << dsMucPhatMotor.size() << " loai" << endl;
    
    // 5. Đọc danh sách mức phạt Car
    readDSLoi(dsMucPhatCar, "car.txt");
    cout << "[OK] Da doc muc phat Car: " << dsMucPhatCar.size() << " loai" << endl;
    
    // 6. Hỏi có tạo dữ liệu mẫu không
    cout << "\nBan co muon tao du lieu mau? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        cout << "Nhap so luong xe muon tao (de xuat: 100-500): ";
        int soLuong;
        cin >> soLuong;
        cin.ignore();
        
        // Gộp 2 danh sách mức phạt
        Mylist<Violation> dsGop = dsMucPhatMotor;
        Node<Violation>* v = dsMucPhatCar.begin();
        while (v != nullptr) {
            dsGop.push_back(v->getdata());
            v = v->getnext();
        }
        
        DataGenerator::taoXeMau(hashTableXe, dsGop, soLuong);
    }
    cout << "\n[HOAN TAT] He thong da san sang!" << endl;
    pause();
}*/
void khoiTaoHeThong() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "        KHOI TAO HE THONG               " << endl;
    cout << "========================================" << endl;
    
    try {
        hashTableXe = new vehicleshash(5, 5, 50); // Giảm size để test
        cout << "[OK] Da tao hash table xe" << endl;
        
        hashTableNguoi = new HashTable<Person>(1000);
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
    }
    cout << "\nBan co muon tao du lieu mau? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 'y' || choice == 'Y') {
        cout << "Nhap so luong xe muon tao (de xuat: 100-500): ";
        int soLuong;
        cin >> soLuong;
        cin.ignore();
        
        // Gộp 2 danh sách mức phạt
        Mylist<Violation> dsGop = dsMucPhatMotor;
        Node<Violation>* v = dsMucPhatCar.begin();
        while (v != nullptr) {
            dsGop.push_back(v->getdata());
            v = v->getnext();
        }
        
        DataGenerator::taoXeMau(hashTableXe, dsGop, soLuong);
    }
    pause();
}

// ===== MENU CÔNG AN =====

void congAn_XemThongKe() {
    clearScreen();
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
            clearScreen();
            hashTableXe->thongke();
            pause();
            break;
        case 2:
            clearScreen();
            // hashTableXe->thongKeMotorVsCar();
            cout << "Chuc nang dang phat trien..." << endl;
            pause();
            break;
        case 3:
            clearScreen();
            // hashTableXe->thongKeTheoLoi(dsMucPhatMotor);
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

void congAn_TimXe() {
    clearScreen();
    cout << "\n=== TIM KIEM XE THEO BIEN SO ===\n";
    
    cout << "Nhap bien so xe (VD: 29-A1-12345): ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashTableXe->find(bienSo);
    if (xe) {
        xe->truyxuatLoi();
    } else {
        cout << "\nKhong tim thay xe co bien so: " << bienSo << endl;
    }
    
    pause();
}

void congAn_ThemLoi() {
    clearScreen();
    cout << "\n=== THEM LOI VI PHAM CHO XE ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashTableXe->find(bienSo);
    if (!xe) {
        cout << "\nKhong tim thay xe!" << endl;
        pause();
        return;
    }
    
    cout << "\nDa tim thay xe: " << bienSo << endl;
    cout << "Loai xe: " << xe->getLS() << endl;
    
    // Hiển thị danh sách lỗi
    cout << "\n--- DANH SACH LOI CO THE CHON ---" << endl;
    
    Mylist<Violation>* dsMucPhat = nullptr;
    if (xe->getLS() == "Motor") {
        dsMucPhat = &dsMucPhatMotor;
    } else {
        dsMucPhat = &dsMucPhatCar;
    }
    
    Node<Violation>* v = dsMucPhat->begin();
    int stt = 1;
    while (v != nullptr) {
        cout << stt++ << ". " << v->getdata().getLoiViPham() 
             << " - " << v->getdata().getMucPhat() << " VND" << endl;
        v = v->getnext();
    }
    
    cout << "\nNhap ten loi vi pham: ";
    string tenLoi;
    getline(cin, tenLoi);
    
    cout << "Nhap ngay vi pham (dd-mm-yyyy): ";
    string ngayVP;
    getline(cin, ngayVP);
    
    // Thêm lỗi
    xe->themLoi(tenLoi, ngayVP);
    cout << "\n[THANH CONG] Da them loi vi pham!" << endl;
    
    pause();
}

void congAn_XoaLoi() {
    clearScreen();
    cout << "\n=== XOA LOI VI PHAM (NEU GHI NHAM) ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashTableXe->find(bienSo);
    if (!xe) {
        cout << "\nKhong tim thay xe!" << endl;
        pause();
        return;
    }
    
    // Hiển thị danh sách lỗi hiện có
    cout << "\n--- DANH SACH LOI HIEN TAI ---" << endl;
    if (xe->dsLoi.size() == 0) {
        cout << "Xe chua co loi vi pham nao!" << endl;
        pause();
        return;
    }
    
    Node<Pair>* loi = xe->dsLoi.begin();
    int stt = 1;
    while (loi != nullptr) {
        cout << stt++ << ". " << loi->getdata().key 
             << " - " << loi->getdata().value << endl;
        loi = loi->getnext();
    }
    
    cout << "\nNhap ten loi can xoa: ";
    string tenLoi;
    getline(cin, tenLoi);
    
    cout << "Nhap ngay vi pham: ";
    string ngayVP;
    getline(cin, ngayVP);
    
    // Xóa lỗi
    xe->dongPhat(tenLoi, ngayVP);
    cout << "\n[THANH CONG] Da xoa loi vi pham!" << endl;
    
    pause();
}

void congAn_ThemXeMoi() {
    clearScreen();
    cout << "\n=== THEM XE MOI VAO HE THONG ===\n";
    
    cout << "Chon loai xe:\n";
    cout << "1. Xe may (Motor)\n";
    cout << "2. O to (Car)\n";
    cout << "Nhap lua chon: ";
    
    int loai;
    cin >> loai;
    cin.ignore();
    
    if (loai != 1 && loai != 2) {
        cout << "Lua chon khong hop le!" << endl;
        pause();
        return;
    }
    
    Xe* xe = nullptr;
    
    if (loai == 1) {
        Motor* m = new Motor();
        cin >> *m;
        m->danhSachMucPhat = dsMucPhatMotor;
        xe = m;
    } else {
        Car* c = new Car();
        cin >> *c;
        c->danhSachMucPhat = dsMucPhatCar;
        xe = c;
    }
    
    hashTableXe->insertToHash(xe);
    cout << "\n[THANH CONG] Da them xe vao he thong!" << endl;
    cout << "\n--- DEBUG INFO ---" << endl;
    cout << "Bien so: " << xe->getbienSo() << endl;
    cout << "Thanh pho: " << xe->getTP() << endl;
    cout << "Loai xe: " << xe->getLS() << endl;
    
    // Thử tìm lại ngay
    Xe* test = hashTableXe->find(xe->getbienSo());
    if (test) {
        cout << "✓ Tim thay xe!" << endl;
    } else {
        cout << "✗ KHONG tim thay xe!" << endl;
    }
    
    
    pause();
}

void menuCongAn() {
    int choice;
    do {
        clearScreen();
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
                congAn_TimXe();
                break;
            case 3:
                congAn_ThemLoi();
                break;
            case 4:
                congAn_XoaLoi();
                break;
            case 5:
                congAn_ThemXeMoi();
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
    clearScreen();
    hashTableXe->thongke();
    pause();
}

void nguoiDan_TraCuuXe() {
    clearScreen();
    cout << "\n=== TRA CUU XE THEO BIEN SO ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashTableXe->find(bienSo);
    if (xe) {
        xe->truyxuatLoi();
    } else {
        cout << "\nKhong tim thay xe co bien so: " << bienSo << endl;
    }
    
    pause();
}

void nguoiDan_TraCuuCCCD() {
    clearScreen();
    cout << "\n=== TRA CUU THEO CCCD ===\n";
    
    cout << "Nhap so CCCD: ";
    string cccd;
    getline(cin, cccd);
    
    try {
        Person &p = getByCCCD(cccd, *hashTableNguoi);
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
        clearScreen();
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
        
        switch (choice) {
            case 1:
                nguoiDan_XemThongKe();
                break;
            case 2:
                nguoiDan_TraCuuXe();
                break;
            case 3:
                nguoiDan_TraCuuCCCD();
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
        clearScreen();
        cout << "========================================" << endl;
        cout << "   HE THONG QUAN LY LOI VI PHAM GIAO   " << endl;
        cout << "               THONG                    " << endl;
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

// ===== MAIN =====
int main() {
    // Banner chào mừng
    clearScreen();
    cout << "========================================" << endl;
    cout << "                                        " << endl;
    cout << "   HE THONG QUAN LY LOI VI PHAM GIAO   " << endl;
    cout << "               THONG                    " << endl;
    cout << "                                        " << endl;
    cout << "        Phien ban 1.0 - 2025            " << endl;
    cout << "                                        " << endl;
    cout << "========================================" << endl;
    pause();
    
    // Khởi tạo hệ thống
    khoiTaoHeThong();
    
    // Vào menu chính
    menuHome();
    
    // Dọn dẹp bộ nhớ
    if (hashTableXe != nullptr) {
        delete hashTableXe;
    }
    if (hashTableNguoi != nullptr) {
        delete hashTableNguoi;
    }
    
    return 0;
}