#include "Motor.h"
#include <QDebug>
#include <QLocale>

long long Motor::tongTienPhat = 0;

Motor::Motor() {
    thanhPho = " ";
    bienSo = " ";
    loaiXe = "Motor";
}

Motor::~Motor() {
}

long long &Motor::gettongTienPhat() {
    return tongTienPhat;
}

void Motor::display() {
    qDebug() << "loai xe : xe Motor";
    Xe::display();
}

QDebug operator<<(QDebug debug, Motor& motor) {
    debug << "Bien so xe:" << motor.getbienSo();
    debug << "DS loi da vi pham:";
    for (Node<Pair>* x = motor.dsLoi.begin(); x != motor.dsLoi.end(); x = x->getnext())
        debug << x->getdata().key << "-" << x->getdata().value;
    return debug;
}

QString Motor::truyxuatLoi() {
    qDebug() << "\n========================================";
    qDebug() << "       TRUY VAN LOI VI PHAM Motor       ";
    qDebug() << "========================================";
    qDebug() << "Bien so:" << this->getbienSo();
    qDebug() << "Loai xe: " << this->getLS();

    QLocale vietnamese(QLocale::Vietnamese, QLocale::Vietnam);
    QString result;

    if (dsLoi.size() == 0) {
        result = "<div style='text-align: center; padding: 30px; color: #27ae60; background: rgba(39, 174, 96, 0.1); "
                 "border-radius: 8px; margin-top: 20px; font-size: 16px;'>"
                 "✅ XE KHÔNG CÓ LỖI VI PHẠM NÀO"
                 "</div>";
        return result;
    }

    result += QString(   "<div style='margin-top: 25px;'>"
              "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #e74c3c, stop:1 #c0392b); "
              "color: white; padding: 18px; border-radius: 8px; margin-bottom: 15px;'>"
              "<h4 style='margin: 0; text-align: center; font-size: 20px;'>📋 DANH SÁCH LỖI VI PHẠM CỦA XE MÁY CÓ BIỂN SỐ %1</h4>"
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
              "<tbody>"
               ).arg(this->getbienSo());

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
