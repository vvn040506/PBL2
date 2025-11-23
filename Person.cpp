#include "Person.h"
#include "Motor.h"
#include "HashFunction.h"
#include "HashTable.h"
#include "Xe.h"
#include "Car.h"
#include "DataGenerator.h"
#include "Menu.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QApplication>
#include <QScrollArea>
#include <QStyle>
#include <QRegularExpression>
#include <QValidator>

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;

Person::Person() : cccd(""), ten("") {
    hash_xe = new vehicleshash(10, 10, 100);
}

Person::Person(const QString& cccd, const QString& ten, const QString& sdt, const QString& d)
    : cccd(cccd), ten(ten), sdt(sdt), diachi(d) {
    hash_xe = new vehicleshash(10, 10, 100);
}

Person::Person(const Person& other)
    : cccd(other.cccd), ten(other.ten), sdt(other.sdt), diachi(other.diachi) {

    hash_xe = new vehicleshash(other.hash_xe->get1(),
                               other.hash_xe->get2(),
                               other.hash_xe->get3());

    for (int i = 0; i < other.hash_xe->get1(); ++i) {
        for (int j = 0; j < other.hash_xe->get2(); ++j) {
            for (int k = 0; k < other.hash_xe->get3(); ++k) {
                Node<Xe*>* current = other.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    Xe* xe = current->getdata();
                    Xe* newXe = new Xe(*xe);
                    hash_xe->insertToHash(newXe);
                    current = current->getnext();
                }
            }
        }
    }

    hash_nguoi = nullptr;
}

