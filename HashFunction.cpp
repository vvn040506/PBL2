#include "HashFunction.h"
#include "Xe.h"
#include <QChar>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>
#include <QObject>
#include <QLabel>
#include <QApplication>
#include <QStyle>
#include <QFrame>
#include <QString>
#include <QLocale>

vehicleshash::vehicleshash(int size1, int size2, int size3) : size1(size1), size2(size2), size3(size3){
    cachedtongsoXe = 0;
    cachedMotor = 0;
    cachedCar = 0;
    cachedtongsoXeViPham = 0;
    cachedMotorViPham = 0;
    cachedCarViPham = 0;
    cachedtienPhat = 0;
    cachedtienPhatMotor = 0;
    cachedtienPhatCar = 0;

    cachedtienDaDong = 0;
    cachedtienChuaDong = 0;
    cachedtienDaDongMotor = 0;
    cachedtienChuaDongMotor = 0;
    cachedtienDaDongCar = 0;
    cachedtienChuaDongCar = 0;
    cachedsoLoiDaDong = 0;
    cachedsoLoiChuaDong = 0;

    table = new Mylist<Xe*>**[size1];
    for (int i = 0; i < size1; ++i) {
        table[i] = new Mylist<Xe*>*[size2];
        for (int j = 0; j < size2; ++j)
            table[i][j] = new Mylist<Xe*>[size3];
    }
}

vehicleshash::~vehicleshash() {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++)
            delete[] table[i][j];
        delete[] table[i];
    }
    delete[] table;
}

int vehicleshash::Hash_number(const QString& plate) {
    QString numberPart = "";
    int lastDash = plate.lastIndexOf('-');
    if (lastDash != -1) {
        numberPart = plate.mid(lastDash + 1);
    }

    int num = 0;
    for (QChar c : numberPart) {
        if (c.isDigit()) {
            num = num * 10 + (c.digitValue());
        }
    }
    return num % size3;
}

int vehicleshash::Hash_province(const QString& plate){
    int num = 0;
    for (int i = 0; i < 2 && i < plate.length(); i++) {
        if (plate[i].isDigit()) {
            num = num * 10 + (plate[i].digitValue());
        }
    }
    return num % size1;
}

int vehicleshash::Hash_type(const QString& plate){
    int num = 0;
    int firstDash = plate.indexOf('-');
    if (firstDash != -1) {
        int secondDash = plate.indexOf('-', firstDash + 1);
        if (secondDash != -1) {
            QString typePart = plate.mid(firstDash + 1, secondDash - firstDash - 1);
            for (QChar c : typePart) {
                if (c.isLetter()) {
                    num = num * 31 + (c.toUpper().unicode() - 'A' + 1);
                }
            }
        }
    }
    return num % size2;
}

void vehicleshash::insertToHash(Xe* a){
    int p = Hash_province(a->getbienSo());
    int t = Hash_type(a->getbienSo());
    int n = Hash_number(a->getbienSo());

    table[p][t][n].push_back(a);

    cachedtongsoXe++;
    QString loaiXe = a->getLS();
    if (loaiXe == "Motor") cachedMotor++;
    else cachedCar++;

    if (a->dsLoi.size() > 0) {
        cachedtongsoXeViPham++;

        if (loaiXe == "Motor") {
            cachedMotorViPham++;
        } else {
            cachedCarViPham++;
        }
    }

    Node<Pair>* loiNode = a->dsLoi.begin();
    while (loiNode != nullptr) {
        QString tenLoi = loiNode->getdata().key;
        bool trangThaiDong = loiNode->getdata().State;

        long long tienPhat = 0;
        Node<Violation>* v = a->danhSachMucPhat.begin();

        while (v != nullptr) {
            if (v->getdata().getLoiViPham() == tenLoi) {
                tienPhat = v->getdata().getMucPhat();
                break;
            }
            v = v->getnext();
        }

        cachedtienPhat += tienPhat;
        if (loaiXe == "Motor") {
            cachedtienPhatMotor += tienPhat;
        } else {
            cachedtienPhatCar += tienPhat;
        }

        if (trangThaiDong) {
            cachedtienDaDong += tienPhat;
            cachedsoLoiDaDong++;
            if (loaiXe == "Motor") {
                cachedtienDaDongMotor += tienPhat;
            } else {
                cachedtienDaDongCar += tienPhat;
            }
        } else {
            cachedtienChuaDong += tienPhat;
            cachedsoLoiChuaDong++;
            if (loaiXe == "Motor") {
                cachedtienChuaDongMotor += tienPhat;
            } else {
                cachedtienChuaDongCar += tienPhat;
            }
        }

        bool timThay = false;
        Node<thongkeLoi>* current = cachedthongkeLoi.begin();
        while (current != nullptr) {
            if (current->refgetdata().tenLoi == tenLoi) {
                current->refgetdata().soLan++;
                if (trangThaiDong) {
                    current->refgetdata().soDaDong++;
                } else {
                    current->refgetdata().soChuaDong++;
                }
                timThay = true;
                break;
            }
            current = current->getnext();
        }

        if (!timThay) {
            thongkeLoi tkLoi(tenLoi, 1);
            if (trangThaiDong) {
                tkLoi.soDaDong = 1;
                tkLoi.soChuaDong = 0;
            } else {
                tkLoi.soDaDong = 0;
                tkLoi.soChuaDong = 1;
            }
            cachedthongkeLoi.push_back(tkLoi);
        }

        loiNode = loiNode->getnext();
    }
}

