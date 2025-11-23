#include "DataGenerator.h"
#include "Police.h"
#include "Mylist.h"
#include "HashFunction.h"
#include "pair.hpp"
#include "Violation.h"
#include "Xe.h"
#include "Motor.h"
#include "Car.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QRegularExpression>

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern Mylist<Violation> dsMucPhatMotor;
extern Mylist<Violation> dsMucPhatCar;
extern QString finalbienSo;
extern QString finalCCCD;

bool isValidBienSo(const QString& bienSo) {
    QRegularExpression bienSoPattern(R"(\d{2}-[A-Z]\d-\d{5})");
    return bienSoPattern.match(bienSo).hasMatch();
}

void DataGenerator::initRandom() {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
}

bool DataGenerator::generateState(){
    initRandom();
    if (rand () % 2 == 0) return false;
    return true;
}

QString DataGenerator::generateBienSo() {
    QStringList provinces = {
        "29", "30", "31", "32", "33",  // Hà Nội
        "35", "36", "37", "38",         // Miền Trung
        "41", "50", "51", "52",         // TP.HCM
        "60", "61", "72",               // Miền Nam
        "15", "16", "17", "18",         // Hải Phòng, Thái Bình
        "43", "47", "48", "49"          // Đà Nẵng, Tây Nguyên
    };

    QStringList types = {"A1", "A2", "B1", "B2", "C1", "C2", "D1", "D2"};

    QString province = provinces.at(rand() % provinces.size());
    QString type = types.at(rand() % types.size());

    int number = 10000 + (rand() % 90000);

    return province + "-" + type + "-" + QString::number(number);
}

QString DataGenerator::generateNgay() {
    initRandom();

    int ngay = 1 + (rand() % 28);
    int thang = 1 + (rand() % 12);
    int nam = 2024 + (rand() % 2);

    QString d = (ngay < 10) ? "0" + QString::number(ngay) : QString::number(ngay);
    QString m = (thang < 10) ? "0" + QString::number(thang) : QString::number(thang);

    return d + "-" + m + "-" + QString::number(nam);
}

QString DataGenerator::generateCCCD() {
    initRandom();

    QString cccd = "";
    for (int i = 0; i < 12; i++) {
        cccd += QString::number(rand() % 10);
    }
    return cccd;
}

QString DataGenerator::generateSDT() {
    initRandom();

    QStringList prefixes = {"090", "091", "092", "093", "094",
                            "096", "097", "098", "032", "033",
                            "034", "035", "036", "037", "038", "039"};

    QString prefix = prefixes.at(rand() % prefixes.size());
    QString sdt = prefix;

    for (int i = 0; i < 7; i++) {
        sdt += QString::number(rand() % 10);
    }

    return sdt;
}

QString DataGenerator::generateTen() {
    initRandom();

    QStringList ho = {"Nguyen", "Tran", "Le", "Pham", "Hoang",
                      "Phan", "Vu", "Dang", "Bui", "Do", "Ngo", "Duong"};

    QStringList tenDem = {"Van", "Thi", "Huu", "Duc", "Ngoc",
                          "Minh", "Thanh", "Kim", "Anh", "Hong"};

    QStringList ten = {"An", "Binh", "Chau", "Dung", "Hai",
                       "Khoa", "Linh", "Nam", "Phong", "Quan",
                       "Son", "Tuan", "Vu", "Long", "Hieu"};

    return ho.at(rand() % ho.size()) + " " +
           tenDem.at(rand() % tenDem.size()) + " " +
           ten.at(rand() % ten.size());
}

QString DataGenerator::generateDiaChi() {
    initRandom();

    QStringList duong = {"Nguyen Trai", "Le Loi", "Tran Hung Dao",
                         "Hai Ba Trung", "Ly Thuong Kiet", "Hoang Hoa Tham"};

    QStringList quan = {"Quan 1", "Quan 3", "Quan 5", "Quan 10",
                        "Dong Da", "Hai Ba Trung", "Cau Giay", "Thanh Xuan", "Hoa Cuong", "Hai Chau"};

    QStringList thanhPho = {"Ha Noi", "TP Ho Chi Minh", "Da Nang", "Hai Phong"};

    int soNha = 1 + (rand() % 999);

    return QString::number(soNha) + " " +
           duong.at(rand() % duong.size()) + ", " +
           quan.at(rand() % quan.size()) + ", " +
           thanhPho.at(rand() % thanhPho.size());
}

