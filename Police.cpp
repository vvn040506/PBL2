#include "Police.h"
#include "Menu.h"
#include "Car.h"
#include "Motor.h"
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QComboBox>
#include <QFormLayout>
#include <QTextStream>
#include <QFile>
#include <QChar>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QApplication>
#include <QScrollArea>
#include <QRadioButton>
#include <QTextEdit>
#include <QToolButton>

HashTable<Pair>* Police::dsPolice = new HashTable<Pair>(1000);
extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern QString Link;
extern QString finalMaVung;
extern QString finalMotor;
extern QString finalCar;
extern QString finalCCCD;
extern QString finalbienSo;

Police::Police() : id_police("") {}
Police::~Police() {}

Police::Police(const QString& id, const QString& p) : id_police(id), pass(p) {}
QString Police::getID() { return id_police; }

void Police::addPoliceWork(const QString& id_police, const QString& bienso, const QString& ngay) {
    if (dsPolice != nullptr) {
        dsPolice->insert(id_police, Pair(bienso, ngay, false));
    }
}

void Police::showPoliceWork(const QString& id) {
    int pos = dsPolice->hash_function(id);
    for (Node<Pair>* x = dsPolice->buckets[pos].begin(); x != dsPolice->buckets[pos].end(); x = x->getnext()) {
        qDebug() << "Da nhap vao bien so:" << x->getdata().key << "- Ngay:" << x->getdata().value;
    }
}

Mylist<Pair> Police::getPoliceWork(const QString& id) {
    if (dsPolice != nullptr) {
        int pos = dsPolice->hash_function(id);
        return dsPolice->buckets[pos];
    }
    return Mylist<Pair>();
}

QLineEdit* Police::createStyledLineEdit(const QString& placeholder) {
    QLineEdit *edit = new QLineEdit();
    edit->setPlaceholderText(placeholder);
    edit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 10px;"
        "font-size: 14px;"
        "color: #333;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #3498db;"
        "background: white;"
        "}"
        );
    return edit;
}

