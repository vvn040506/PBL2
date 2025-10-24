#include "Person.h"
#include "Motor.h"
#include "HashFunction.h"
#include "HashTable.h"
#include "Xe.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <limits>
#include "Motor.h"
#include "Car.h"
#include "DataGenerator.h"
#include "main1.h"
using namespace std;

// Constructor implementations
Person::Person() : cccd(""), ten(""){
    hash_xe = new vehicleshash(10, 10, 100);
}

Person::Person(const string &cccd, const string &ten, const string& sdt, const string& d) 
    : cccd(cccd), ten(ten), sdt(sdt), diachi(d) { 
            hash_xe = new vehicleshash(10, 10, 100);

}
Person::Person(const Person& other) 
    : cccd(other.cccd), ten(other.ten), sdt(other.sdt), diachi(other.diachi) {
    
    // Deep copy vehicleshash
    hash_xe = new vehicleshash(other.hash_xe->get1(), 
                               other.hash_xe->get2(), 
                               other.hash_xe->get3());
    
    // Copy tất cả xe từ hash table cũ sang mới
    for (int i = 0; i < other.hash_xe->get1(); ++i) {
        for (int j = 0; j < other.hash_xe->get2(); ++j) {
            for (int k = 0; k < other.hash_xe->get3(); ++k) {
                Node<Xe*>* current = other.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    // Clone xe (bạn cần implement clone method cho Xe)
                    Xe* xe = current->getdata();
                    Xe* newXe = new Xe(*xe); // Giả sử Xe có copy constructor
                    hash_xe->insertToHash(newXe);
                    current = current->getnext();
                }
            }
        }
    }
    
    hash_nguoi = nullptr; // Hoặc copy nếu cần
}

// Assignment operator
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        // Xóa hash cũ
        if (hash_xe != nullptr) {
            delete hash_xe;
        }
        
        // Copy data
        cccd = other.cccd;
        ten = other.ten;
        sdt = other.sdt;
        diachi = other.diachi;
        
        // Deep copy hash
        hash_xe = new vehicleshash(other.hash_xe->get1(), 
                                   other.hash_xe->get2(), 
                                   other.hash_xe->get3());
        
        // Copy vehicles...
        for (int i = 0; i < other.hash_xe->get1(); ++i) {
            for (int j = 0; j < other.hash_xe->get2(); ++j) {
                for (int k = 0; k < other.hash_xe->get3(); ++k) {
                    Node<Xe*>* current = other.hash_xe->table[i][j][k].begin();
                    while (current != nullptr) {
                        Xe* newXe = new Xe(*current->getdata());
                        hash_xe->insertToHash(newXe);
                        current = current->getnext();
                    }
                }
            }
        }
    }
    return *this;
}

// Operator implementations
bool Person::operator==(const Person& other) const {
    return this->cccd == other.cccd;
}

bool Person::operator!=(const Person& other) const {
    return this->cccd != other.cccd;
}

// Friend function implementations
istream& operator >> (istream& in, Person& p){
    cout << "Nhap cccd: ";
    getline(in >> ws, p.cccd);  

    cout << "Nhap ten nguoi vp: ";
    getline(in, p.ten);
    return in;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "[CCCD: " << p.cccd << ", Ten: " << p.ten << ", Sdt: " << p.sdt << ", Dia chi: " << p.diachi << "]" << endl;
    os << "Danh sach xe vi pham:" << endl;
    
    for (int i = 0; i < p.hash_xe->get1(); ++i) {
        for (int j = 0; j < p.hash_xe->get2(); ++j) {
            for (int k = 0; k < p.hash_xe->get3(); ++k) {
                
                Node<Xe*>* current = p.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    os << "  - ";
                    current->getdata()->display();  
                    current = current->getnext();
                }
            }
        }
    }
    return os;
}

void Person::nhapTT(){
    cout << "Nhap cccd: "; cin >> cccd;
    cout << "Nhap ten nguoi vp: "; 
    cin.ignore();
    getline(cin, ten);
}

void Person::setXe(vehicleshash* xe){
    if (hash_xe != nullptr) {
        delete hash_xe;
    }
    hash_xe = xe; 
}

vehicleshash* Person::getXe(){
    return hash_xe;
}

void Person::phanTichBienSo(const string& bienSo, Xe& Xe) {
    size_t dash1 = bienSo.find('-');
    size_t dash2 = bienSo.find('-', dash1 + 1);
    
    if (dash1 != string::npos && dash2 != string::npos) {
        string maTP = bienSo.substr(0, dash1);
        string loaiXe = bienSo.substr(dash1 + 1, dash2 - dash1 - 1);
        
        Xe.setBienSo(bienSo);
        
        for (Node<Pair>* x = Xe::dsMaVung.begin(); x != nullptr; x = x->getnext()) {
            if (x->getdata().value == maTP) {
                Xe.setThanhPho(x->getdata().key);
                break;
            }
        }
    }
}