QString DataGenerator::generateLoi() {
    QStringList loi = {"di nguoc chieu", "di tren via he", "vuot toc do", "do via he", "khong mang bang lai", "do po", "di sai lan duong"};
    return loi.at(rand() % loi.size());
}

QString DataGenerator::generatePolice()
{
    initRandom();

    int id = 100000 + rand() % 899999;
    QString pass;
    int n = 6 + rand() % 3;
    const QString c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < n; i++) {
        if (rand() % 100 < 70)
            pass += QString::number(rand() % 9);
        else
            pass += c[rand() % 52];
    }
    return QString::number(id) + " " + pass;
}

bool bienSoDaTonTai(Mylist<QString>& bienSoList, const QString& bienSo) {
    Node<QString>* current = bienSoList.begin();
    while (current != nullptr) {
        if (current->getdata() == bienSo) {
            return true;
        }
        current = current->getnext();
    }
    return false;
}

void DataGenerator::taoDuLieuMau(const QString& cccdFile, const QString& biensoFile, int soLuong) {
    initRandom();

    Mylist<QString> allBienSo;

    QFile cccdOut(cccdFile);
    if (!cccdOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << cccdFile;
        return;
    }

    QTextStream cccdStream(&cccdOut);
    for (int i = 0; i < soLuong; i++) {
        QString cccd = generateCCCD();
        QString ten = generateTen();
        QString diachi = generateDiaChi();
        QString sdt = generateSDT();

        int numBienSo = 1 + (rand() % 5);
        QString bienSoStr;
        for (int j = 0; j < numBienSo; j++) {
            QString bienSo = generateBienSo();
            while (bienSoDaTonTai(allBienSo, bienSo)) {
                bienSo = generateBienSo();
            }
            allBienSo.push_back(bienSo);
            bienSoStr += (j > 0 ? " " : "") + bienSo;
        }

        cccdStream << cccd << " | " << bienSoStr << " | " << ten << " | " << diachi << " | " << sdt << "\n";
    }
    cccdOut.close();
    qDebug() << "Da tao" << soLuong << "ban ghi trong" << cccdFile;

    QFile biensoOut(biensoFile);
    if (!biensoOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << biensoFile;
        return;
    }

    QTextStream biensoStream(&biensoOut);
    int totalBienSo = allBienSo.size();
    int soLuongBienso = qMin(totalBienSo, soLuong);
    Node<QString>* current = allBienSo.begin();

    int xeDaDong = 0;
    int xeChuaDong = 0;
    int xeKhongLoi = 0;

    for (int i = 0; i < soLuongBienso && current != nullptr; i++) {
        QString bienSo = current->getdata();

        int coLoi = rand() % 100;
        if (coLoi < 30) {
            int numLoi = 1 + (rand() % 3);
            biensoStream << bienSo << " |";

            bool xeNayCoLoiChuaDong = false;

            for (int j = 0; j < numLoi; j++) {
                QString tenLoi = generateLoi();
                QString ngay = generateNgay();

                bool daDong = (rand() % 100 < 60);

                if (!daDong) {
                    xeNayCoLoiChuaDong = true;
                }

                QString trangThai;
                if (!daDong) trangThai = "CD";
                else trangThai = "DD";

                biensoStream << " " << tenLoi << " " << ngay << " " << trangThai;
                if (j < numLoi - 1) biensoStream << " |";
            }
            biensoStream << "\n";

            if (xeNayCoLoiChuaDong) {
                xeChuaDong++;
            } else {
                xeDaDong++;
            }
        } else {
            biensoStream << bienSo << "\n";
            xeKhongLoi++;
        }

        current = current->getnext();
    }
    biensoOut.close();


    qDebug() << "Da tao" << soLuongBienso << "ban ghi trong" << biensoFile;
    qDebug() << "  - Xe khong loi:" << xeKhongLoi;
    qDebug() << "  - Xe da dong het phat:" << xeDaDong;
    qDebug() << "  - Xe con no phat:" << xeChuaDong;
}

