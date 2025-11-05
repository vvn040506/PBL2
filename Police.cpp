#include<iostream>
#include"Police.h"
#include "main1.h"

using namespace std;
HashTable<Pair>* Police::dsPolice = new HashTable<Pair>(1000);


Police::Police(){ id_police = " "; }
Police::~Police(){}

Police::Police(const string& id) : id_police(id) {}
string Police::getID() { return id_police; }

void Police::addPoliceWork(const string& id_police, const string& bienso, const string& ngay){
            if(dsPolice != nullptr){
                dsPolice->insert(id_police, Pair(bienso, ngay,false));
            }
        }
void Police::showPoliceWork(const string& id){
            int pos = dsPolice->hash_function(id);
            for(Node<Pair> *x = dsPolice->buckets[pos].begin(); x != dsPolice->buckets[pos].end(); x = x->getnext()){
                cout << "Da nhap vao bien so: " << x->getdata().key << " - Ngay: " << x->getdata().value << endl;
            }
        }
Mylist<Pair> Police::getPoliceWork(const string& id){
            if(dsPolice != nullptr){
                int pos = dsPolice->hash_function(id);
                return dsPolice->buckets[pos];
            }
            return Mylist<Pair>();
        }

void Police::themloiXe(vehicleshash* Hash){
    system("cls");
    cout << "\n=== THEM LOI VI PHAM CHO XE ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashtableXe->find(bienSo);
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
    
    capNhatFileBienSo(xe);
    
    pause();
}

void Police :: dongPhat(vehicleshash* hashtableXe){
    system("cls");
    cout << "\n=== XOA LOI VI PHAM ===\n";
    
    cout << "Nhap bien so xe: ";
    string bienSo;
    getline(cin, bienSo);
    
    Xe* xe = hashtableXe->find(bienSo);
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
        if(loi->getdata().State == false){
            cout << stt++ << ". " << loi->getdata().key 
                << " - " << loi->getdata().value << endl;
            loi = loi->getnext();
        }
    }
    
    cout << "\nNhap ten loi can dong phat: ";
    string tenLoi;
    getline(cin, tenLoi);
    
    cout << "Nhap ngay vi pham: ";
    string ngayVP;
    getline(cin, ngayVP);
    
    // Xóa lỗi
    xe->dongPhat(tenLoi, ngayVP);
    cout << "\n[THANH CONG] Da dong phat!" << endl;
    
    capNhatFileBienSo(xe);
    
    pause();
}

void Police :: themxeMoi(vehicleshash* hashtableXe){
    system("cls");
    system("cls");
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
    
    // Nhập thông tin
    string bienSo, cccd, ten, sdt, diachi;
    cout << "Nhap bien so xe (VD: 29-A1-12345): ";
    getline(cin, bienSo);
    
    if (hashtableXe->find(bienSo) != nullptr) {
        cout << "Bien so nay da ton tai trong he thong!" << endl;
        pause();
        return;
    }
    
    cout << "Nhap CCCD chu xe: ";
    getline(cin, cccd);
    cout << "Nhap ten chu xe: ";
    getline(cin, ten);
    cout << "Nhap so dien thoai: ";
    getline(cin, sdt);
    cout << "Nhap dia chi: ";
    getline(cin, diachi);
    
    // Tạo và thêm xe vào hashtableXe
    Xe* xe = taoXeMoi(bienSo, loai);
    hashtableXe->insertToHash(xe);
    
    // Ghi vào file bienso.txt
    ofstream biensoFile(finalbienSo, ios::app);
    if (biensoFile.is_open()) {
        biensoFile << bienSo << endl;
        biensoFile.close();
        cout << "[OK] Da ghi vao file bienso.txt" << endl;
    }
    
    // Thêm xe vào Person và cập nhật file cccd.txt
    themXeVaoPerson(cccd, bienSo, ten, sdt, diachi, loai);
    
    cout << "\n[THANH CONG] Da them xe vao he thong!" << endl;
    cout << "\n--- THONG TIN XE MOI ---" << endl;
    cout << "Bien so: " << xe->getbienSo() << endl;
    cout << "Thanh pho: " << xe->getTP() << endl;
    cout << "Loai xe: " << xe->getLS() << endl;
    cout << "Chu xe: " << ten << " (CCCD: " << cccd << ")" << endl;
    
    pause();
}

