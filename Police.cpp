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
                dsPolice->insert(id_police, Pair(bienso, ngay));
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
    
    pause();
}

void Police :: xoaloiXe(vehicleshash* hashtableXe){
    /*Xe* X = Hash->find(bienSo);

    if (!X) {
        cout <<"bien so xe khong ton tai " <<endl;
        return;
    }
    X->dongPhat(loiVP,ngayVP);
    cout <<"Da xoa loi thanh cong"<<endl;*/
    system("cls");
    cout << "\n=== XOA LOI VI PHAM (NEU GHI NHAM) ===\n";
    
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

void Police :: themxeMoi(vehicleshash* hashtableXe){
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
    
    hashtableXe->insertToHash(xe);
    cout << "\n[THANH CONG] Da them xe vao he thong!" << endl;
    cout << "\n--- NEW VEHICLES INFO ---" << endl;
    cout << "Bien so: " << xe->getbienSo() << endl;
    cout << "Thanh pho: " << xe->getTP() << endl;
    cout << "Loai xe: " << xe->getLS() << endl;
    
    // Thử tìm lại ngay
    Xe* test = hashtableXe->find(xe->getbienSo());
    if (test) {
        cout << "Tim thay xe!" << endl;
    } else {
        cout << "KHONG tim thay xe!" << endl;
    }
    pause();
}