Person::~Person() {
    if (hash_xe != nullptr) {
        delete hash_xe;
    }
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        if (hash_xe != nullptr) {
            delete hash_xe;
        }

        cccd = other.cccd;
        ten = other.ten;
        sdt = other.sdt;
        diachi = other.diachi;

        hash_xe = new vehicleshash(other.hash_xe->get1(),
                                   other.hash_xe->get2(),
                                   other.hash_xe->get3());

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

bool Person::operator==(const Person& other) const {
    return this->cccd == other.cccd;
}

bool Person::operator!=(const Person& other) const {
    return this->cccd != other.cccd;
}

QDebug operator<<(QDebug debug, const Person& p) {
    debug << "[CCCD:" << p.cccd << ", Ten:" << p.ten << ", Sdt:" << p.sdt << ", Dia chi:" << p.diachi << "]";
    debug << "Danh sach xe vi pham:";

    for (int i = 0; i < p.hash_xe->get1(); ++i) {
        for (int j = 0; j < p.hash_xe->get2(); ++j) {
            for (int k = 0; k < p.hash_xe->get3(); ++k) {
                Node<Xe*>* current = p.hash_xe->table[i][j][k].begin();
                while (current != nullptr) {
                    debug << "  -";
                    current->getdata()->display();
                    current = current->getnext();
                }
            }
        }
    }
    return debug;
}

void Person::nhapTT() {
}

void Person::setXe(vehicleshash* xe) {
    if (hash_xe != nullptr) {
        delete hash_xe;
    }
    hash_xe = xe;
}

vehicleshash* Person::getXe() {
    return hash_xe;
}

void Person::phanTichBienSo(const QString& bienSo, Xe& xe) {
    int dash1 = bienSo.indexOf('-');
    int dash2 = bienSo.indexOf('-', dash1 + 1);

    if (dash1 != -1 && dash2 != -1) {
        QString maTP = bienSo.mid(0, dash1);
        QString loaiXe = bienSo.mid(dash1 + 1, dash2 - dash1 - 1);

        xe.setBienSo(bienSo);

        for (Node<Pair>* x = Xe::dsMaVung.begin(); x != nullptr; x = x->getnext()) {
            if (x->getdata().value == maTP) {
                xe.setThanhPho(x->getdata().key);
                break;
            }
        }
    }
}

void Person::timXe(vehicleshash* hash) {
    QDialog dialog;
    dialog.setWindowTitle("Tìm Kiếm Xe Theo Biển Số");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogContentsView));
    dialog.setMinimumSize(900, 750);
    dialog.resize(900, 750);

    dialog.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QFrame *mainFrame = new QFrame();
    mainFrame->setStyleSheet(
        "QFrame {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #667eea, stop:1 #764ba2);"
        "border-radius: 15px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(25);
    frameLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titleLabel = new QLabel("TÌM KIẾM XE THEO BIỂN SỐ");
    titleLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 26px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.2);"
        "padding: 20px;"
        "border-radius: 12px;"
        "border: 2px solid rgba(255,255,255,0.4);"
        "text-align: center;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFixedHeight(80);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
        "QScrollArea {"
        "border: none;"
        "background: transparent;"
        "}"
        "QScrollBar:vertical {"
        "background: rgba(255,255,255,0.3);"
        "width: 12px;"
        "border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background: rgba(255,255,255,0.6);"
        "border-radius: 6px;"
        "min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background: rgba(255,255,255,0.8);"
        "}"
        );

    QWidget *scrollContentWidget = new QWidget();
    scrollContentWidget->setStyleSheet("QWidget { background: transparent; }");

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContentWidget);
    scrollLayout->setSpacing(25);
    scrollLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *bienSoLabel = new QLabel("BIỂN SỐ XE");
    bienSoLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        "background: transparent;"
        "margin-bottom: 10px;"
        "}"
        );
    bienSoLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *bienSoEdit = new QLineEdit();
    bienSoEdit->setPlaceholderText("VD: 38-C2-42567");
    bienSoEdit->setMinimumHeight(50);
    bienSoEdit->setMinimumWidth(500);
    bienSoEdit->setAlignment(Qt::AlignCenter);
    bienSoEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 15px;"
        "font-size: 16px;"
        "color: #333;"
        "text-align: center;"
        "min-height: 20px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #4ecdc4;"
        "background: white;"
        "}"
        );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 10, 0, 0);
    buttonLayout->addStretch();

    QPushButton *searchButton = new QPushButton("🔍 TÌM KIẾM");
    searchButton->setMinimumSize(160, 55);
    searchButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #ff6b6b, stop:1 #ee5a52);"
        "color: white;"
        "border: none;"
        "padding: 15px;"
        "font-size: 16px;"
        "font-weight: bold;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #ff5252, stop:1 #e53935);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #e53935, stop:1 #c62828);"
        "}"
        );

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setMinimumSize(130, 55);
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #95a5a6, stop:1 #7f8c8d);"
        "color: white;"
        "border: none;"
        "padding: 15px 25px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #7f8c8d, stop:1 #6c7b7d);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #6c7b7d, stop:1 #5d6b6c);"
        "}"
        );

    buttonLayout->addWidget(searchButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();

    QTextEdit *resultText = new QTextEdit();
    resultText->setReadOnly(true);
    resultText->setMinimumHeight(400);
    resultText->setStyleSheet(
        "QTextEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.3);"
        "border-radius: 10px;"
        "padding: 20px;"
        "font-size: 14px;"
        "color: #333;"
        "}"
        );

    scrollLayout->addWidget(bienSoLabel);
    scrollLayout->addWidget(bienSoEdit, 0, Qt::AlignVCenter);
    scrollLayout->addLayout(buttonLayout);
    scrollLayout->addWidget(resultText, 1);

    scrollArea->setWidget(scrollContentWidget);

    frameLayout->addWidget(titleLabel);
    frameLayout->addWidget(scrollArea, 1);

    mainLayout->addWidget(mainFrame);

    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        QString bienSo = bienSoEdit->text().trimmed();
        if (bienSo.isEmpty()) {
            resultText->setHtml("<div style='color: #e74c3c; text-align: center; padding: 20px; font-size: 16px;'>"
                                "⚠️ Vui lòng nhập biển số xe!</div>");
            return;
        }

        Xe* xe1 = hash->find(bienSo);
        qDebug() << "Loai xe: " << xe1->getLS();
        Xe* xe = nullptr;
        if(xe1->getLS() == "Motor")
            xe = dynamic_cast<Motor*>(xe1);
        else
            xe = dynamic_cast<Car*>(xe1);

        if (xe) {
            qDebug() << "Tìm thấy xe:" << xe->getbienSo();
            qDebug() << "Số lỗi (getsoLoi):" << xe->getsoLoi();
            qDebug() << "Số lỗi (dsLoi.size):" << xe->dsLoi.size();

            Node<Pair>* loiNode = xe->dsLoi.begin();
            int countLoi = 0;
            int countLoiChuaDong = 0;
            while (loiNode != nullptr) {
                qDebug() << "Lỗi" << countLoi + 1 << ":" << loiNode->getdata().key
                         << "- Ngày:" << loiNode->getdata().value
                         << "- Trạng thái:" << (loiNode->getdata().State ? "Đã đóng" : "Chưa đóng");
                if (!loiNode->getdata().State) {
                    countLoiChuaDong++;
                }
                loiNode = loiNode->getnext();
                countLoi++;
            }
            qDebug() << "Tổng số lỗi thực tế:" << countLoi;
            qDebug() << "Số lỗi chưa đóng:" << countLoiChuaDong;

            Person p = getByCCCD(xe->getID(), *hashtableNguoi);
            int soLoiThucTe = xe->dsLoi.size();

            QString result = QString(
                                 "<div style='background: linear-gradient(135deg, #27ae60, #2ecc71); "
                                 "color: white; padding: 20px; border-radius: 8px; margin-bottom: 15px;'>"
                                 "<h3 style='margin: 0; font-size: 22px;'>🚗🏍 THÔNG TIN XE TÌM THẤY</h3>"
                                 "</div>"
                                 "<div style='padding: 20px; font-size: 16px; line-height: 1.6;'>"
                                 "<table width='100%' style='border-collapse: collapse;'>"
                                 "<tr>"
                                 "<td width='30%' style='padding: 10px;'><b>Biển số:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%1</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Loại xe:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%2</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Số lỗi:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: %3;'>%4</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Số lỗi chưa đóng phạt:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: %5;'>%6</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td colspan='2' style='padding: 15px 10px 5px 10px; font-size: 18px; font-weight: bold; color: #2c3e50;'>👤 THÔNG TIN CHỦ XE</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Căn cước công dân:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%7</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Họ và tên:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%8</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Địa chỉ:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%9</td>"
                                 "</tr>"
                                 "<tr>"
                                 "<td style='padding: 10px;'><b>Số điện thoại:</b></td>"
                                 "<td style='padding: 10px; font-size: 18px; color: #2c3e50;'>%10</td>"
                                 "</tr>"
                                 "</table>"
                                 "</div>"
                                 ).arg(xe->getbienSo())
                                 .arg(xe->getLS().isEmpty() ? "Không xác định" : xe->getLS())
                                 .arg(soLoiThucTe > 0 ? "#e74c3c" : "#27ae60")
                                 .arg(soLoiThucTe)
                                 .arg(countLoiChuaDong > 0 ? "#e74c3c" : "#27ae60")
                                 .arg(countLoiChuaDong)
                                 .arg(p.getCCCD())
                                 .arg(p.getTen())
                                 .arg(p.getDiaChi())
                                 .arg(p.getSdt());

            resultText->setHtml(result);

            QString danhSachLoi = xe->truyxuatLoi();

            resultText->setHtml(result + danhSachLoi);

        } else {
            resultText->setHtml("...KHÔNG TÌM THẤY XE...");
        }
    });

    QObject::connect(bienSoEdit, &QLineEdit::returnPressed, searchButton, &QPushButton::click);
    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