void Police :: menu() {
    system("cls");
    cout << "========================================" << endl;
    cout << "           MENU CONG AN                 " << endl;
    cout << "========================================" << endl;
    cout << "1. Xem thong ke tong quan" << endl;
    cout << "2. Tim xe theo bien so" << endl;
    cout << "3. Them loi vi pham cho xe" << endl;
    cout << "4. Dong phat" << endl;
    cout << "5. Them xe moi vao he thong" << endl;
    cout << "0. Quay lai" << endl;
    cout << "========================================" << endl;
    cout << "Nhap lua chon: ";
}

void Person :: menu(){}

void capNhatFileBienSo(Xe* xe) {
    string bienSo = xe->getbienSo();
    
    ifstream fileIn(finalbienSo);
    stringstream buffer;
    string line;
    bool updated = false;
    
    while (getline(fileIn, line)) {
        if (line.substr(0, bienSo.length()) == bienSo && !updated) {
            string newLine = bienSo;
            Node<Pair>* currentLoi = xe->dsLoi.begin();
            
            if (currentLoi != nullptr) {
                newLine += " |";
                while (currentLoi != nullptr) {
                    newLine += " " + currentLoi->getdata().key + " " 
                             + currentLoi->getdata().value + " ";
                    
                    // Ghi rõ ràng
                    if (currentLoi->getdata().State) {
                        newLine += "DD";
                    } else {
                        newLine += "CD";
                    }
                    
                    currentLoi = currentLoi->getnext();
                    if (currentLoi != nullptr) {
                        newLine += " |";
                    }
                }
            }
            
            line = newLine;
            updated = true;
        }
        buffer << line << endl;
    }
    fileIn.close();
    
    ofstream fileOut(finalbienSo);
    fileOut << buffer.str();
    fileOut.close();
}

void capNhatFileCCCD(const string& cccd, const string& bienSo) {
    ifstream fileIn(finalCCCD);
    stringstream buffer;
    string line;
    bool updated = false;
    
    while (getline(fileIn, line)) {
        if (line.find(cccd) != string::npos && !updated) {
            size_t firstPipe = line.find('|');
            size_t secondPipe = line.find('|', firstPipe + 1);
            
            if (firstPipe != string::npos && secondPipe != string::npos) {
                string bienSoPart = line.substr(firstPipe + 1, secondPipe - firstPipe - 1);
                bienSoPart += " " + bienSo;
                line = line.substr(0, firstPipe + 1) + bienSoPart + line.substr(secondPipe);
                updated = true;
            }
        }
        buffer << line << endl;
    }
    fileIn.close();
    
    ofstream fileOut(finalCCCD);
    fileOut << buffer.str();
    fileOut.close();
}

Xe* taoXeMoi(const string& bienSo, int loai) {
    Xe* xe = nullptr;
    if (loai == 1) {
        Motor* m = new Motor();
        m->setBienSo(bienSo);
        m->danhSachMucPhat = dsMucPhatMotor;
        Person::phanTichBienSo(bienSo, *m);
        xe = m;
    } else {
        Car* c = new Car();
        c->setBienSo(bienSo);
        c->danhSachMucPhat = dsMucPhatCar;
        Person::phanTichBienSo(bienSo, *c);
        xe = c;
    }
    return xe;
}


void themXeVaoPerson(const string& cccd, const string& bienSo, const string& ten, 
                     const string& sdt, const string& diachi, int loai) {
    try {
        // CCCD đã tồn tại
        Person &p = getByCCCD(cccd, *hashtableNguoi);
        Xe* xeCopy = taoXeMoi(bienSo, loai);
        p.getXe()->insertToHash(xeCopy);
        
        capNhatFileCCCD(cccd, bienSo);
        cout << "[OK] Da them xe vao chu xe co san (CCCD: " << cccd << ")" << endl;
        
    } catch (...) {
        // CCCD chưa có, tạo mới
        Person newPerson(cccd, ten, sdt, diachi);
        Xe* xeCopy = taoXeMoi(bienSo, loai);
        newPerson.getXe()->insertToHash(xeCopy);
        hashtableNguoi->insert(cccd, newPerson);
        
        // Ghi vào file cccd.txt
        ofstream cccdFile(finalCCCD, ios::app);
        if (cccdFile.is_open()) {
            cccdFile << cccd << " | " << bienSo << " | " << ten << " | " << diachi << " | " << sdt << endl;
            cccdFile.close();
            cout << "[OK] Da ghi vao file cccd.txt" << endl;
        } else {
            cout << "[LOI] Khong the mo file cccd.txt" << endl;
        }
    }
}
