#include "Xe.h"
#include "Person.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLocale>

extern HashTable<Person>* hashtableNguoi;
int Xe::tongTienPhat = 0;
Mylist<Pair> Xe::dsMaVung;

Xe::Xe() {
    Owner_id = thanhPho = " ";
    bienSo = " ";
    soLoi = 0;
}

Xe::Xe(QString &id, QString& tp, QString& ls, QString& bs, int& loi)
    : Owner_id(id), thanhPho(tp), loaiXe(ls), bienSo(bs), soLoi(loi) {}

Xe::~Xe() {}

void Xe::docFileMaVung(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << filename;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(' ');
        if (parts.size() < 2) continue;

        QString thanhPho;
        QString maVung;

        for (int i = 0; i < parts.size(); ++i) {
            if (parts[i][0].isDigit()) {
                maVung = parts[i];
                break;
            } else {
                thanhPho += parts[i] + " ";
            }
        }

        thanhPho = thanhPho.trimmed();
        if (!maVung.isEmpty()) {
            Pair p(thanhPho, maVung, true);
            dsMaVung.push_back(p);
        }
    }
    file.close();
}

QString Xe::getbienSo() const {
    return bienSo;
}

QString Xe::getTP() const {
    return thanhPho;
}

QString Xe::getLS() const {
    return loaiXe;
}

QString Xe :: getID() const{
    return Owner_id;
}

int Xe::getsoLoi() {
    return dsLoi.size();
}

int &Xe::gettongTienPhat() {
    return tongTienPhat;
}

Xe& Xe::operator=(const Xe& other) {
    this->bienSo = other.bienSo;
    this->thanhPho = other.thanhPho;
    return *this;
}

void Xe::setBienSo(const QString& bs) {
    bienSo = bs;
}

void Xe::setThanhPho(const QString& tp) {
    thanhPho = tp;
}

void Xe :: setOwner(const QString& cccd) {
    Owner_id = cccd;
}
void Xe::truyenDSVP(const QString& filename) {
}

void Xe::docFileMucPhat(const QString& tenFile) {
    QFile file(tenFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file" << tenFile;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(' ');
        if (parts.size() < 3) continue;

        bool ok;
        int id = parts[0].toInt(&ok);
        if (!ok) continue;

        int mucPhat = parts[parts.size() - 1].toInt(&ok);
        if (!ok) continue;

        QString tenLoi;
        for (int i = 1; i < parts.size() - 1; ++i) {
            tenLoi += parts[i];
            if (i < parts.size() - 2) tenLoi += " ";
        }

        Violation p(id, tenLoi, mucPhat, true);
        Xe::danhSachMucPhat.push_back(p);
    }
    file.close();
}

void Xe::themLoi(const QString& loiVP, const QString& ngayVP){
    dsLoi.push_back(Pair(loiVP, ngayVP, false));
    int tienPhat = 0;

    for(Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()){
        if(loiVP == x->getdata().getLoiViPham()){
            x->getdata().setState(false);
            tienPhat = x->getdata().getMucPhat();
        }
    }

    qDebug() << "Tien phat cua" << loiVP << "la:" << QString::number(tienPhat, 'f', 0);
    try {
        Person &p = getByCCCD(Owner_id, *hashtableNguoi);
        qDebug() << "\n--- THONG TIN CHU XE ---";
        qDebug() << p.getCCCD();
        qDebug() << p.getTen();
        qDebug() << p.getSdt();
        qDebug() << p.getDiaChi();
    } catch (const std::exception& e) {
        qDebug() << "\nKhong tim thay CCCD:" << Owner_id;
    }

    tongTienPhat += tienPhat;
    soLoi++;
}

void Xe::dongPhat(const QString& loiVP, const QString& ngayVP) {
    for (Node<Pair>* current = dsLoi.begin(); current != nullptr; current = current->getnext()) {

        if (current->getdata().key == loiVP && current->getdata().value == ngayVP) {

            current->refgetdata().State = true;
            soLoi--;

            int tienPhat = 0;
            for (Node<Violation>* x = danhSachMucPhat.begin(); x != danhSachMucPhat.end(); x = x->getnext()) {

                if (x->getdata().getLoiViPham() == loiVP) {
                    tienPhat = x->getdata().getMucPhat();
                    break;
                }
            }

            tongTienPhat -= tienPhat;

            if (tongTienPhat == 0) {
                qDebug() << "Hoan tat dong phat";
            } else {
                qDebug() << "Da dong phat loi: " << loiVP << ". Tong tien con lai: " << tongTienPhat;
            }

            return;
        }
    }

    qDebug() << "[LOI LOGIC] Khong tim thay loi de dong phat: " << loiVP << " @ " << ngayVP;
}

