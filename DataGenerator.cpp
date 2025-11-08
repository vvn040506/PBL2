#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "DataGenerator.h"
#include "Mylist.h"
#include "Violation.h"
#include "Xe.h"
#include "Person.h"
#include "HashFunction.h"
#include "HashTable.h"
#include <regex>
#include "main1.h"


bool isValidBienSo(const string& bienSo) {
    regex bienSoPattern(R"(\d{2}-[A-Z]\d-\d{5})");
    return regex_match(bienSo, bienSoPattern);
}

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern Mylist<Violation> dsMucPhatMotor;
extern Mylist<Violation> dsMucPhatCar;

void DataGenerator::initRandom() {
    static bool initialized = false;
    if (!initialized) {
        srand(time(0));
        initialized = true;
    }
}

bool DataGenerator::generateState(){
    initRandom();

    if (rand () % 2 == 0) return false;
    return true;
}
// Sinh biển số ngẫu nhiên
string DataGenerator::generateBienSo() {
    //initRandom();
    
    string provinces[] = {
        "29", "30", "31", "32", "33",
        "35", "36", "37", "38",        
        "41", "50", "51", "52",        
        "60", "61", "72",              
        "15", "16", "17", "18",         
        "43", "47", "48", "49"          
    };
    
    string types[] = {"A1", "A2", "B1", "B2", "C1", "C2", "D1", "D2"};
    
    string province = provinces[rand() % 24];
    string type = types[rand() % 8];
    
    // Số từ 10000 đến 99999
    int number = 10000 + (rand() % 90000);
    
    return province + "-" + type + "-" + to_string(number);
}


string DataGenerator::generateNgay() {
    initRandom();
    
    int ngay = 1 + (rand() % 28); 
    int thang = 1 + (rand() % 12);
    int nam = 2024 + (rand() % 2);
    
    string d = (ngay < 10) ? "0" + to_string(ngay) : to_string(ngay);
    string m = (thang < 10) ? "0" + to_string(thang) : to_string(thang);
    
    return d + "-" + m + "-" + to_string(nam);
}

string DataGenerator::generateCCCD() {
    initRandom();
    
    string cccd = "";
    for (int i = 0; i < 12; i++) {
        cccd += to_string(rand() % 10);
    }
    return cccd;
}


string DataGenerator::generateSDT() {
    initRandom();
    
    string prefixes[] = {"090", "091", "092", "093", "094", 
                        "096", "097", "098", "032", "033", 
                        "034", "035", "036", "037", "038", "039"};
    
    string prefix = prefixes[rand() % 16];
    string sdt = prefix;
    
    for (int i = 0; i < 7; i++) {
        sdt += to_string(rand() % 10);
    }
    
    return sdt;
}

string DataGenerator::generateTen() {
    initRandom();
    
    string ho[] = {"Nguyen", "Tran", "Le", "Pham", "Hoang", 
                   "Phan", "Vu", "Dang", "Bui", "Do", "Ngo", "Duong"};
    
    string tenDem[] = {"Van", "Thi", "Huu", "Duc", "Ngoc", 
                       "Minh", "Thanh", "Kim", "Anh", "Hong"};
    
    string ten[] = {"An", "Binh", "Chau", "Dung", "Hai", 
                    "Khoa", "Linh", "Nam", "Phong", "Quan", 
                    "Son", "Tuan", "Vu", "Long", "Hieu"};
    
    return ho[rand() % 12] + " " + 
           tenDem[rand() % 10] + " " + 
           ten[rand() % 15];
}

string DataGenerator::generateDiaChi() {
    initRandom();
    
    string duong[] = {"Nguyen Trai", "Le Loi", "Tran Hung Dao", 
                      "Hai Ba Trung", "Ly Thuong Kiet", "Hoang Hoa Tham"};
    
    string quan[] = {"Quan 1", "Quan 3", "Quan 5", "Quan 10", 
                     "Dong Da", "Hai Ba Trung", "Cau Giay", "Thanh Xuan"};
    
    string thanhPho[] = {"Ha Noi", "TP Ho Chi Minh", "Da Nang", "Hai Phong"};
    
    int soNha = 1 + (rand() % 999);
    
    return to_string(soNha) + " " + 
           duong[rand() % 6] + ", " + 
           quan[rand() % 8] + ", " + 
           thanhPho[rand() % 4];
}
string DataGenerator::generateLoi(){
    string loi[] = {"di nguoc chieu","di tren via he", "vuot toc do","do via he","khong mang bang lai","do po","di sai lan duong"};
    return loi [rand() % 5];
}