void Police::themloiXe(vehicleshash* Hash) {
    QDialog dialog;
    dialog.setWindowTitle("THÊM LỖI VI PHẠM CHO XE");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    dialog.setMinimumSize(900, 750);
    dialog.resize(900, 750);

    dialog.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QFrame *mainFrame = new QFrame();
    mainFrame->setStyleSheet(
        "QFrame {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #ff6b6b, stop:1 #ee5a52);"
        "border-radius: 15px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(15);
    frameLayout->setContentsMargins(25, 25, 25, 25);

    QLabel *titleLabel = new QLabel("THÊM LỖI VI PHẠM CHO XE");
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
    titleLabel->setWordWrap(true);

    QLabel *bienSoLabel = new QLabel("BIỂN SỐ XE");
    bienSoLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 14px;"
        "font-weight: bold;"
        "background: transparent;"
        "text-align: center;"
        "}"
        );
    bienSoLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *bienSoEdit = new QLineEdit();
    bienSoEdit->setPlaceholderText("VD: 29-A1-12345");
    bienSoEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 10px;"
        "font-size: 13px;"
        "color: #333;"
        "text-align: center;"
        "min-height: 20px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #ffeb3b;"
        "background: white;"
        "}"
        );
    bienSoEdit->setAlignment(Qt::AlignCenter);

    QPushButton *findButton = new QPushButton("TÌM XE");
    findButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #4ecdc4, stop:1 #44a08d);"
        "color: white;"
        "border: none;"
        "padding: 10px 15px;"
        "font-size: 13px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "min-height: 25px;"
        "text-align: center;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #26a69a, stop:1 #00897b);"
        "}"
        );

    QFrame *infoFrame = new QFrame();
    infoFrame->setStyleSheet(
        "QFrame {"
        "background: rgba(255,255,255,0.9);"
        "border-radius: 10px;"
        "border: 2px solid rgba(255,255,255,0.5);"
        "padding: 12px;"
        "}"
        );
    QVBoxLayout *infoLayout = new QVBoxLayout(infoFrame);

    QLabel *infoLabel = new QLabel("THÔNG TIN XE SẼ HIỂN THỊ Ở ĐÂY...");
    infoLabel->setStyleSheet("color: #666; font-style: italic; font-weight: bold; font-size: 12px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setWordWrap(true);
    infoLayout->addWidget(infoLabel);

    QLabel *loiLabel = new QLabel("NHẬP LỖI CẦN THÊM VÀO");
    loiLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 16px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.2);"
        "padding: 12px;"
        "border-radius: 8px;"
        "text-align: center;"
        "}"
        );
    loiLabel->setAlignment(Qt::AlignCenter);
    loiLabel->setWordWrap(true);

    QVBoxLayout *loiInputLayout = new QVBoxLayout();
    loiInputLayout->setSpacing(8);

    QLabel *tenLoiLabel = new QLabel("TÊN LỖI");
    tenLoiLabel->setStyleSheet("color: white; font-weight: bold; font-size: 13px;");
    tenLoiLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *tenLoiEdit = new QLineEdit();
    tenLoiEdit->setPlaceholderText("NHẬP TÊN LỖI VI PHẠM");
    tenLoiEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 8px;"
        "font-size: 13px;"
        "text-align: center;"
        "min-height: 20px;"
        "}"
        );
    tenLoiEdit->setAlignment(Qt::AlignCenter);

    QLabel *ngayLabel = new QLabel("NGÀY VI PHẠM");
    ngayLabel->setStyleSheet("color: white; font-weight: bold; font-size: 13px;");
    ngayLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *ngayEdit = new QLineEdit();
    ngayEdit->setPlaceholderText("DD-MM-YYYY");
    ngayEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 8px;"
        "font-size: 13px;"
        "text-align: center;"
        "min-height: 20px;"
        "}"
        );
    ngayEdit->setAlignment(Qt::AlignCenter);

    loiInputLayout->addWidget(tenLoiLabel);
    loiInputLayout->addWidget(tenLoiEdit);
    loiInputLayout->addWidget(ngayLabel);
    loiInputLayout->addWidget(ngayEdit);

    QPushButton *addButton = new QPushButton("THÊM LỖI VI PHẠM");
    addButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #27ae60, stop:1 #2ecc71);"
        "color: white;"
        "border: none;"
        "padding: 12px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 10px;"
        "text-align: center;"
        "min-height: 25px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #229954, stop:1 #27ae60);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #1e8449, stop:1 #229954);"
        "}"
        "QPushButton:disabled {"
        "background: #95a5a6;"
        "color: #7f8c8d;"
        "}"
        );
    addButton->setEnabled(false);

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: #95a5a6;"
        "color: white;"
        "border: none;"
        "padding: 12px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 10px;"
        "min-height: 25px;"
        "}"
        "QPushButton:hover {"
        "background: #7f8c8d;"
        "}"
        );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    buttonLayout->addWidget(addButton);

    frameLayout->addWidget(titleLabel);
    frameLayout->addSpacing(10);
    frameLayout->addWidget(bienSoLabel);
    frameLayout->addWidget(bienSoEdit);
    frameLayout->addWidget(findButton);
    frameLayout->addSpacing(10);
    frameLayout->addWidget(infoFrame);
    frameLayout->addSpacing(10);
    frameLayout->addWidget(loiLabel);
    frameLayout->addSpacing(10);
    frameLayout->addLayout(loiInputLayout);
    frameLayout->addSpacing(15);
    frameLayout->addLayout(buttonLayout);

    scrollArea->setWidget(mainFrame);
    mainLayout->addWidget(scrollArea);

    Xe* currentXe = nullptr;

    QObject::connect(findButton, &QPushButton::clicked, [&]() {
        QString bienSo = bienSoEdit->text().trimmed();
        if (bienSo.isEmpty()) {
            QMessageBox::warning(&dialog, "LỖI", "VUI LÒNG NHẬP BIỂN SỐ XE!");
            return;
        }

        currentXe = Hash->find(bienSo);
        if (!currentXe) {
            infoLabel->setText("❌ KHÔNG TÌM THẤY XE!");
            infoLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
            addButton->setEnabled(false);
            return;
        }

        Person p = getByCCCD(currentXe->getID(), *hashtableNguoi);
        QString infoText = QString(
                               "🚗 <b>BIỂN SỐ:</b> %1<br>"
                               "📝 <b>LOẠI XE:</b> %2<br>"
                               "🏙️ <b>THÀNH PHỐ:</b> %3<br>"
                               "👤 <b>THÔNG TIN CHỦ XE</b><br>"
                               "🆔 <b>CCCD:</b> %4<br>"
                               "👨‍💼 <b>HỌ TÊN:</b> %5<br>"
                               "🏠 <b>ĐỊA CHỈ:</b> %6<br>"
                               "📞 <b>SĐT:</b> %7"
                               ).arg(currentXe->getbienSo())
                               .arg(currentXe->getLS())
                               .arg(currentXe->getTP())
                               .arg(p.getCCCD())
                               .arg(p.getTen())
                               .arg(p.getDiaChi())
                               .arg(p.getSdt());
        infoLabel->setText(infoText);
        infoLabel->setStyleSheet("color: #2c3e50; font-weight: normal;");

        addButton->setEnabled(true);
    });

    QObject::connect(addButton, &QPushButton::clicked, [&]() {
        if (!currentXe) {
            QMessageBox::warning(&dialog, "LỖI", "VUI LÒNG TÌM XE TRƯỚC!");
            return;
        }

        QString tenLoi = tenLoiEdit->text().trimmed();
        QString ngayVP = ngayEdit->text().trimmed();

        if (tenLoi.isEmpty() || ngayVP.isEmpty()) {
            QMessageBox::warning(&dialog, "LỖI", "VUI LÒNG NHẬP ĐẦY ĐỦ THÔNG TIN LỖI!");
            return;
        }

        currentXe->themLoi(tenLoi, ngayVP);
        Person &p = getByCCCD(currentXe->getID(), *hashtableNguoi);
        Xe *newXe = p.getXe()->find(currentXe->getbienSo());
        newXe->themLoi(tenLoi, ngayVP);
        capNhatFileBienSo(currentXe);

        QMessageBox::information(&dialog, "THÀNH CÔNG",
                                 "✅ ĐÃ THÊM LỖI VI PHẠM THÀNH CÔNG!\n\n"
                                 "LỖI: " + tenLoi + "\n"
                                                "NGÀY: " + ngayVP + "\n"
                                                "BIỂN SỐ: " + currentXe->getbienSo());

        tenLoiEdit->clear();
        ngayEdit->clear();
    });

    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    dialog.exec();
}