void Person::truyvanCCCD(HashTable<Person>* hashtableNguoi) {
    QDialog dialog;
    dialog.setWindowTitle("TRA CỨU THÔNG TIN THEO CCCD");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));

    dialog.setMinimumSize(900, 750);
    dialog.resize(900, 750);

    dialog.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QScrollArea *mainScrollArea = new QScrollArea();
    mainScrollArea->setWidgetResizable(true);
    mainScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainScrollArea->setStyleSheet(
        "QScrollArea {"
        "border: none;"
        "background: transparent;"
        "}"
        "QScrollBar:vertical {"
        "background: rgba(255,255,255,0.3);"
        "width: 15px;"
        "margin: 0px;"
        "border-radius: 7px;"
        "}"
        "QScrollBar::handle:vertical {"
        "background: rgba(255,255,255,0.7);"
        "border-radius: 7px;"
        "min-height: 20px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "background: rgba(255,255,255,0.9);"
        "}"
        );

    QWidget *scrollContentWidget = new QWidget();
    scrollContentWidget->setStyleSheet("QWidget { background: transparent; }");

    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContentWidget);
    contentLayout->setSpacing(25);
    contentLayout->setContentsMargins(30, 30, 30, 30);

    QFrame *mainFrame = new QFrame();
    mainFrame->setStyleSheet(
        "QFrame {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #f093fb, stop:1 #f5576c);"
        "border-radius: 15px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(25);
    frameLayout->setContentsMargins(30, 30, 30, 30);

    QLabel *titleLabel = new QLabel("TRA CỨU THÔNG TIN THEO CCCD");
    titleLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 24px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.15);"
        "padding: 18px;"
        "border-radius: 10px;"
        "border: 1px solid rgba(255,255,255,0.3);"
        "text-align: center;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(titleLabel);

    QLabel *cccdLabel = new QLabel("SỐ CCCD");
    cccdLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        "background: transparent;"
        "text-align: center;"
        "}"
        );
    cccdLabel->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(cccdLabel);

    QLineEdit *cccdEdit = new QLineEdit();
    cccdEdit->setPlaceholderText("NHẬP 12 SỐ CCCD");
    cccdEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 15px;"
        "font-size: 16px;"
        "color: #333;"
        "text-align: center;"
        "min-height: 20px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #4ecdc4;"
        "background: white;"
        "}"
        );
    cccdEdit->setAlignment(Qt::AlignCenter);

    QRegularExpressionValidator *validator = new QRegularExpressionValidator(QRegularExpression("\\d{0,12}"), cccdEdit);
    cccdEdit->setValidator(validator);
    frameLayout->addWidget(cccdEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 10, 0, 0);
    buttonLayout->addStretch();

    QPushButton *searchButton = new QPushButton("TRA CỨU");
    searchButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #4ecdc4, stop:1 #44a08d);"
        "color: white; border: none; padding: 15px 30px;"
        "font-size: 16px; font-weight: bold; border-radius: 10px;"
        "min-height: 25px; min-width: 150px; text-align: center;"
        "}"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #26a69a, stop:1 #00897b); }"
        "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00897b, stop:1 #00695c); }"
        );
    buttonLayout->addWidget(searchButton);

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #95a5a6, stop:1 #7f8c8d);"
        "color: white; border: none; padding: 15px 30px;"
        "font-size: 16px; font-weight: bold; border-radius: 10px;"
        "min-height: 25px; min-width: 120px; text-align: center;"
        "}"
        "QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #7f8c8d, stop:1 #6c7b7d); }"
        "QPushButton:pressed { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #6c7b7d, stop:1 #5d6b6c); }"
        );
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();
    frameLayout->addLayout(buttonLayout);

    QLabel *resultLabel = new QLabel();
    resultLabel->setWordWrap(true);
    resultLabel->setTextFormat(Qt::RichText);
    resultLabel->setStyleSheet(
        "QLabel {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.3);"
        "border-radius: 10px;"
        "padding: 20px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 400px;"
        "}"
        );
    resultLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    frameLayout->addWidget(resultLabel);

    contentLayout->addWidget(mainFrame);
    contentLayout->addStretch();

    mainScrollArea->setWidget(scrollContentWidget);
    mainLayout->addWidget(mainScrollArea);

    QObject::connect(searchButton, &QPushButton::clicked, [&]() {
        QString cccd = cccdEdit->text().trimmed();
        if (cccd.isEmpty()) {
            resultLabel->setText("<div style='color: #e74c3c; text-align: center; padding: 20px; font-size: 16px;'>"
                                 "⚠️ VUI LÒNG NHẬP SỐ CCCD!</div>");
            return;
        }

        if (cccd.length() != 12) {
            resultLabel->setText("<div style='color: #e74c3c; text-align: center; padding: 20px; font-size: 16px;'>"
                                 "⚠️ CCCD PHẢI CÓ ĐÚNG 12 SỐ!</div>");
            return;
        }

        try {
            Person &p = getByCCCD(cccd, *hashtableNguoi);

            QString result = QString(
                                 "<div style='background: linear-gradient(135deg, #3498db, #2980b9); "
                                 "color: black; padding: 20px; border-radius: 8px; margin-bottom: 20px;'>"
                                 "<h3 style='margin: 0; text-align: center; font-size: 20px;'>👤 THÔNG TIN CHỦ XE</h3>"
                                 "</div>"
                                 "<div style='padding: 20px; background: #f8f9fa; border-radius: 8px; margin-bottom: 20px; font-size: 15px;'>"
                                 "<table width='100%' style='border-collapse: collapse; font-size: 15px;'>"
                                 "<tr><td width='25%' style='padding: 8px;'><b>CCCD:</b></td><td style='padding: 8px; color: #2c3e50;'>%1</td></tr>"
                                 "<tr><td style='padding: 8px;'><b>HỌ TÊN:</b></td><td style='padding: 8px; color: #2c3e50;'>%2</td></tr>"
                                 "<tr><td style='padding: 8px;'><b>ĐỊA CHỈ:</b></td><td style='padding: 8px; color: #2c3e50;'>%3</td></tr>"
                                 "<tr><td style='padding: 8px;'><b>SỐ ĐIỆN THOẠI:</b></td><td style='padding: 8px; color: #2c3e50;'>%4</td></tr>"
                                 "</table>"
                                 "</div>"
                                 ).arg(p.getCCCD())
                                 .arg(p.getTen())
                                 .arg(p.getDiaChi())
                                 .arg(p.getSdt());

            vehicleshash *xeHash = p.getXe();
            if (xeHash && xeHash->cachedtongsoXe > 0) {
                result += QString(
                              "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #e67e22, stop:1 #d35400); "
                              "color: white; padding: 15px; border-radius: 8px; margin: 15px 0;'>"
                              "<h4 style='margin: 0; text-align: center; font-size: 18px;'>🚗🏍 DANH SÁCH XE VI PHẠM</h4>"
                              "</div>"
                              ).arg(xeHash->cachedtongsoXe);

                result += "<div>";
\
                long long tongTienPhatChuaDongCuaNguoi = 0;
                int xeCount = 0;
                for (int i = 0; i < xeHash->get1(); ++i) {
                    for (int j = 0; j < xeHash->get2(); ++j) {
                        for (int k = 0; k < xeHash->get3(); ++k) {
                            Node<Xe*>* current = xeHash->table[i][j][k].begin();
                            while (current != nullptr) {
                                Xe* xe = current->getdata();
                                if(xe->getLS() == "Car"){
                                    if (xe != nullptr) {
                                        xeCount++;

                                        QString xeBgColor = (xeCount % 2 == 0) ?
                                                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #9b59b6, stop:1 #8e44ad);" :
                                                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #34495e, stop:1 #2c3e50);";

                                        result += QString("<div style='%1 padding: 15px; margin: 10px 0; border-radius: 8px; color: white;'>").arg(xeBgColor);

                                        result += QString("<div style='font-weight: bold; font-size: 16px; margin-bottom: 10px; text-align: center;'>🚗 BIỂN SỐ: %1</div>").arg(xe->getbienSo());

                                        result += xe->truyxuatLoi_TomTat(xe->danhSachMucPhat);
                                        tongTienPhatChuaDongCuaNguoi += xe->tinhTongTienPhatChuaDong(xe->danhSachMucPhat);

                                        result += "</div>";
                                    }
                                } else if(xe->getLS() == "Motor"){
                                    if (xe != nullptr) {
                                        xeCount++;

                                        QString xeBgColor = (xeCount % 2 == 0) ?
                                                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #9b59b6, stop:1 #8e44ad);" :
                                                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #34495e, stop:1 #2c3e50);";

                                        result += QString("<div style='%1 padding: 15px; margin: 10px 0; border-radius: 8px; color: white;'>").arg(xeBgColor);

                                        result += QString("<div style='font-weight: bold; font-size: 16px; margin-bottom: 10px; text-align: center;'>🏍️ BIỂN SỐ: %1</div>").arg(xe->getbienSo());

                                        result += xe->truyxuatLoi_TomTat(xe->danhSachMucPhat);
                                        tongTienPhatChuaDongCuaNguoi += xe->tinhTongTienPhatChuaDong(xe->danhSachMucPhat);

                                        result += "</div>";
                                    }
                                }
                                current = current->getnext();
                            }
                        }
                    }
                }
                result += "</div>";
\
                result += QString(
                              "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #27ae60, stop:1 #2ecc71); "
                              "color: white; padding: 15px; margin-top: 20px; border-radius: 8px; text-align: center; font-weight: bold; font-size: 16px;'>"
                              "📊 TỔNG KẾT TIỀN CẦN ĐÓNG: %1 VND"
                              "</div>"
                              ).arg(QLocale(QLocale::Vietnamese, QLocale::Vietnam).toString(tongTienPhatChuaDongCuaNguoi));

            } else {
                result += "<div style='text-align: center; padding: 30px; color: #7f8c8d; background: rgba(127, 140, 141, 0.1); border-radius: 8px; font-size: 16px;'>"
                          "📭 KHÔNG CÓ XE NÀO TRONG HỆ THỐNG"
                          "</div>";
            }

            resultLabel->setText(result);

        } catch (const std::exception& e) {
            resultLabel->setText(
                "<div style='text-align: center; padding: 50px; color: #e74c3c; font-size: 16px;'>"
                "❌<br><br>"
                "<h3 style='color: #c0392b; font-size: 20px;'>KHÔNG TÌM THẤY THÔNG TIN</h3>"
                "<p>KHÔNG TÌM THẤY THÔNG TIN VỚI CCCD: <b>" + cccd + "</b></p>"
                         "<p style='font-size: 14px; color: #7f8c8d;'>VUI LÒNG KIỂM TRA LẠI SỐ CCCD</p>"
                         "</div>"
                );
        }
    });

    QObject::connect(cccdEdit, &QLineEdit::returnPressed, searchButton, &QPushButton::click);
    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}