bool bienSoDaTonTai(Mylist<string>& bienSoList, const string& bienSo) {
    Node<string>* current = bienSoList.begin();
    while (current != nullptr) {
        if (current->getdata() == bienSo) {
            return true;
        }
        current = current->getnext();
    }
    return false;
}

void DataGenerator::taoDuLieuMau(const string& cccdFile, const string& biensoFile, int soLuong) {
    initRandom();

    Mylist<string> allBienSo;

    ofstream cccdOut(cccdFile);
    if (!cccdOut.is_open()) {
        cout << "Khong the mo file " << cccdFile << endl;
        return;
    }

    for (int i = 0; i < soLuong; i++) {
        string cccd = generateCCCD();
        string ten = generateTen();
        string diachi = generateDiaChi();
        string sdt = generateSDT();

        int numBienSo = 1 + (rand() % 5);
        string bienSoStr;
        for (int j = 0; j < numBienSo; j++) {
            string bienSo = generateBienSo();
            while (bienSoDaTonTai(allBienSo, bienSo)) {
                bienSo = generateBienSo();
            }
            allBienSo.push_back(bienSo);
            bienSoStr += (j > 0 ? " " : "") + bienSo;
        }

        cccdOut << cccd << " | " << bienSoStr << " | " << ten << " | " << diachi << " | " << sdt << endl;
    }
    cccdOut.close();
    cout << "Da tao " << soLuong << " ban ghi trong " << cccdFile << endl;

    ofstream biensoOut(biensoFile);
    if (!biensoOut.is_open()) {
        cout << "Khong the mo file " << biensoFile << endl;
        return;
    }

    int totalBienSo = allBienSo.size();
    int soLuongBienso = min(totalBienSo, soLuong);
    Node<string>* current = allBienSo.begin();
    
    int xeDaDong = 0;
    int xeChuaDong = 0;
    int xeKhongLoi = 0;
    
    for (int i = 0; i < soLuongBienso && current != nullptr; i++) {
        string bienSo = current->getdata();
        
        int coLoi = rand() % 100;
        if (coLoi < 30) {
            int numLoi = 1 + (rand() % 3);  // 1-3 lỗi
            biensoOut << bienSo << " |";
            
            bool xeNayCoLoiChuaDong = false;
            
            for (int j = 0; j < numLoi; j++) {
                string tenLoi = generateLoi();
                string ngay = generateNgay();
                
                bool daDong = (rand() % 100 < 60);
                
                if (!daDong) {
                    xeNayCoLoiChuaDong = true;
                }
                
                string trangThai;
                if (!daDong) trangThai = "CD";
                    else trangThai = "DD";
                
                biensoOut << " " << tenLoi << " " << ngay << " " << trangThai;
                if (j < numLoi - 1) biensoOut << " |";
            }
            biensoOut << endl;
            
            if (xeNayCoLoiChuaDong) {
                xeChuaDong++;
            } else {
                xeDaDong++;
            }
        } else {
            biensoOut << bienSo << endl;
            xeKhongLoi++;
        }
        
        current = current->getnext();
    }
    biensoOut.close();
    
    cout << "Da tao " << soLuongBienso << " ban ghi trong " << biensoFile << endl;
    cout << "  - Xe khong loi: " << xeKhongLoi << endl;
    cout << "  - Xe da dong het phat: " << xeDaDong << endl;
    cout << "  - Xe con no phat: " << xeChuaDong << endl;
}