void Xe::display() {
    qDebug() << "Bien so xe:" << bienSo;
    qDebug() << "DS Loi:";
    for (Node<Pair>* x = dsLoi.begin(); x != dsLoi.end(); x = x->getnext())
        qDebug() << x->getdata().key << "-" << x->getdata().value;
}

long long Xe::tinhTongTienPhatChuaDong(Mylist<Violation>& masterViolationList) {
     long long tienPhatChuaDong = 0;
    Node<Pair>* loiNode = dsLoi.begin();
    while (loiNode != nullptr) {
        bool trangThai = loiNode->getdata().State;
        if (!trangThai) { // Chỉ nếu chưa đóng
            QString tenLoi = loiNode->getdata().key;
            int mucPhat = 0;

            Node<Violation>* v = masterViolationList.begin();
            while (v != nullptr) {
                if (v->getdata().getLoiViPham() == tenLoi) {
                    mucPhat = v->getdata().getMucPhat();
                    break;
                }
                v = v->getnext();
            }
            tienPhatChuaDong += mucPhat;
        }
    loiNode = loiNode->getnext();
    }
    return tienPhatChuaDong;
}

QString Xe::truyxuatLoi() {
    QLocale vietnamese(QLocale::Vietnamese, QLocale::Vietnam);
    QString result;

    if (dsLoi.size() == 0) {
       result = "<div style='text-align: center; padding: 30px; color: #27ae60; background: rgba(39, 174, 96, 0.1); "
                 "border-radius: 8px; margin-top: 20px; font-size: 16px;'>"
                 "✅ XE KHÔNG CÓ LỖI VI PHẠM NÀO"
                 "</div>";
        return result;
    }

    result +=   "<div style='margin-top: 25px;'>"
                "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #e74c3c, stop:1 #c0392b); "
                "color: white; padding: 18px; border-radius: 8px; margin-bottom: 15px;'>"
                "<h4 style='margin: 0; text-align: center; font-size: 20px;'>📋 DANH SÁCH LỖI VI PHẠM</h4>"
                "</div>"
                "<table width='100%' style='border-collapse: collapse; background: white; border-radius: 8px;'>"
                "<thead>"
                "<tr style='background: #3498db; color: white;'>"
                 "<th style='padding: 12px; text-align: center; width: 10%;'>STT</th>"
                "<th style='padding: 12px; text-align: left; width: 40%;'>LỖI VI PHẠM</th>"
                "<th style='padding: 12px; text-align: center; width: 20%;'>NGÀY VI PHẠM</th>"
                "<th style='padding: 12px; text-align: center; width: 20%;'>TIỀN PHẠT</th>"
                "<th style='padding: 12px; text-align: center; width: 10%;'>TRẠNG THÁI</th>"
                "</tr>"
                "</thead>"
                "<tbody>";

    int stt = 1;
    long long tongTien = 0;
    bool coLoiChuaDong = false;

    Node<Pair>* loiNode = dsLoi.begin();
    while (loiNode != nullptr) {
        QString tenLoi = loiNode->getdata().key;
        QString ngayVP = loiNode->getdata().value;
        bool trangThai = loiNode->getdata().State;

        int tienPhat = 0;
        Node<Violation>* v = danhSachMucPhat.begin();
        while (v != nullptr) {
            if (v->getdata().getLoiViPham() == tenLoi) {
                tienPhat = v->getdata().getMucPhat();
                break;
            }
            v = v->getnext();
        }

        if (!trangThai) {
            tongTien += tienPhat;
            coLoiChuaDong = true;
        }

        QString rowColor = (stt % 2 == 0) ? "background: #f8f9fa;" : "background: white;";

        QString trangThaiText = trangThai ? "✅ ĐÃ ĐÓNG" : "❌ CHƯA ĐÓNG";
        QString trangThaiColor = trangThai ? "color: #27ae60;" : "color: #e74c3c;";

        QString formattedtienPhat = vietnamese.toString(tienPhat) + " VND";
        result += QString("<tr style='%1'>"
                          "<td style='padding: 10px; text-align: center; border-bottom: 1px solid #dee2e6;'>%2</td>"
                           "<td style='padding: 10px; border-bottom: 1px solid #dee2e6;'><b>%3</b></td>"
                          "<td style='padding: 10px; text-align: center; border-bottom: 1px solid #dee2e6;'>%4</td>"
                          "<td style='padding: 10px; text-align: center; border-bottom: 1px solid #dee2e6;'><b>%5 </b></td>"
                          "<td style='padding: 10px; text-align: center; border-bottom: 1px solid #dee2e6; %6'><b>%7</b></td>"
                           "</tr>")
                          .arg(rowColor)
                          .arg(stt)
                          .arg(tenLoi)
                          .arg(ngayVP)
                          .arg(formattedtienPhat)
                          .arg(trangThaiColor)
                          .arg(trangThaiText);

            stt++;
            loiNode = loiNode->getnext();
        }

        result += "</tbody></table>";

        QString formattedTien = vietnamese.toString(tongTien) + " VND";
        if (coLoiChuaDong) {
            result += QString("<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #27ae60, stop:1 #2ecc71); "
                              "color: white; padding: 18px; margin-top: 20px; border-radius: 8px; text-align: center; font-weight: bold; font-size: 18px;'>"
                              "💰 TỔNG TIỀN PHẠT CẦN ĐÓNG: <span style='font-size: 20px;'>%1</span>"
                              "</div>").arg(formattedTien);
        } else {
            result += QString("<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #27ae60, stop:1 #2ecc71); "
                              "color: white; padding: 18px; margin-top: 20px; border-radius: 8px; text-align: center; font-weight: bold; font-size: 18px;'>"
                              "✅ ĐÃ ĐÓNG HẾT TẤT CẢ TIỀN PHẠT"
                              "</div>");
        }

    result += "</div>";
    return result;
}

