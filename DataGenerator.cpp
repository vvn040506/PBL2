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
// Khởi tạo random seed
void DataGenerator::initRandom() {
    static bool initialized = false;
    if (!initialized) {
        srand(time(0));
        initialized = true;
    }
}

// Sinh biển số ngẫu nhiên
string DataGenerator::generateBienSo() {
    //initRandom();
    
    string provinces[] = {
        "29", "30", "31", "32", "33",  // Hà Nội
        "35", "36", "37", "38",         // Miền Trung
        "41", "50", "51", "52",         // TP.HCM
        "60", "61", "72",               // Miền Nam
        "15", "16", "17", "18",         // Hải Phòng, Thái Bình
        "43", "47", "48", "49"          // Đà Nẵng, Tây Nguyên
    };
    
    string types[] = {"A1", "A2", "B1", "B2", "C1", "C2", "D1", "D2"};
    
    string province = provinces[rand() % 24];
    string type = types[rand() % 8];
    
    // Số từ 10000 đến 99999
    int number = 10000 + (rand() % 90000);
    
    return province + "-" + type + "-" + to_string(number);
}

// Sinh ngày ngẫu nhiên (năm 2024-2025)
string DataGenerator::generateNgay() {
    initRandom();
    
    int ngay = 1 + (rand() % 28);  // 1-28
    int thang = 1 + (rand() % 12); // 1-12
    int nam = 2024 + (rand() % 2); // 2024-2025
    
    string d = (ngay < 10) ? "0" + to_string(ngay) : to_string(ngay);
    string m = (thang < 10) ? "0" + to_string(thang) : to_string(thang);
    
    return d + "-" + m + "-" + to_string(nam);
}

// Sinh CCCD ngẫu nhiên (12 số)
string DataGenerator::generateCCCD() {
    initRandom();
    
    string cccd = "";
    for (int i = 0; i < 12; i++) {
        cccd += to_string(rand() % 10);
    }
    return cccd;
}

// Sinh SĐT ngẫu nhiên
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

// Sinh tên ngẫu nhiên
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

// Sinh địa chỉ ngẫu nhiên
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
// Tạo dữ liệu xe mẫu


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

// Tạo 50,000 bản ghi cho cccd.txt và bienso.txt
void DataGenerator::taoDuLieuMau(const string& cccdFile, const string& biensoFile, int soLuong) {
    initRandom();

    // Danh sách để lưu trữ tất cả biển số
    Mylist<string> allBienSo;

    // Tạo file cccd.txt
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

        // Tạo 1-5 biển số cho mỗi người
        int numBienSo = 1 + (rand() % 5);
        string bienSoStr;
        for (int j = 0; j < numBienSo; j++) {
            string bienSo = generateBienSo();
            // Kiểm tra trùng lặp
            while (bienSoDaTonTai(allBienSo, bienSo)) {
                bienSo = generateBienSo();
            }
            allBienSo.push_back(bienSo);
            bienSoStr += (j > 0 ? " " : "") + bienSo;
        }

        // Ghi vào file cccd.txt
        cccdOut << cccd << " | " << bienSoStr << " | " << ten << " | " << diachi << " | " << sdt << endl;
    }
    cccdOut.close();
    cout << "Da tao " << soLuong << " ban ghi trong " << cccdFile << endl;

    // Tạo file bienso.txt
    ofstream biensoOut(biensoFile);
    if (!biensoOut.is_open()) {
        cout << "Khong the mo file " << biensoFile << endl;
        return;
    }

    // Chọn ngẫu nhiên từ danh sách biển số
    int totalBienSo = allBienSo.size();
    int soLuongBienso = min(totalBienSo, soLuong); // Tối đa số bản ghi bằng số biển số
    Node<string>* current = allBienSo.begin();
    for (int i = 0; i < soLuongBienso && current != nullptr; i++) {
        string bienSo = current->getdata();
        string loiStr;

        // Tạo 0-5 lỗi vi phạm
        int numLoi = rand() % 6;
        for (int j = 0; j < numLoi; j++) {
            loiStr += (j > 0 ? " " : "") + generateLoi() + " " + generateNgay();
        }

        // Ghi vào file bienso.txt
        biensoOut << bienSo << (loiStr.empty() ? "" : " | " + loiStr) << endl;
        current = current->getnext();
    }
    biensoOut.close();
    cout << "Da tao " << soLuongBienso << " ban ghi trong " << biensoFile << endl;
}

void DataGenerator::taoXeMau(vehicleshash* hashtableXe, Mylist<Violation>& dsGop, int soLuong, HashTable<Person>& dsNguoi) {
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


void DataGenerator::docFileCCCD(const string& filename, HashTable<Person>& dsNguoi) {
    initRandom(); // ✅ Khởi tạo random seed
    
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

        // Loại bỏ khoảng trắng thừa
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

        // Thêm biển số
        stringstream bienSoSS(bienSoStr);
        string bienSo;
        while (bienSoSS >> bienSo) {
            bienSo.erase(0, bienSo.find_first_not_of(" \t"));
            bienSo.erase(bienSo.find_last_not_of(" \t") + 1);
            
            if (bienSo.empty() || !isValidBienSo(bienSo)) {
                continue;
            }

            // Tìm xe trong hashtableXe (đã được load từ bienso.txt)
            Xe* xeGoc = hashtableXe->find(bienSo);
            
            if (xeGoc != nullptr) {
                // Xe đã tồn tại, copy thông tin xe (bao gồm cả lỗi)
                Xe* xe = nullptr;
                
                if (xeGoc->getLS() == "Motor") {
                    Motor* motor = new Motor();
                    motor->setBienSo(bienSo);
                    motor->danhSachMucPhat = dsMucPhatMotor;
                    
                    // ✅ Copy từng lỗi thủ công
                    Node<Pair>* loiNode = xeGoc->dsLoi.begin();
                    while (loiNode != nullptr) {
                        motor->dsLoi.push_back(loiNode->getdata());
                        loiNode = loiNode->getnext();
                    }
                    
                    xe = motor;
                } else {
                    Car* car = new Car();
                    car->setBienSo(bienSo);
                    car->danhSachMucPhat = dsMucPhatCar;
                    
                    // ✅ Copy từng lỗi thủ công
                    Node<Pair>* loiNode = xeGoc->dsLoi.begin();
                    while (loiNode != nullptr) {
                        car->dsLoi.push_back(loiNode->getdata());
                        loiNode = loiNode->getnext();
                    }
                    
                    xe = car;
                }
                
                Person::phanTichBienSo(bienSo, *xe);
                person.getXe()->insertToHash(xe);
            } else {
                // Xe chưa tồn tại, tạo mới (không có lỗi)
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

void DataGenerator::docFileBienSo(const string& filename, vehicleshash* hashtableXe) {
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

        // Loại bỏ khoảng trắng
        bienSo.erase(0, bienSo.find_first_not_of(" \t"));
        bienSo.erase(bienSo.find_last_not_of(" \t") + 1);

        // Random tạo Motor hoặc Car (50-50)
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

        // Đọc lỗi vi phạm
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
                
                if (currentToken.length() == 10 && 
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
                    
                    if (!tenLoi.empty()) {
                        Pair loiPair(tenLoi, currentToken);
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
}