void DataGenerator::docFileBienSo(const string& filename, vehicleshash* hashtableXe) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }
    
    string line;
    int lineCount = 0;
    int successCount = 0;
    int loiDaDong = 0;
    int loiChuaDong = 0;
    
    while (getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;

        size_t pipePos = line.find('|');
        string bienSo;
        string loiPart;
        
        if (pipePos != string::npos) {
            bienSo = line.substr(0, pipePos);
            loiPart = line.substr(pipePos + 1);
        } else {
            bienSo = line;
            loiPart = "";
        }

        bienSo.erase(0, bienSo.find_first_not_of(" \t"));
        bienSo.erase(bienSo.find_last_not_of(" \t") + 1);

        Xe* xe = nullptr;
        bool isMotor = (rand() % 2 == 0);
        
        if (isMotor) {
            Motor* motor = new Motor();
            motor->setBienSo(bienSo);
            motor->danhSachMucPhat = dsMucPhatMotor;
            xe = motor;
        } else {
            Car* car = new Car();
            car->setBienSo(bienSo);
            car->danhSachMucPhat = dsMucPhatCar;
            xe = car;
        }
        
        Person::phanTichBienSo(bienSo, *xe);

        if (!loiPart.empty()) {
            stringstream ss(loiPart);
            string token;
            Mylist<string> tokens;  
            
            while (ss >> token) {
                tokens.push_back(token);
            }
            
            Node<string>* current = tokens.begin();
            int index = 0;
            
            while (current != nullptr) {
                string currentToken = current->getdata();
                
                bool laTrangThai = (currentToken == "DD" || currentToken == "CD");
                
                if (!laTrangThai && currentToken.length() == 10 && 
                    currentToken[2] == '-' && 
                    currentToken[5] == '-' &&
                    isdigit(currentToken[0]) && 
                    isdigit(currentToken[1])) {
                    
                    string tenLoi = "";
                    Node<string>* prev = tokens.begin();
                    int prevIndex = 0;
                    int startIdx = 0;
                    
                    while (prev != nullptr && prevIndex < index) {
                        if (prev->getdata() == "|" || 
                            (prev->getdata().length() == 10 && 
                             prev->getdata()[2] == '-' && 
                             prev->getdata()[5] == '-' &&
                             isdigit(prev->getdata()[0]))) {
                            startIdx = prevIndex + 1;
                        }
                        prev = prev->getnext();
                        prevIndex++;
                    }
                    
                    Node<string>* nameNode = tokens.begin();
                    int nameIdx = 0;
                    while (nameNode != nullptr && nameIdx < index) {
                        if (nameIdx >= startIdx && nameNode->getdata() != "|") {
                            if (!tenLoi.empty()) tenLoi += " ";
                            tenLoi += nameNode->getdata();
                        }
                        nameNode = nameNode->getnext();
                        nameIdx++;
                    }
                    
                    bool trangThaiDong = false; 
                    Node<string>* nextNode = current->getnext();
                    if (nextNode != nullptr) {
                        string trangThaiStr = nextNode->getdata();
                        if (trangThaiStr == "DD") {
                            trangThaiDong = true;
                            loiDaDong++;
                        } else if (trangThaiStr == "CD") {
                            trangThaiDong = false;
                            loiChuaDong++;
                        } else {
                            trangThaiDong = false;
                            loiChuaDong++;
                        }
                    } else {
                        trangThaiDong = false;
                        loiChuaDong++;
                    }
                    
                    if (!tenLoi.empty()) {
                        Pair loiPair(tenLoi, currentToken, trangThaiDong);
                        xe->dsLoi.push_back(loiPair);
                    }
                }
                
                current = current->getnext();
                index++;
            }
        }

        hashtableXe->insertToHash(xe);
        successCount++;

        if (lineCount % 1000 == 0) {
            cout << "Da doc " << lineCount << " dong..." << endl;
        }
    }
    
    file.close();
    cout << "Da doc xong " << successCount << "/" << lineCount << " ban ghi tu file bienso.txt" << endl;
    cout << "  - Loi da dong phat: " << loiDaDong << endl;
    cout << "  - Loi chua dong phat: " << loiChuaDong << endl;
}