void Xe::setloaiXe(const QString& lx) {
    loaiXe = lx;
}

QString Xe::truyxuatLoi_TomTat(Mylist<Violation>& list) {
    QLocale vietnamese(QLocale::Vietnamese, QLocale::Vietnam);

    QString loiHtmlList = "";
    long long tienPhatChuaDong = 0;
    int loiChuaDongCount = 0;

    Node<Pair>* loiNode = dsLoi.begin();
    while (loiNode != nullptr) {
        bool trangThai = loiNode->getdata().State;

        if (!trangThai) {
            loiChuaDongCount++;
            QString tenLoi = loiNode->getdata().key;
            QString ngayViPham = loiNode->getdata().value;

            long long mucPhat = 0;

            Node<Violation>* v = list.begin();
            while (v != nullptr) {
                if (v->getdata().getLoiViPham() == tenLoi) {
                    mucPhat = v->getdata().getMucPhat();
                    break;
                }
                v = v->getnext();
            }

            tienPhatChuaDong += mucPhat;

            loiHtmlList += QString(
                               "<div style='background: rgba(255,255,255,0.15); padding: 12px; margin: 5px 0; border-radius: 4px; border-left: 3px solid #f39c12;'>"
                               "<div style='text-align: center;'>"
                               "<div style='font-size: 15px; font-weight: bold; color: #333;'>• %1</div>"
                               "<div style='font-size: 14px; opacity: 0.8; margin-top: 5px; color: #555;'>📅 %2</div>"
                               "<div style='font-size: 14px; font-weight: bold; margin-top: 5px; color: #c0392b;'>%3</div>"
                               "</div>"
                               "</div>"
                               ).arg(tenLoi).arg(ngayViPham).arg(vietnamese.toString(mucPhat) + " VND");
        }
        loiNode = loiNode->getnext();
    }


    QString finalResult = "";
    if (loiChuaDongCount > 0) {
        finalResult += "<div style='margin: 0 0 0 0; padding: 12px; background: rgba(255,255,255,0.1); border-radius: 6px;'>";

        finalResult += "<div style='font-weight: bold; font-size: 14px; margin-bottom: 8px; color: #e74c3c; text-align: center;'>📋 DANH SÁCH LỖI CHƯA ĐÓNG:</div>";

        finalResult += loiHtmlList;

        finalResult += QString(
                           "<div style='background: rgba(231, 76, 60, 0.2); padding: 10px; margin-top: 8px; border-radius: 4px; text-align: center; font-size: 15px; font-weight: bold; color: #c0392b;'>"
                           "💰 Tổng tiền cần đóng: %1"
                           "</div>"
                           ).arg(vietnamese.toString(tienPhatChuaDong) + " VND");

        finalResult += "</div>";
    }

    return finalResult;
}
