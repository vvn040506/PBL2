#include<iostream>
#include<string.h>
#include<limits>
#include "HashTable.h"
#include "HashFunction.h"
#include "Police.h"
#include "Motor.h"
// #include "Person.h"  
using namespace std;

void themLoiTheoBienSo(HashTable<Person>& dsNguoi) {
    string bienSo, loiVP, ngayVP, idPolice;
    
    cout << "\n=== THEM LOI CHO XE THEO BIEN SO ===" << endl;
    cout << "Nhap bien so xe (vi du: 43-AB-18150): ";
    getline(cin, bienSo);
    cout << "Nhap ten loi vi pham: ";
    getline(cin, loiVP);
    cout << "Nhap ngay vi pham (dd/mm/yyyy): ";
    getline(cin, ngayVP);
    cout << "Nhap id cong an thuc hien: ";
    getline(cin, idPolice);
    
    bool found = false;

    for (int i = 0; i < dsNguoi.getCapacity(); i++) {
        Mylist<Person>* buckets = dsNguoi.buckets;
        for (Node<Person>* personNode = buckets[i].begin(); personNode != nullptr; personNode = personNode->getnext()) {
            Person& person = personNode->refgetdata();
            vehicleshash& hashXe = person.getXe();
            
            Motor* xe = hashXe.find(bienSo);
            if (xe != nullptr) {
                xe->themLoi(loiVP, ngayVP, idPolice);
                cout << "Da them loi '" << loiVP << "' cho xe: " << bienSo << endl;
                cout << "Chu xe: " << person.getTen() << " (CCCD: " << person.getCCCD() << ")" << endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }
    
    if (!found) {
        cout << "Khong tim thay xe voi bien so: " << bienSo << endl;
    }
}

void themLoiTheoCCCD(HashTable<Person>& dsNguoi) {
    string cccd, loiVP, ngayVP, idPolice;
    
    cout << "\n=== THEM LOI CHO TAT CA XE CUA MOT NGUOI ===" << endl;
    cout << "Nhap CCCD: ";
    getline(cin, cccd);
    cout << "Nhap ten loi vi pham: ";
    getline(cin, loiVP);
    cout << "Nhap ngay vi pham (dd/mm/yyyy): ";
    getline(cin, ngayVP);
    cout << "Nhap id cong an thuc hien: ";
    getline(cin, idPolice);
    
    try {
        Person& person = getByCCCD(cccd, dsNguoi);
        int count = 0;
        
        cout << "Them loi cho tat ca xe cua: " << person.getTen() << endl;
        
        for (int i = 0; i < person.getXe().get1(); i++) {
            for (int j = 0; j < person.getXe().get2(); j++) {
                for (int k = 0; k < person.getXe().get3(); k++) {
                    Node<Motor>* current = person.getXe().table[i][j][k].begin();
                    while (current != nullptr) {
                        current->refgetdata().themLoi(loiVP, ngayVP, idPolice);
                        cout << "Da them loi cho xe: " << current->getdata().getbienSo() << endl;
                        count++;
                        current = current->getnext();
                    }
                }
            }
        }
        
        if (count > 0) {
            cout << "Da them loi cho " << count << " xe" << endl;
        } else {
            cout << "Nguoi nay khong co xe nao" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Loi: " << e.what() << endl;
    }
}

void hienThiThongTin(HashTable<Person>& dsNguoi) {
    string cccd;
    
    cout << "\n=== HIEN THI THONG TIN VI PHAM ===" << endl;
    cout << "Nhap CCCD can xem: ";
    getline(cin, cccd);
    
    searchByCCCD(cccd, dsNguoi);
}

void menu(HashTable<Person>& dsNguoi) {
    int choice;
    
    do {
        cout << "\n=== MENU CHINH ===" << endl;
        cout << "1. Them loi cho xe theo bien so" << endl;
        cout << "2. Them loi cho tat ca xe cua mot nguoi" << endl;
        cout << "3. Hien thi thong tin vi pham theo CCCD" << endl;
        cout << "4. Tim kiem thong tin theo CCCD" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                themLoiTheoBienSo(dsNguoi);
                break;
                
            case 2:
                themLoiTheoCCCD(dsNguoi);
                break;
                
            case 3:
                hienThiThongTin(dsNguoi);
                break;
                
            case 4:
                {
                    string cccd;
                    cout << "Nhap CCCD can tim: ";
                    getline(cin, cccd);
                    searchByCCCD(cccd, dsNguoi);
                }
                break;
                
            case 0:
                cout << "Thoat chuong trinh" << endl;
                break;
                
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {

    cout << "=== BAT DAU CHUONG TRINH ===" << endl;
        
    HashTable<Person> dsNguoi(100);
    Police::dsPolice = new HashTable<Pair>(100);
    // Đọc file mã vùng
    cout << "1. Dang doc file ma vung..." << endl;
    Xe::docFileMaVung("mavung.txt");
    cout << "   -> Doc ma vung hoan tat" << endl;
        
    // Đọc file dữ liệu
    cout << "2. Dang doc file du lieu..." << endl;
    Person::docFileDanhSach("vipham.txt", dsNguoi);
    cout << "   -> Doc du lieu hoan tat" << endl;
        
    menu(dsNguoi);
    system("pause"); 
    return 0;
}
// g++ main.cpp Violation.cpp Xe.cpp Motor.cpp Person.cpp Police.cpp HashFunction.cpp HashTable.cpp -o main.exe
 