void DataGenerator::docFileCCCD(const string& filename, HashTable<Person>& dsNguoi) {
    initRandom(); 
    
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file " << filename << endl;
        return;
    }
    
    string line;
    int lineCount = 0;
    int successCount = 0;
    
    while (getline(file, line)) {
        lineCount++;
        if (line.empty()) continue;

        stringstream ss(line);
        string cccd, bienSoStr, ten, diachi, sdt;
        getline(ss, cccd, '|');
        getline(ss, bienSoStr, '|');
        getline(ss, ten, '|');
        getline(ss, diachi, '|');
        getline(ss, sdt);

        cccd.erase(0, cccd.find_first_not_of(" \t"));
        cccd.erase(cccd.find_last_not_of(" \t") + 1);
        ten.erase(0, ten.find_first_not_of(" \t"));
        ten.erase(ten.find_last_not_of(" \t") + 1);
        diachi.erase(0, diachi.find_first_not_of(" \t"));
        diachi.erase(diachi.find_last_not_of(" \t") + 1);
        sdt.erase(0, sdt.find_first_not_of(" \t"));
        sdt.erase(sdt.find_last_not_of(" \t") + 1);

        if (cccd.empty() || ten.empty() || diachi.empty() || sdt.empty()) {
            continue;
        }

        Person person(cccd, ten, sdt, diachi);

        stringstream bienSoSS(bienSoStr);
        string bienSo;
        while (bienSoSS >> bienSo) {
            bienSo.erase(0, bienSo.find_first_not_of(" \t"));
            bienSo.erase(bienSo.find_last_not_of(" \t") + 1);
            
            if (bienSo.empty() || !isValidBienSo(bienSo)) {
                continue;
            }

            Xe* xeGoc = hashtableXe->find(bienSo);
            
            if (xeGoc != nullptr) {
                Xe* xe = nullptr;
                
                if (xeGoc->getLS() == "Motor") {
                    Motor* motor = new Motor();
                    motor->setBienSo(bienSo);
                    motor->danhSachMucPhat = dsMucPhatMotor;
                    
                    Node<Pair>* loiNode = xeGoc->dsLoi.begin();
                    while (loiNode != nullptr) {
                        Pair loiMoi(loiNode->getdata().key, 
                                   loiNode->getdata().value, 
                                   loiNode->getdata().State); 
                        motor->dsLoi.push_back(loiMoi);
                        loiNode = loiNode->getnext();
                    }
                    
                    xe = motor;
                } else {
                    Car* car = new Car();
                    car->setBienSo(bienSo);
                    car->danhSachMucPhat = dsMucPhatCar;
                    
                    Node<Pair>* loiNode = xeGoc->dsLoi.begin();
                    while (loiNode != nullptr) {
                        Pair loiMoi(loiNode->getdata().key, 
                                   loiNode->getdata().value, 
                                   loiNode->getdata().State);  
                        car->dsLoi.push_back(loiMoi);
                        loiNode = loiNode->getnext();
                    }
                    
                    xe = car;
                }
                
                Person::phanTichBienSo(bienSo, *xe);
                person.getXe()->insertToHash(xe);
            } else {
                Xe* xe = nullptr;
                bool isMotor = (successCount % 2 == 0);
                
                if (isMotor) {
                    Motor* motor = new Motor();
                    motor->setBienSo(bienSo);
                    motor->danhSachMucPhat = dsMucPhatMotor;
                    xe = motor;
                } else {
                    Car* car = new Car();
                    car->setBienSo(bienSo);
                    car->danhSachMucPhat = dsMucPhatCar;
                    xe = car;
                }
                
                Person::phanTichBienSo(bienSo, *xe);
                person.getXe()->insertToHash(xe);
            }
        }

        try {
            dsNguoi.insert(cccd, person);
            successCount++;
        } catch (...) {
            continue;
        }

        if (lineCount % 1000 == 0) {
            cout << "Da doc " << lineCount << " dong..." << endl;
        }
    }
    
    file.close();
    cout << "Da doc xong " << successCount << "/" << lineCount << " ban ghi tu file cccd.txt" << endl;
}

void DataGenerator::taoXeMau(vehicleshash* hashtableXe, int soLuong, HashTable<Person>& dsNguoi) {
    cout << "\n=== BAT DAU DOC BIENSO.TXT ===" << endl;
    docFileBienSo(finalbienSo, hashtableXe);
    
    int xeCoLoiTrongHash = 0;
    int xeKhongLoiTrongHash = 0;
    for (int i = 0; i < hashtableXe->get1(); i++) {
        for (int j = 0; j < hashtableXe->get2(); j++) {
            for (int k = 0; k < hashtableXe->get3(); k++) {
                Node<Xe*>* current = hashtableXe->table[i][j][k].begin();
                while (current != nullptr) {
                    if (current->getdata()->dsLoi.size() > 0) {
                        xeCoLoiTrongHash++;
                    } else {
                        xeKhongLoiTrongHash++;
                    }
                    current = current->getnext();
                }
            }
        }
    }
    cout << "[KIEM TRA] Trong hashtableXe: " << xeCoLoiTrongHash << " xe co loi, " 
         << xeKhongLoiTrongHash << " xe khong loi" << endl;
    
    cout << "\n=== BAT DAU DOC CCCD.TXT ===" << endl;
    docFileCCCD(finalCCCD, dsNguoi);
    
    cout << "\n=== HOAN TAT ===" << endl;
    cout << "Da tai du lieu tu file vao hashtable" << endl;
}

string DataGenerator ::generatePolice(){
    initRandom();

    int id = 100000 + rand() % 899999;
    string pass;
    int n = 6 + rand() % 3;
    const string c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i < n ; i++){
        if (rand() % 100 < 70)
            pass += to_string(rand() % 9);
                else pass += c[rand() % 52];
    }
    return to_string(id) + " " + pass;
}

void docFilePolice(const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Khong the mo file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, pass;

        if (ss >> id >> pass) {
            Police::dsPolice->insert(id, Pair(id, pass, false));
        }
    }

    file.close();
    cout << "Da tai danh sach canh sat tu file: " << filename << endl;
}