void Person::docFileDanhSach(const string& filename, HashTable<Person>& dsNguoi) {
    ifstream fs(filename);
    if (!fs.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }

    cout << "Mo file thanh cong: " << filename << endl;
    string line;
    int lineCount = 0;

    while (getline(fs, line)) {
        lineCount++;
        if (line.empty()) continue;

        stringstream ss(line);
        string token;

        Mylist<string> tokens;
        while (ss >> token) tokens.push_back(token);

        if (tokens.IsEmpty()) {
            cout << "-> Dong " << lineCount << ": Dong trong, bo qua" << endl;
            continue;
        }

        cout << "\n--- Dong " << lineCount << " ---" << endl;

        // Lấy CCCD
        string cccd = tokens.begin()->getdata();
        tokens.pop_front();
        cout << "CCCD: " << cccd << endl;

        // Parse danh sách xe (LoaiXe BienSo)
        Mylist<Pair> danhSachXe;
        Node<string>* cur = tokens.begin();
        while (cur != nullptr) {
            string loai = cur->getdata();
            Node<string>* next = cur->getnext();

            if ((loai == "Motor" || loai == "Car") && next != nullptr) {
                string bienSo = next->getdata();
                danhSachXe.push_back(Pair(loai, bienSo));
                cur = next->getnext();
            } else {
                break;
            }
        }

        // Parse thông tin còn lại (Tên, SDT, Địa chỉ)
        Mylist<string> thongTinConLai;
        while (cur != nullptr) {
            thongTinConLai.push_back(cur->getdata());
            cur = cur->getnext();
        }

        if (thongTinConLai.size() < 3) {
            cout << "-> Dong " << lineCount << ": Thieu thong tin, bo qua" << endl;
            continue;
        }

        int n = thongTinConLai.size();
        Node<string>* p = thongTinConLai.begin();
        string arr[100];
        int idx = 0;
        while (p != nullptr && idx < 100) {
            arr[idx++] = p->getdata();
            p = p->getnext();
        }

        // Tìm SDT (chuỗi all-digit)
        int posSDT = -1;
        for (int i = idx - 1; i >= 0; --i) {
            bool allDigit = true;
            for (char c : arr[i]) {
                if (!isdigit(c)) { allDigit = false; break; }
            }
            if (allDigit) { posSDT = i; break; }
        }

        if (posSDT == -1) {
            cout << "-> Dong " << lineCount << ": Khong tim thay SDT, bo qua" << endl;
            continue;
        }

        // Parse Tên
        string ten = "";
        for (int i = 0; i < posSDT; ++i) {
            if (!ten.empty()) ten += " ";
            ten += arr[i];
        }

        // Parse SDT
        string sdt = arr[posSDT];

        // Parse Địa chỉ
        string diachi = "";
        for (int i = posSDT + 1; i < idx; ++i) {
            if (!diachi.empty()) diachi += " ";
            diachi += arr[i];
        }

        cout << "Ten: " << ten << "\nSDT: " << sdt << "\nDia chi: " << diachi << endl;

        // Tạo Person mới
        Person pnew(cccd, ten, sdt, diachi);

        // Thêm xe vào hash_xe của Person
        for (Node<Pair>* x = danhSachXe.begin(); x != nullptr; x = x->getnext()) {
            string loaiXe = x->getdata().key;
            string bienSo = x->getdata().value;

            // Tìm xe gốc từ hashtableXe toàn cục
            Xe* xeGoc = hashtableXe->find(bienSo);
            
            // Tạo xe mới theo loại
            Xe* xeMoi = nullptr;
            if (loaiXe == "Motor") {
                xeMoi = new Motor();
            } else if (loaiXe == "Car") {
                xeMoi = new Car();
            } else {
                cout << "-> Dong " << lineCount << ": Loai xe khong hop le: " << loaiXe << endl;
                continue;
            }

            // Set thông tin cơ bản
            xeMoi->setBienSo(bienSo);
            phanTichBienSo(bienSo, *xeMoi);

            // Copy dsLoi và danhSachMucPhat từ xe gốc (nếu có)
            if (xeGoc != nullptr) {
                // Deep copy dsLoi
                Node<Pair>* loiGoc = xeGoc->dsLoi.begin();
                while (loiGoc != nullptr) {
                    Pair loiCopy = loiGoc->getdata(); // Copy Pair (tenLoi, ngayVP)
                    xeMoi->dsLoi.push_back(loiCopy);
                    loiGoc = loiGoc->getnext();
                }

                // Set danhSachMucPhat (dùng global để đồng bộ)
                xeMoi->danhSachMucPhat = (loaiXe == "Motor") ? dsMucPhatMotor : dsMucPhatCar;

                // Copy các thuộc tính khác
                //xeMoi->soLoi = xeGoc->soLoi;
                // Nếu cần copy thêm tongTienPhat hoặc các field khác, thêm ở đây
            } else {
                cout << "-> Dong " << lineCount << ": Khong tim thay xe " << bienSo << " trong hashtableXe" << endl;
                // Vẫn thêm xe mới vào Person, nhưng không có lỗi
                xeMoi->danhSachMucPhat = (loaiXe == "Motor") ? dsMucPhatMotor : dsMucPhatCar;
            }

            // Thêm xe vào hash_xe của Person
            pnew.getXe()->insertToHash(xeMoi);
            cout << "-> Dong " << lineCount << ": Da them xe " << bienSo << " (" << loaiXe << ") vao Person" << endl;
        }

        // Thêm Person vào HashTable
        dsNguoi.insert(cccd, pnew);
        cout << "-> Da them " << ten << " vao HashTable" << endl;
    }

    cout << "\n=== KET THUC DOC FILE ===" << endl;
    fs.close();
}




void Person :: timXe(vehicleshash* hash){
    system("cls");
    cout << "\n=== TIM KIEM XE THEO BIEN SO ===\n";
    
    cout << "Nhap bien so xe (VD: 29-A1-12345): ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hash->find(bienSo);
    if (xe) {
        xe->truyxuatLoi();
    } else {
        cout << "\nKhong tim thay xe co bien so: " << bienSo << endl;
    }
    pause();
}

void Person :: truyvanCCCD(HashTable<Person>* HashTable){
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