Xe* vehicleshash::find(const QString& a){
    int p = Hash_province(a);
    int t = Hash_type(a);
    int n = Hash_number(a);

    Node<Xe*>* current = table[p][t][n].begin();

    while (current != nullptr){
        if (current->getdata()->getbienSo() == a)
            return (current->refgetdata());
        current = current->getnext();
    }
    return nullptr;
}

void vehicleshash::thongke(){
    int tongSoLoi = 0;
    Node<thongkeLoi>* current = cachedthongkeLoi.begin();
    while (current != nullptr) {
        tongSoLoi += current->getdata().soLan;
        current = current->getnext();
    }

    QDialog dialog;
    dialog.setWindowTitle("THỐNG KÊ TỔNG QUAN HỆ THỐNG");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogDetailedView));
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
        "stop:0 #3498db, stop:1 #2980b9);"
        "border-radius: 15px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(20);
    frameLayout->setContentsMargins(25, 25, 25, 25);

    QLabel *titleLabel = new QLabel("THỐNG KÊ TỔNG QUAN HỆ THỐNG");
    titleLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 22px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.15);"
        "padding: 15px;"
        "border-radius: 10px;"
        "border: 1px solid rgba(255,255,255,0.3);"
        "text-align: center;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    QTableWidget *table = new QTableWidget(9, 2);
    table->setHorizontalHeaderLabels({"CHỈ SỐ", "GIÁ TRỊ"});

    QStringList rowLabels = {
        "Tổng số xe",
        "  - Xe máy (Motor)",
        "  - Ô tô (Car)",
        "Tổng xe đã vi phạm",
        "Tổng số lỗi vi phạm",
        "  - Đã đóng phạt",
        "  - Chưa đóng phạt",
        "Tổng tiền phạt",
        "  - Đã thu",
        "  - Chưa thu"
    };

    table->setItem(0, 0, new QTableWidgetItem(rowLabels[0]));
    table->setItem(0, 1, new QTableWidgetItem(QString::number(cachedtongsoXe)));

    table->setItem(1, 0, new QTableWidgetItem(rowLabels[1]));
    table->setItem(1, 1, new QTableWidgetItem(QString::number(cachedMotor)));

    table->setItem(2, 0, new QTableWidgetItem(rowLabels[2]));
    table->setItem(2, 1, new QTableWidgetItem(QString::number(cachedCar)));

    table->setItem(3, 0, new QTableWidgetItem(rowLabels[3]));
    table->setItem(3, 1, new QTableWidgetItem(QString::number(cachedtongsoXeViPham)));

    table->setItem(4, 0, new QTableWidgetItem(rowLabels[4]));
    table->setItem(4, 1, new QTableWidgetItem(QString::number(tongSoLoi)));

    table->setItem(5, 0, new QTableWidgetItem(rowLabels[5]));
    table->setItem(5, 1, new QTableWidgetItem(QString::number(cachedsoLoiDaDong) + " lỗi"));

    table->setItem(6, 0, new QTableWidgetItem(rowLabels[6]));
    table->setItem(6, 1, new QTableWidgetItem(QString::number(cachedsoLoiChuaDong) + " lỗi"));

    QLocale vietnamese(QLocale::Vietnamese, QLocale::Vietnam);
    QString formattedTongTienPhat = vietnamese.toString(cachedtienPhat) + " VND";
    QString formattedTienDaDong = vietnamese.toString(cachedtienDaDong) + " VND";
    QString formattedTienChuaDong = vietnamese.toString(cachedtienChuaDong) + " VND";

    table->setItem(7, 0, new QTableWidgetItem(rowLabels[7]));
    table->setItem(7, 1, new QTableWidgetItem(formattedTongTienPhat));

    table->setItem(8, 0, new QTableWidgetItem(rowLabels[8]));
    table->setItem(8, 1, new QTableWidgetItem(formattedTienDaDong));

    table->setRowCount(10);
    table->setItem(9, 0, new QTableWidgetItem(rowLabels[9]));
    table->setItem(9, 1, new QTableWidgetItem(formattedTienChuaDong));

    table->setStyleSheet(
        "QTableWidget {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 10px;"
        "font-size: 14px;"
        "gridline-color: rgba(255,255,255,0.3);"
        "}"
        "QTableWidget::item {"
        "padding: 10px;"
        "border-bottom: 1px solid rgba(0,0,0,0.1);"
        "}"
        "QTableWidget::item:selected {"
        "background: #3498db;"
        "color: white;"
        "}"
        "QHeaderView::section {"
        "background: #2c3e50;"
        "color: white;"
        "padding: 12px;"
        "border: none;"
        "font-weight: bold;"
        "font-size: 14px;"
        "}"
        );

    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setAlternatingRowColors(true);

    table->setColumnWidth(0, 300);
    table->setColumnWidth(1, 300);
    for (int i = 0; i < 10; ++i) {
        table->setRowHeight(i, 40);
    }

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #e74c3c, stop:1 #c0392b);"
        "color: white;"
        "border: none;"
        "padding: 12px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "min-height: 25px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #c0392b, stop:1 #a93226);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #a93226, stop:1 #922b21);"
        "}"
        );

    frameLayout->addWidget(titleLabel);
    frameLayout->addWidget(table);
    frameLayout->addWidget(closeButton);

    mainLayout->addWidget(mainFrame);

    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}