void DataGenerator::docFileBienSo(const QString& filename, vehicleshash* hashtableXe) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << filename;
        return;
    }

    QTextStream in(&file);
    QString line;
    int lineCount = 0;
    int successCount = 0;
    int loiDaDong = 0;
    int loiChuaDong = 0;

    while (!in.atEnd()) {
        line = in.readLine();
        lineCount++;
        if (line.isEmpty()) continue;

        int pipePos = line.indexOf('|');
        QString bienSo;
        QString loiPart;

        if (pipePos != -1) {
            bienSo = line.left(pipePos);
            loiPart = line.mid(pipePos + 1);
        } else {
            bienSo = line;
            loiPart = "";
        }

        bienSo = bienSo.trimmed();

        Xe* xe = nullptr;
        bool isMotor = (rand() % 2 == 0);

        if (isMotor) {
            Motor* motor = new Motor();
            motor->setBienSo(bienSo);
            motor->setOwner("");
            motor->danhSachMucPhat = dsMucPhatMotor;
            xe = motor;
        } else {
            Car* car = new Car();
            car->setBienSo(bienSo);
            car->setOwner("");
            car->danhSachMucPhat = dsMucPhatCar;
            xe = car;
        }

        Person::phanTichBienSo(bienSo, *xe);

        if (!loiPart.isEmpty()) {
            QStringList tokens = loiPart.split(' ', Qt::SkipEmptyParts);

            for (int i = 0; i < tokens.size(); i++) {
                QString currentToken = tokens[i];

                bool laTrangThai = (currentToken == "DD" || currentToken == "CD");

                if (!laTrangThai && currentToken.length() == 10 &&
                    currentToken[2] == '-' &&
                    currentToken[5] == '-' &&
                    currentToken[0].isDigit() &&
                    currentToken[1].isDigit()) {

                    QString tenLoi = "";
                    int startIdx = 0;

                    for (int prevIndex = 0; prevIndex < i; prevIndex++) {
                        QString prevToken = tokens[prevIndex];
                        if (prevToken == "|" ||
                            (prevToken.length() == 10 &&
                             prevToken[2] == '-' &&
                             prevToken[5] == '-' &&
                             prevToken[0].isDigit())) {
                            startIdx = prevIndex + 1;
                        }
                    }

                    for (int nameIdx = startIdx; nameIdx < i; nameIdx++) {
                        if (tokens[nameIdx] != "|") {
                            if (!tenLoi.isEmpty()) tenLoi += " ";
                            tenLoi += tokens[nameIdx];
                        }
                    }

                    bool trangThaiDong = false;
                    if (i + 1 < tokens.size()) {
                        QString trangThaiStr = tokens[i + 1];
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

                    if (!tenLoi.isEmpty()) {
                        Pair loiPair(tenLoi, currentToken, trangThaiDong);
                        xe->dsLoi.push_back(loiPair);
                    }
                }
            }
        }

        hashtableXe->insertToHash(xe);
        successCount++;

        if (lineCount % 1000 == 0) {
            qDebug() << "Da doc" << lineCount << "dong...";
        }
    }

    file.close();
    qDebug() << "Da doc xong" << successCount << "/" << lineCount << "ban ghi tu file bienso.txt";
    qDebug() << "  - Loi da dong phat:" << loiDaDong;
    qDebug() << "  - Loi chua dong phat:" << loiChuaDong;
}
void DataGenerator::docFileCCCD(const QString& filename, HashTable<Person>& dsNguoi) {
    initRandom();

    int xeDaCapNhatOwner = 0;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << filename;
        return;
    }

    QTextStream in(&file);
    QString line;
    int lineCount = 0;
    int successCount = 0;

    while (!in.atEnd()) {
        line = in.readLine();
        lineCount++;
        if (line.isEmpty()) continue;

        QStringList parts = line.split('|');
        if (parts.size() < 5) continue;

        QString cccd = parts[0].trimmed();
        QString bienSoStr = parts[1].trimmed();
        QString ten = parts[2].trimmed();
        QString diachi = parts[3].trimmed();
        QString sdt = parts[4].trimmed();

        if (cccd.isEmpty() || ten.isEmpty() || diachi.isEmpty() || sdt.isEmpty()) {
            continue;
        }

        Person person(cccd, ten, sdt, diachi);

        QStringList bienSoList = bienSoStr.split(' ', Qt::SkipEmptyParts);
        for (const QString& bienSo : bienSoList) {
            QString trimmedBienSo = bienSo.trimmed();

            if (trimmedBienSo.isEmpty() || !isValidBienSo(trimmedBienSo)) {
                continue;
            }

            Xe* xeGoc = hashtableXe->find(trimmedBienSo);
            if (xeGoc != nullptr) {
                xeGoc->setOwner(cccd);
                xeDaCapNhatOwner++;
            }

            if (xeGoc != nullptr) {
                Xe* xe = nullptr;

                if (xeGoc->getLS() == "Motor") {
                    Motor* motor = new Motor();
                    motor->setBienSo(trimmedBienSo);
                    motor->setOwner(cccd);
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
                    car->setBienSo(trimmedBienSo);
                    car->setOwner(cccd);
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

                Person::phanTichBienSo(trimmedBienSo, *xe);
                person.getXe()->insertToHash(xe);
            } else {
                Xe* xe = nullptr;
                bool isMotor = (successCount % 2 == 0);

                if (isMotor) {
                    Motor* motor = new Motor();
                    motor->setBienSo(trimmedBienSo);
                    motor->setOwner(cccd);
                    motor->danhSachMucPhat = dsMucPhatMotor;
                    xe = motor;
                } else {
                    Car* car = new Car();
                    car->setBienSo(trimmedBienSo);
                    car->setOwner(cccd);
                    car->danhSachMucPhat = dsMucPhatCar;
                    xe = car;
                }

                Person::phanTichBienSo(trimmedBienSo, *xe);
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
            qDebug() << "Da doc" << lineCount << "dong...";
        }
    }

    file.close();
    qDebug() << "Da doc xong" << successCount << "/" << lineCount << "ban ghi tu file cccd.txt";
    qDebug() << "  - Da cap nhat chu xe cho" << xeDaCapNhatOwner << "xe trong hashtableXe";
}

void DataGenerator::taoXeMau(vehicleshash* hashtableXe, int soLuong, HashTable<Person>& dsNguoi) {
    qDebug() << "\n=== BAT DAU DOC BIENSO.TXT ===";
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
    qDebug() << "[KIEM TRA] Trong hashtableXe:" << xeCoLoiTrongHash << "xe co loi,"
             << xeKhongLoiTrongHash << "xe khong loi";

    qDebug() << "\n=== BAT DAU DOC CCCD.TXT ===";
    docFileCCCD(finalCCCD, dsNguoi);

    qDebug() << "\n=== HOAN TAT ===";
    qDebug() << "Da tai du lieu tu file vao hashtable";
}

double DataGenerator::timTienPhat(const QString& tenLoi, Mylist<Violation>& dsMucPhat) {
    Node<Violation>* current = dsMucPhat.begin();
    while (current != nullptr) {
        QString tenLoiTrongDS = current->getdata().getLoiViPham();

        if (tenLoi.contains(tenLoiTrongDS, Qt::CaseInsensitive) ||
            tenLoiTrongDS.contains(tenLoi, Qt::CaseInsensitive)) {
            return current->getdata().getMucPhat();
        }
        current = current->getnext();
    }
    return 0.0;
}

void DataGenerator::phanTichLoiPham(const QString& loiPart, Xe* xe, bool isMotor) {
    if (loiPart.isEmpty()) return;

    QStringList cacLoi = loiPart.split('|', Qt::SkipEmptyParts);

    foreach (const QString& motLoi, cacLoi) {
        QString loiDaTrim = motLoi.trimmed();
        if (loiDaTrim.isEmpty()) continue;

        QStringList parts = loiDaTrim.split(' ', Qt::SkipEmptyParts);
        if (parts.size() < 2) continue;

        QString trangThaiStr = parts.last();
        bool trangThaiDong = (trangThaiStr == "DD");

        QString ngayViPham = "";
        for (int i = parts.size() - 2; i >= 0; i--) {
            QString part = parts[i];
            if (part.length() == 10 && part[2] == '-' && part[5] == '-') {
                ngayViPham = part;
                break;
            }
        }

        QString tenLoi = "";
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i] != ngayViPham && parts[i] != trangThaiStr) {
                if (!tenLoi.isEmpty()) tenLoi += " ";
                tenLoi += parts[i];
            }
        }

        if (!tenLoi.isEmpty() && !ngayViPham.isEmpty()) {
            double soTien = 0.0;
            if (isMotor) {
                soTien = timTienPhat(tenLoi, dsMucPhatMotor);
            } else {
                soTien = timTienPhat(tenLoi, dsMucPhatCar);
            }

            Pair loiMoi(tenLoi, ngayViPham, trangThaiDong);
            xe->dsLoi.push_back(loiMoi);

            if (!trangThaiDong) {
                xe->gettongTienPhat() += soTien;
            }
        }
    }
}

void docFilePolice(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file:" << filename;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");

        if (parts.size() >= 2) {
            QString id = parts[0];
            QString pass = parts[1];
            Police::dsPolice->insert(id, Pair(id, pass, false));
        }
    }

    file.close();
    qDebug() << "Da tai danh sach canh sat tu file:" << filename;
}