void Police::xoaloiXe(vehicleshash* hashtableXe) {
    QDialog dialog;
    dialog.setWindowTitle("Xóa Lỗi Vi Phạm");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_TrashIcon));
    dialog.setMinimumSize(900, 750);
    dialog.resize(900, 750);

    dialog.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QFrame *mainFrame = new QFrame();
    mainFrame->setStyleSheet(
        "QFrame {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #8e44ad, stop:1 #9b59b6);"
        "border-radius: 15px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(15);
    frameLayout->setContentsMargins(25, 25, 25, 25);

    QLabel *titleLabel = new QLabel("CHỈNH SỬA LỖI VI PHẠM ĐÃ ĐÓNG PHẠT");
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
    titleLabel->setWordWrap(true);

    QHBoxLayout *bienSoLayout = new QHBoxLayout();

    QLabel *bienSoLabel = new QLabel("BIỂN SỐ XE");
    bienSoLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 14px;"
        "font-weight: bold;"
        "min-width: 100px;"
        "qproperty-alignment: 'AlignCenter';"
        "}"
        );
    bienSoLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *bienSoEdit = new QLineEdit();
    bienSoEdit->setPlaceholderText("VD: 29-A1-12345");
    bienSoEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "padding: 10px;"
        "font-size: 14px;"
        "color: #333;"
        "}"
        );

    QPushButton *findButton = new QPushButton("Tìm Xe");
    findButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #e67e22, stop:1 #d35400);"
        "color: white;"
        "border: none;"
        "padding: 10px 20px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #f39c12, stop:1 #e67e22);"
        "}"
        );

    bienSoLayout->addWidget(bienSoLabel);
    bienSoLayout->addWidget(bienSoEdit);
    bienSoLayout->addWidget(findButton);

    QFrame *infoFrame = new QFrame();
    infoFrame->setStyleSheet(
        "QFrame {"
        "background: rgba(255,255,255,0.9);"
        "border-radius: 10px;"
        "border: 2px solid rgba(255,255,255,0.5);"
        "padding: 15px;"
        "}"
        );
    QVBoxLayout *infoLayout = new QVBoxLayout(infoFrame);

    QLabel *infoLabel = new QLabel("Thông tin xe sẽ hiển thị ở đây...");
    infoLabel->setStyleSheet("color: #666; font-style: italic; font-size: 14px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setMinimumHeight(180);
    infoLabel->setWordWrap(true);
    infoLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    infoLayout->addWidget(infoLabel);

    QLabel *loiLabel = new QLabel("DANH SÁCH LỖI CHƯA ĐÓNG PHẠT");
    loiLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 16px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.2);"
        "padding: 10px;"
        "border-radius: 8px;"
        "qproperty-alignment: 'AlignCenter';"
        "}"
        );
    loiLabel->setAlignment(Qt::AlignCenter);
    loiLabel->setFixedHeight(50);

    QTableWidget *loiTable = new QTableWidget();
    loiTable->verticalHeader()->setVisible(false);
    loiTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    loiTable->setSelectionMode(QAbstractItemView::SingleSelection);
    loiTable->setFocusPolicy(Qt::NoFocus);
    loiTable->setColumnCount(3);
    loiTable->setHorizontalHeaderLabels({"STT", "Lỗi vi phạm", "Ngày vi phạm"});
    loiTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    loiTable->setStyleSheet(
        "QTableWidget {"
        "background: rgba(255,255,255,0.95);"
        "border: 2px solid rgba(255,255,255,0.5);"
        "border-radius: 8px;"
        "font-size: 13px;"
        "alternate-background-color: #f8f9fa;"
        "gridline-color: #dee2e6;"
        "outline: none;"
        "}"
        "QHeaderView::section {"
        "background: #3498db;"
        "color: white;"
        "padding: 8px;"
        "border: none;"
        "font-weight: bold;"
        "font-size: 13px;"
        "}"
        "QTableWidget::item {"
        "padding: 8px;"
        "border: none;"
        "}"
        "QTableWidget::item:selected {"
        "background: #e74c3c;"
        "color: white;"
        "border: none;"
        "outline: none;"
        "}"
        );

    loiTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    loiTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    loiTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    loiTable->setMinimumHeight(150);
    loiTable->setMaximumHeight(200);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(15);
    buttonLayout->setContentsMargins(0, 10, 0, 0);
    buttonLayout->addStretch();

    QPushButton *deleteButton = new QPushButton("XÓA LỖI ĐÃ CHỌN");
    deleteButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #e74c3c, stop:1 #c0392b);"
        "color: white;"
        "border: none;"
        "padding: 12px 25px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "min-width: 160px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #c0392b, stop:1 #a93226);"
        "}"
        "QPushButton:disabled {"
        "background: #95a5a6;"
        "color: #7f8c8d;"
        "}"
        );
    deleteButton->setEnabled(false);

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #95a5a6, stop:1 #7f8c8d);"
        "color: white;"
        "border: none;"
        "padding: 12px 25px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #7f8c8d, stop:1 #6c7b7d);"
        "}"
        );

    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();

    frameLayout->addWidget(titleLabel);
    frameLayout->addLayout(bienSoLayout);
    frameLayout->addWidget(infoFrame);
    frameLayout->addWidget(loiLabel);
    frameLayout->addWidget(loiTable);
    frameLayout->addLayout(buttonLayout);

    scrollArea->setWidget(mainFrame);
    mainLayout->addWidget(scrollArea);

    Xe* currentXe = nullptr;

    QObject::connect(findButton, &QPushButton::clicked, [&]() {
        QString bienSo = bienSoEdit->text().trimmed();
        if (bienSo.isEmpty()) {
            QMessageBox::warning(&dialog, "Lỗi", "Vui lòng nhập biển số xe!");
            return;
        }

        loiTable->setRowCount(0);
        deleteButton->setEnabled(false);
        currentXe = nullptr;

        currentXe = hashtableXe->find(bienSo);
        if (!currentXe) {
            infoLabel->setText("❌ Không tìm thấy xe!");
            infoLabel->setStyleSheet("color: #e74c3c; font-weight: bold; font-size: 14px;");
            return;
        }

        Person p = getByCCCD(currentXe->getID(), *hashtableNguoi);

        QString infoText = QString(
                               "🚗 <b>Biển số:</b> %1<br>"
                               "📝 <b>Loại xe:</b> %2<br>"
                               "📊 <b>Tổng số lỗi đã ghi nhận:</b> %3<br>"
                               "<br>"
                               "👤 <b>THÔNG TIN CHỦ XE</b><br>"
                               "🆔 <b>CCCD:</b> %4<br>"
                               "👨‍💼 <b>HỌ TÊN:</b> %5<br>"
                               "🏠 <b>ĐỊA CHỈ:</b> %6<br>"
                               "📞 <b>SĐT:</b> %7"
                               ).arg(currentXe->getbienSo())
                               .arg(currentXe->getLS())
                               .arg(currentXe->getsoLoi())
                               .arg(p.getCCCD())
                               .arg(p.getTen())
                               .arg(p.getDiaChi())
                               .arg(p.getSdt());

        infoLabel->setText(infoText);
        infoLabel->setStyleSheet("color: #2c3e50; font-weight: normal; font-size: 13px;");

        int row = 0;
        Node<Pair>* loi = currentXe->dsLoi.begin();

        while (loi != nullptr) {
            if (loi->getdata().State == false) {
                loiTable->insertRow(row);

                QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(row + 1));
                item0->setTextAlignment(Qt::AlignCenter);
                loiTable->setItem(row, 0, item0);

                QTableWidgetItem *item1 = new QTableWidgetItem(loi->getdata().key);
                item1->setTextAlignment(Qt::AlignCenter);
                loiTable->setItem(row, 1, item1);

                QTableWidgetItem *item2 = new QTableWidgetItem(loi->getdata().value);
                item2->setTextAlignment(Qt::AlignCenter);
                loiTable->setItem(row, 2, item2);

                row++;
            }
            loi = loi->getnext();
        }

        if (row > 0) {
            deleteButton->setEnabled(true);
        }
    });

    QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
        if (!currentXe) {
            QMessageBox::warning(&dialog, "Lỗi", "Vui lòng tìm xe trước!");
            return;
        }

        int currentRow = loiTable->currentRow();
        if (currentRow == -1) {
            QMessageBox::warning(&dialog, "Lỗi", "Vui lòng chọn lỗi cần xóa!");
            return;
        }

        QString tenLoi = loiTable->item(currentRow, 1)->text();
        QString ngayVP = loiTable->item(currentRow, 2)->text();

        QMessageBox::StandardButton reply = QMessageBox::question(&dialog, "Xác nhận xóa",
                                                                  QString("Bạn có chắc muốn xóa lỗi:\n\n"
                                                                          "Lỗi: %1\n"
                                                                          "Ngày: %2\n\n"
                                                                          "Thao tác này sẽ cập nhật lỗi là ĐÃ ĐÓNG PHẠT.").arg(tenLoi, ngayVP),
                                                                  QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            currentXe->dongPhat(tenLoi, ngayVP);
            Person &newP = getByCCCD(currentXe->getID(), *hashtableNguoi);
            Xe *newXe = newP.getXe()->find(currentXe->getbienSo());
            newXe->dongPhat(tenLoi, ngayVP);
            capNhatFileBienSo(currentXe);

            QMessageBox::information(&dialog, "Thành công", "✅ Đã cập nhật trạng thái lỗi thành công!");

            loiTable->removeRow(currentRow);
            Person p = getByCCCD(currentXe->getID(), *hashtableNguoi);
            QString infoText = QString(
                                   "🚗 <b>Biển số:</b> %1<br>"
                                   "📝 <b>Loại xe:</b> %2<br>"
                                   "📊 <b>Tổng số lỗi đã ghi nhận:</b> %3<br>"
                                   "<br>"
                                   "👤 <b>THÔNG TIN CHỦ XE</b><br>"
                                   "🆔 <b>CCCD:</b> %4<br>"
                                   "👨‍💼 <b>HỌ TÊN:</b> %5<br>"
                                   "🏠 <b>ĐỊA CHỈ:</b> %6<br>"
                                   "📞 <b>SĐT:</b> %7"
                                   ).arg(currentXe->getbienSo())
                                   .arg(currentXe->getLS())
                                   .arg(currentXe->getsoLoi())
                                   .arg(p.getCCCD())
                                   .arg(p.getTen())
                                   .arg(p.getDiaChi())
                                   .arg(p.getSdt());
            infoLabel->setText(infoText);

            for (int row = 0; row < loiTable->rowCount(); ++row) {
                QTableWidgetItem *item = loiTable->item(row, 0);
                if (item) {
                    item->setText(QString::number(row + 1));
                }
            }

            if (loiTable->rowCount() == 0) {
                deleteButton->setEnabled(false);
            }
        }
    });

    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(bienSoEdit, &QLineEdit::returnPressed, findButton, &QPushButton::click);

    dialog.exec();
}

void Police::themxeMoi(vehicleshash* hashtableXe) {
    QDialog dialog;
    dialog.setWindowTitle("THÊM XE MỚI VÀO HỆ THỐNG");
    dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    dialog.setMinimumSize(900, 750);
    dialog.resize(900, 750);

    dialog.setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QFrame *mainFrame = new QFrame();
    mainFrame->setStyleSheet(
        "QFrame {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #27ae60, stop:1 #2ecc71);"
        "border-radius: 12px;"
        "border: 2px solid rgba(255,255,255,0.3);"
        "}"
        );

    QVBoxLayout *frameLayout = new QVBoxLayout(mainFrame);
    frameLayout->setSpacing(12);
    frameLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel("THÊM XE MỚI");
    titleLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 20px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.15);"
        "padding: 15px;"
        "border-radius: 8px;"
        "border: 1px solid rgba(255,255,255,0.3);"
        "text-align: center;"
        "}"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    QLabel *formTitleLabel = new QLabel("THÔNG TIN ĐĂNG KÝ XE");
    formTitleLabel->setStyleSheet(
        "QLabel {"
        "color: white;"
        "font-size: 16px;"
        "font-weight: bold;"
        "background: rgba(255,255,255,0.1);"
        "padding: 12px;"
        "border-radius: 6px;"
        "text-align: center;"
        "}"
        );
    formTitleLabel->setAlignment(Qt::AlignCenter);

    QFrame *typeFrame = new QFrame();
    typeFrame->setStyleSheet(
        "QFrame {"
        "background: rgba(255,255,255,0.9);"
        "border-radius: 8px;"
        "border: 2px solid rgba(255,255,255,0.5);"
        "padding: 15px;"
        "}"
        );
    QVBoxLayout *typeLayout = new QVBoxLayout(typeFrame);

    QLabel *typeLabel = new QLabel("CHỌN LOẠI XE:");
    typeLabel->setStyleSheet("color: #2c3e50; font-weight: bold; font-size: 14px; text-align: center;");
    typeLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    QRadioButton *xeMayRadio = new QRadioButton("🚗 XE MÁY");
    QRadioButton *otoRadio = new QRadioButton("🚙 Ô TÔ");

    xeMayRadio->setStyleSheet(
        "QRadioButton {"
        "color: #2c3e50;"
        "font-size: 13px;"
        "font-weight: bold;"
        "padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "width: 16px;"
        "height: 16px;"
        "}"
        );

    otoRadio->setStyleSheet(
        "QRadioButton {"
        "color: #2c3e50;"
        "font-size: 13px;"
        "font-weight: bold;"
        "padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "width: 16px;"
        "height: 16px;"
        "}"
        );

    radioLayout->addStretch();
    radioLayout->addWidget(xeMayRadio);
    radioLayout->addWidget(otoRadio);
    radioLayout->addStretch();

    typeLayout->addWidget(typeLabel);
    typeLayout->addLayout(radioLayout);

    QFrame *formFrame = new QFrame();
    formFrame->setStyleSheet(
        "QFrame {"
        "   background: rgba(255,255,255,0.9);"
        "   border-radius: 8px;"
        "   border: 2px solid rgba(255,255,255,0.5);"
        "   padding: 20px;"
        "}"
        "QLabel {"
        "   color: #2c3e50;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "   background: transparent;"
        "   min-width: 120px;"
        "   min-height: 20px;"
        "   text-align: center;"
        "}"
        );

    QFormLayout *formLayout = new QFormLayout(formFrame);
    formLayout->setSpacing(8);
    formLayout->setHorizontalSpacing(15);
    formLayout->setVerticalSpacing(8);
    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    QLabel *bienSoLabel = new QLabel("BIỂN SỐ XE");
    bienSoLabel->setMinimumSize(120, 25);
    bienSoLabel->setAlignment(Qt::AlignVCenter | Qt::AlignVCenter);

    QLineEdit *bienSoEdit = new QLineEdit();
    bienSoEdit->setPlaceholderText("VD: 29-A1-12345");
    bienSoEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 3px solid rgba(255,255,255,0.5);"
        "border-radius: 9px;"
        "padding: 10.5px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 3px solid #4ecdc4;"
        "background: white;"
        "}"
        );

    QLabel *cccdLabel = new QLabel("CCCD CHỦ XE");
    cccdLabel->setMinimumSize(120, 25);
    cccdLabel->setAlignment(Qt::AlignVCenter | Qt::AlignVCenter);

    QLineEdit *cccdEdit = new QLineEdit();
    cccdEdit->setPlaceholderText("Nhập 12 số CCCD");
    cccdEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 3px solid rgba(255,255,255,0.5);"
        "border-radius: 9px;"
        "padding: 10.5px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 3px solid #4ecdc4;"
        "background: white;"
        "}"
        );

    QLabel *TenLabel = new QLabel("TÊN CHỦ XE");
    TenLabel->setMinimumSize(120, 25);
    TenLabel->setAlignment(Qt::AlignVCenter | Qt::AlignVCenter);

    QLineEdit *tenEdit = new QLineEdit();
    tenEdit->setPlaceholderText("VD: Nguyễn Văn A");
    tenEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 3px solid rgba(255,255,255,0.5);"
        "border-radius: 9px;"
        "padding: 10.5px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 3px solid #4ecdc4;"
        "background: white;"
        "}"
        );


    QLabel *sdtLabel = new QLabel("SỐ ĐIỆN THOẠI");
    sdtLabel->setMinimumSize(120, 25);
    sdtLabel->setAlignment(Qt::AlignVCenter | Qt::AlignVCenter);

    QLineEdit *sdtEdit = new QLineEdit();
    sdtEdit->setPlaceholderText("VD: 0912345678");
    sdtEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 3px solid rgba(255,255,255,0.5);"
        "border-radius: 9px;"
        "padding: 10.5px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 3px solid #4ecdc4;"
        "background: white;"
        "}"
        );

    QLabel *diaChiLabel = new QLabel("ĐỊA CHỈ");
    diaChiLabel->setMinimumSize(120, 25);
    diaChiLabel->setAlignment(Qt::AlignVCenter | Qt::AlignVCenter);

    QLineEdit *diaChiEdit = new QLineEdit();
    diaChiEdit->setPlaceholderText("VD: 123 Duong ABC, Phuong X, Thanh pho Y");
    diaChiEdit->setStyleSheet(
        "QLineEdit {"
        "background: rgba(255,255,255,0.95);"
        "border: 3px solid rgba(255,255,255,0.5);"
        "border-radius: 9px;"
        "padding: 10.5px;"
        "font-size: 14px;"
        "color: #333;"
        "min-height: 25px;"
        "}"
        "QLineEdit:focus {"
        "border: 3px solid #4ecdc4;"
        "background: white;"
        "}"
        );

    formLayout->addRow(bienSoLabel, bienSoEdit);
    formLayout->addRow(cccdLabel, cccdEdit);
    formLayout->addRow(TenLabel, tenEdit);
    formLayout->addRow(sdtLabel, sdtEdit);
    formLayout->addRow(diaChiLabel, diaChiEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(12);
    buttonLayout->setContentsMargins(0, 8, 0, 0);

    QPushButton *addButton = new QPushButton("THÊM XE MỚI");
    addButton->setMinimumSize(150, 40);
    addButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #e74c3c, stop:1 #c0392b);"
        "color: white;"
        "border: none;"
        "padding: 12px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "text-align: center;"
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

    QPushButton *closeButton = new QPushButton("ĐÓNG");
    closeButton->setMinimumSize(100, 40);
    closeButton->setStyleSheet(
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "stop:0 #95a5a6, stop:1 #7f8c8d);"
        "color: white;"
        "border: none;"
        "padding: 12px 20px;"
        "font-size: 13px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "text-align: center;"
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

    buttonLayout->addStretch();
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();

    frameLayout->addWidget(titleLabel);
    frameLayout->addWidget(formTitleLabel);
    frameLayout->addWidget(typeFrame);
    frameLayout->addWidget(formFrame);
    frameLayout->addLayout(buttonLayout);

    mainLayout->addWidget(mainFrame);

    int selectedLoaiXe = 1;

    QObject::connect(xeMayRadio, &QRadioButton::toggled, [&](bool checked) {
        if (checked) selectedLoaiXe = 1;
    });

    QObject::connect(otoRadio, &QRadioButton::toggled, [&](bool checked) {
        if (checked) selectedLoaiXe = 2;
    });

    xeMayRadio->setChecked(true);

    QObject::connect(addButton, &QPushButton::clicked, [&]() {

        QString bienSo = bienSoEdit->text().trimmed();
        QString cccd = cccdEdit->text().trimmed();
        QString ten = tenEdit->text().trimmed();
        QString sdt = sdtEdit->text().trimmed();
        QString diaChi = diaChiEdit->text().trimmed();

        if (bienSo.isEmpty() || cccd.isEmpty() || ten.isEmpty() || sdt.isEmpty() || diaChi.isEmpty()) {
            QMessageBox::warning(&dialog, "LỖI", "VUI LÒNG NHẬP ĐẦY ĐỦ THÔNG TIN!");
            return;
        }

        if (cccd.length() != 12) {
            QMessageBox::warning(&dialog, "LỖI", "CCCD PHẢI CÓ ĐÚNG 12 SỐ!");
            return;
        }

        if (hashtableXe->find(bienSo) != nullptr) {
            QMessageBox::warning(&dialog, "LỖI", "BIỂN SỐ XE " + bienSo + " ĐÃ TỒN TẠI TRONG HỆ THỐNG!");
            return;
        }

        try {
            Xe* xe = taoXeMoi(bienSo, selectedLoaiXe);
            xe->setOwner(cccd);
            qDebug() << "Da them thanh cong cccd " << xe->getID() << "cho xe co bien so" << xe->getbienSo();
            hashtableXe->insertToHash(xe);

            themXeVaoPerson(cccd, bienSo, ten, sdt, diaChi, selectedLoaiXe, xe);
            capNhatFileBienSo(xe);

            QString successMsg = QString(
                                     "✅ <b>ĐÃ THÊM XE MỚI THÀNH CÔNG!</b><br><br>"
                                     "🚗 <b>Biển số:</b> %1<br>"
                                     "🔤 <b>Loại xe:</b> %2<br>"
                                     "👤 <b>Chủ xe:</b> %3<br>"
                                     "📞 <b>SĐT:</b> %4<br>"
                                     "🏠 <b>Địa chỉ:</b> %5<br><br>"
                                     "<i>Thông tin đã được lưu vào hệ thống</i>"
                                     ).arg(bienSo)
                                     .arg(selectedLoaiXe == 1 ? "Xe máy" : "Ô tô")
                                     .arg(ten)
                                     .arg(sdt)
                                     .arg(diaChi);

            QMessageBox::information(&dialog, "THÀNH CÔNG", successMsg);

            bienSoEdit->clear();
            cccdEdit->clear();
            tenEdit->clear();
            sdtEdit->clear();
            diaChiEdit->clear();
            bienSoEdit->setFocus();

        } catch (const std::exception& e) {
            QMessageBox::critical(&dialog, "LỖI", "CÓ LỖI XẢY RA KHI THÊM XE: " + QString(e.what()));
        }
    });

    QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.exec();
}

void capNhatFileBienSo(Xe* xe) {
    QString bienSo = xe->getbienSo();

    QFile fileIn(finalbienSo);
    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở file biển số để đọc";
        return;
    }

    QTextStream in(&fileIn);
    QStringList lines;
    bool updated = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.startsWith(bienSo) && !updated) {
            QString newLine = bienSo;

            Node<Pair>* currentLoi = xe->dsLoi.begin();
            if (currentLoi != nullptr) {
                newLine += " |";
                while (currentLoi != nullptr) {
                    newLine += " " + currentLoi->getdata().key + " " + currentLoi->getdata().value + " ";
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
        lines.append(line);
    }
    fileIn.close();

    if (!updated) {
        lines.append(bienSo);
    }

    QFile fileOut(finalbienSo);
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở file biển số để ghi";
        return;
    }

    QTextStream out(&fileOut);
    foreach (const QString &line, lines) {
        out << line << "\n";
    }
    fileOut.close();
}

void capNhatFileCCCD(const QString& cccd, const QString& bienSo) {
    QFile fileIn(finalCCCD);
    if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở file CCCD để đọc";
        return;
    }

    QTextStream in(&fileIn);
    QStringList lines;
    bool updated = false;

    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.contains(cccd) && !updated) {
            int firstPipe = line.indexOf('|');
            int secondPipe = line.indexOf('|', firstPipe + 1);

            if (firstPipe != -1 && secondPipe != -1) {
                QString bienSoPart = line.mid(firstPipe + 1, secondPipe - firstPipe - 1).trimmed();
                bienSoPart += " " + bienSo;
                line = line.left(firstPipe + 1) + " " + bienSoPart + line.mid(secondPipe);
                updated = true;
            }
        }
        lines.append(line);
    }
    fileIn.close();

    QFile fileOut(finalCCCD);
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Không thể mở file CCCD để ghi";
        return;
    }

    QTextStream out(&fileOut);
    foreach (const QString &line, lines) {
        out << line << "\n";
    }
    fileOut.close();
}

Xe* taoXeMoi(const QString& bienSo, int loai) {
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

void themXeVaoPerson(const QString& cccd, const QString& bienSo, const QString& ten,
                     const QString& sdt, const QString& diachi, int loai, Xe* xe) {
    try {
        Person &p = getByCCCD(cccd, *hashtableNguoi);
        p.getXe()->insertToHash(xe);

        capNhatFileCCCD(cccd, bienSo);
        QMessageBox::information(nullptr, "Thành công",
                                 QString("Đã thêm xe vào chủ xe có sẵn (CCCD: %1)").arg(cccd));

    } catch (...) {
        Person newPerson(cccd, ten, sdt, diachi);
        newPerson.getXe()->insertToHash(xe);
        hashtableNguoi->insert(cccd, newPerson);

        QFile cccdFile(finalCCCD);
        if (cccdFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&cccdFile);
            out << cccd << " | " << bienSo << " | " << ten << " | " << diachi << " | " << sdt << "\n";
            cccdFile.close();
            QMessageBox::information(nullptr, "Thành công", "Đã ghi vào file cccd.txt");
        } else {
            QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file cccd.txt");
        }
    }
}



bool Police::dangNhap(const QString& i,const QString& p){

    int pos = dsPolice->hash_function(i);

    Node<Pair>* node = dsPolice->buckets[pos].begin();
    while (node != nullptr){
        Pair& check = node->refgetdata();
        if (check.key == i && check.value == p) return true;
        node = node->getnext();
    }
    return false;
}
