#include "Menu.h"
#include "StartupDialog.h"
#include "Motor.h"
#include "DataGenerator.h"
#include "Car.h"
#include "Police.h"
#include "Citizen.h"
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QFrame>
#include <QTimer>
#include <QFile>
#include <QStyle>
#include <QPainter>

vehicleshash* hashtableXe = new vehicleshash(100, 100, 100);
HashTable<Person>* hashtableNguoi = new HashTable<Person>(1000);
Mylist<Violation> dsMucPhatMotor;
Mylist<Violation> dsMucPhatCar;

QString ghepFile(const QString& Link, const QString& File) {
    return Link + File;
}

// INPUT FILE
QString Link = "D:\\DaiHoc\\Nam2\\PBL2\\DoHoa\\PBL2\\";
QString finalMaVung = ghepFile(Link, "mavung.txt");
QString finalMotor = ghepFile(Link, "Motor.txt");
QString finalCar = ghepFile(Link, "Car.txt");
QString finalCCCD = ghepFile(Link, "cccd.txt");
QString finalbienSo = ghepFile(Link, "bienso.txt");
QString finalpolice = ghepFile(Link,"police.txt");

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    qDebug() << "Menu đang được khởi tạo...";

    stackedWidget = new QStackedWidget(this);
    setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #ecf0f1, stop:1 #bdc3c7);"
        );

    setupMainMenu();
    setupPoliceMenu();
    setupCitizenMenu();

    stackedWidget->addWidget(mainMenuWidget);
    stackedWidget->addWidget(policeMenuWidget);
    stackedWidget->addWidget(citizenMenuWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);


    showMainMenu();

    setWindowTitle("Hệ Thống Quản Lý Xe Bị Phạt Nguội");
    resize(650, 480);
    setMinimumSize(480, 480);
    setWindowIcon(QIcon(":/image/logo.png"));

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    if (primaryScreen) {
        QRect screenGeometry = primaryScreen->availableGeometry();
        move(screenGeometry.center() - rect().center());
    }
    qDebug() << "Menu khởi tạo xong";
}

void Menu::setupMainMenu()
{
    mainMenuWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(mainMenuWidget);
    setWindowIcon(QIcon(":/image/logo.png"));

    mainMenuWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #27AE60, stop:0.5 #2ECC71, stop:1 #1E8449);"
        );

    QLabel *titleLabel = new QLabel("HỆ THỐNG QUẢN LÝ XE BỊ PHẠT NGUỘI");
    titleLabel->setStyleSheet(
      "font-size: 20px; "
        "font-weight: bold; "
        "color: white; "
        "margin: 30px; "
        "padding: 15px; "
        "background-color: rgba(39, 174, 96, 0.7); "
        "border-radius: 12px; "
        "border: 2px solid rgba(255, 255, 255, 0.3);"
        "box-shadow: 0 4px 15px rgba(0, 0, 0, 0.3);"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    QPushButton *policeBtn = new QPushButton("Đăng nhập Công an");
    QPushButton *citizenBtn = new QPushButton("Đăng nhập Người dân");
    QPushButton *exitBtn = new QPushButton("Thoát");

    QString buttonStyle =
        "QPushButton {"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #27AE60, stop:0.5 #229954, stop:1 #1E8449);"
        "color: white;"
        "border: 2px solid rgba(255, 255, 255, 0.3);"
        "padding: 15px 25px;"
        "font-size: 14px;"
        "font-weight: bold;"
        "border-radius: 10px;"
        "margin: 8px;"
        "min-width: 200px;"
        "box-shadow: 0 4px 15px rgba(39, 174, 96, 0.5);"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #2ECC71, stop:0.5 #27AE60, stop:1 #229954);"
        "border: 2px solid rgba(255, 255, 255, 0.5);"
        "box-shadow: 0 6px 20px rgba(39, 174, 96, 0.7);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "stop:0 #1E8449, stop:0.5 #186A3B, stop:1 #145A32);"
        "box-shadow: 0 2px 8px rgba(39, 174, 96, 0.3);"
        "}";

    policeBtn->setStyleSheet(buttonStyle);
    citizenBtn->setStyleSheet(buttonStyle);
    exitBtn->setStyleSheet(buttonStyle);

    connect(policeBtn, &QPushButton::clicked, this, &Menu::logIn);
    connect(citizenBtn, &QPushButton::clicked, this, &Menu::showCitizenMenu);
    connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    layout->addWidget(titleLabel);
    layout->addStretch();
    layout->addWidget(policeBtn);
    layout->addWidget(citizenBtn);
    layout->addWidget(exitBtn);
    layout->addStretch();

    layout->setAlignment(Qt::AlignCenter);
}


void Menu::logIn()
{
    Police *p = new Police();
    bool loggedIn = false;

    do {
        QString id, password;

        if (this->showLoginDialog(id, password)) {
            if (p->dangNhap(id, password)) {
                loggedIn = true;
                QMessageBox::information(nullptr, "Thành công", "Đăng nhập thành công!");
                showPoliceMenu();
            } else {
                QMessageBox::warning(nullptr, "Lỗi", "ID hoặc mật khẩu không đúng!");
            }
        } else {
            break;
        }

    } while (!loggedIn);

    if (!loggedIn) {
        QMessageBox::information(nullptr, "Thông báo", "Đã thoát đăng nhập.");
    }
}

void Menu::setupPoliceMenu()
{
    policeMenuWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(policeMenuWidget);

    policeMenuWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #e3f2fd, stop:1 #bbdefb);"
        );

    layout->setSpacing(6);
    layout->setContentsMargins(15, 10, 15, 10);

    QLabel *titleLabel = new QLabel("MENU CÔNG AN");
    titleLabel->setStyleSheet(
        "font-size: 18px; font-weight: bold; color: #1565c0;"
        "background-color: #e3f2fd;"
        "padding: 8px;"
        "border-radius: 8px;"
        "border: 2px solid #1976d2;"
        "margin: 8px;"
        "text-shadow: 1px 1px 2px rgba(0,0,0,0.3);"
        );
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: #1976d2; height: 2px; margin: 3px;");
    line->setFixedHeight(2);

    QPushButton *btn1 = new QPushButton("📊 Xem thống kê tổng quan");
    QPushButton *btn2 = new QPushButton("🔍 Tìm xe theo biển số");
    QPushButton *btn3 = new QPushButton("🆔 Tra cứu theo CCCD");
    QPushButton *btn4 = new QPushButton("➕ Thêm lỗi vi phạm cho xe");
    QPushButton *btn5 = new QPushButton("🗑️ Chỉnh lỗi đã đóng phạt");
    QPushButton *btn6 = new QPushButton("🚗 Thêm xe mới vào hệ thống");
    QPushButton *backBtn = new QPushButton("↩️ Quay lại");

    QString buttonStyle =
        "QPushButton {"
        "background-color: #1976d2;"
        "color: white;"
        "border: none;"
        "padding: 10px 8px;"
        "font-size: 12px;"
        "font-weight: bold;"
        "border-radius: 6px;"
        "margin: 2px;"
        "min-height: 20px;"
        "border-bottom: 2px solid #0d47a1;"
        "}"
        "QPushButton:hover {"
        "background-color: #1565c0;"
        "border-bottom: 2px solid #0a3578;"
        "}"
        "QPushButton:pressed {"
        "background-color: #0d47a1;"
        "border-bottom: 1px solid #0a3578;"
        "}";

    QList<QPushButton*> buttons = {btn1, btn2, btn3, btn4, btn5, btn6, backBtn};
    for (QPushButton *btn : buttons) {
        btn->setStyleSheet(buttonStyle);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        btn->setMinimumHeight(35);
    }
    Police *p = new Police();
    QObject::connect(btn1, &QPushButton::clicked, this, [this, p]() {
        if (hashtableXe && hashtableXe->cachedtongsoXe > 0) {
            hashtableXe->thongke();
        } else {
            QMessageBox::information(this, "Thông báo", "Hệ thống chưa có dữ liệu xe!");
        }
    });
    QObject::connect(btn2, &QPushButton::clicked, this, [this, p]() {
        p->timXe(hashtableXe);
    });
    QObject::connect(btn3, &QPushButton::clicked, this, [this, p]() {
        p->truyvanCCCD(hashtableNguoi);
    });
    QObject::connect(btn4, &QPushButton::clicked, this, [this, p]() {
        p->themloiXe(hashtableXe);
    });
    QObject::connect(btn5, &QPushButton::clicked, this, [this, p]() {
        p->xoaloiXe(hashtableXe);
    });
    QObject::connect(btn6, &QPushButton::clicked, this, [this, p]() {
        p->themxeMoi(hashtableXe);
    });
    QObject::connect(backBtn, &QPushButton::clicked, this, &Menu::showMainMenu);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->addWidget(line);
    layout->addStretch(1);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);
    layout->addWidget(btn5);
    layout->addWidget(btn6);
    layout->addStretch(1);
    layout->addWidget(backBtn);
    layout->addStretch(1);
}

void Menu::setupCitizenMenu()
{
    citizenMenuWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(citizenMenuWidget);

    citizenMenuWidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #ffebee, stop:1 #ffcdd2);"
        );

    layout->setSpacing(12);
    layout->setContentsMargins(25, 20, 25, 20);

    QLabel *titleLabel = new QLabel("MENU NGƯỜI DÂN");
    titleLabel->setStyleSheet(
        "font-size: 20px; font-weight: bold; color: #c62828;"
        "background-color: #ffebee;"
        "padding: 12px;"
        "border-radius: 10px;"
        "border: 2px solid #d32f2f;"
        "margin: 10px;"
        "text-shadow: 1px 1px 2px rgba(0,0,0,0.3);"
        );
    titleLabel->setAlignment(Qt::AlignCenter);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: #d32f2f; height: 2px; margin: 5px;");
    line->setFixedHeight(2);

    QPushButton *btn1 = new QPushButton("📊 Xem thống kê tổng quan");
    QPushButton *btn2 = new QPushButton("🔍 Tra cứu xe theo biển số");
    QPushButton *btn3 = new QPushButton("🆔 Tra cứu theo CCCD");
    QPushButton *backBtn = new QPushButton("↩️ Quay lại");

    QString buttonStyle =
        "QPushButton {"
        "background-color: #d32f2f;"
        "color: white;"
        "border: none;"
        "padding: 14px 10px;"
        "font-size: 13px;"
        "font-weight: bold;"
        "border-radius: 8px;"
        "margin: 4px;"
        "min-height: 25px;"
        "border-bottom: 3px solid #b71c1c;"
        "}"
        "QPushButton:hover {"
        "background-color: #c62828;"
        "border-bottom: 3px solid #8b0000;"
        "}"
        "QPushButton:pressed {"
        "background-color: #b71c1c;"
        "border-bottom: 1px solid #8b0000;"
        "}";

    QList<QPushButton*> buttons = {btn1, btn2, btn3, backBtn};
    for (QPushButton *btn : buttons) {
        btn->setStyleSheet(buttonStyle);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        btn->setMinimumHeight(45);
    }

    Citizen *c = new Citizen;

    QObject::connect(btn1, &QPushButton::clicked, this, [this, c]() {
        if (hashtableXe && hashtableXe->cachedtongsoXe > 0) {
            hashtableXe->thongke();
        } else {
            QMessageBox::information(this, "Thông báo", "Hệ thống chưa có dữ liệu xe!");
        }
    });
    QObject::connect(btn2, &QPushButton::clicked, this, [this, c]() {
        c->timXe(hashtableXe);
    });
    QObject::connect(btn3, &QPushButton::clicked, this, [this, c]() {
        c->truyvanCCCD(hashtableNguoi);
    });
    QObject::connect(backBtn, &QPushButton::clicked, this, &Menu::showMainMenu);

    layout->addStretch(1);
    layout->addWidget(titleLabel);
    layout->addWidget(line);
    layout->addStretch(2);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addStretch(2);
    layout->addWidget(backBtn);
    layout->addStretch(1);
}

void Menu::showMainMenu()
{
    stackedWidget->setCurrentWidget(mainMenuWidget);
}

void Menu::showPoliceMenu()
{
    stackedWidget->setCurrentWidget(policeMenuWidget);
}

void Menu::showCitizenMenu()
{
    stackedWidget->setCurrentWidget(citizenMenuWidget);
}

void khoiTaoHeThong(StartupDialog& startup) {
    startup.show();

    QTimer::singleShot(500, &startup, [&startup]() {
        try {
            hashtableXe = new vehicleshash(5, 5, 50);
            startup.addStatusMessage("[OK] Đã tạo danh sách lưu thông tin xe", true);
            startup.updateProgress(10);
        } catch (const std::exception& e) {
            startup.addStatusMessage(QString("Lỗi tạo danh sách lưu thông tin xe: %1").arg(e.what()), false);
        }
    });

    QTimer::singleShot(1000, &startup, [&startup]() {
        try {
            hashtableNguoi = new HashTable<Person>(1000);
            startup.addStatusMessage("[OK] Đã tạo danh sách lưu thông tin người", true);
            startup.updateProgress(20);
        } catch (const std::exception& e) {
            startup.addStatusMessage(QString("Lỗi tạo danh sách lưu thông tin người: %1").arg(e.what()), false);
        }
    });

    QTimer::singleShot(1500, &startup, [&startup]() {
        try {
            Xe::docFileMaVung(finalMaVung);
            if (Xe::dsMaVung.size() > 0) {
                startup.addStatusMessage(QString("Đã đọc mã biển số xe của các tỉnh thành: %1 tỉnh/thành").arg(Xe::dsMaVung.size()), true);
            } else {
                startup.addStatusMessage("Không đọc được mã biển số xe của các tỉnh thành!", false);
            }
            startup.updateProgress(40);
        } catch (const std::exception& e) {
            startup.addStatusMessage(QString("Lỗi đọc mã vùng: %1").arg(e.what()), false);
        }
    });

    QTimer::singleShot(2000, &startup, [&startup]() {
        try {
            readDSLoi(dsMucPhatMotor, finalMotor);
            startup.addStatusMessage(QString("Đã đọc mức phạt xe máy: %1 loại").arg(dsMucPhatMotor.size()), true);
            startup.updateProgress(60);
        } catch (const std::exception& e) {
            startup.addStatusMessage(QString("Lỗi đọc phạt xe máy: %1").arg(e.what()), false);
        }
    });

    QTimer::singleShot(2500, &startup, [&startup]() {
        try {
            readDSLoi(dsMucPhatCar, finalCar);
            startup.addStatusMessage(QString("Đã đọc mức phạt xe cơ giới: %1 loại").arg(dsMucPhatCar.size()), true);
            startup.updateProgress(80);
        } catch (const std::exception& e) {
            startup.addStatusMessage(QString("Lỗi đọc phạt xe cơ giới: %1").arg(e.what()), false);
        }
    });

    QTimer::singleShot(3000, &startup, [&startup]() {
        startup.addStatusMessage("[HOÀN TẤT] Hệ thống đã sẵn sàng!", true);
        startup.updateProgress(100);

        QDialog dialog;
        dialog.setWindowTitle("Lựa chọn đọc dữ liệu");
        dialog.setFixedSize(450, 250);
        dialog.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxQuestion));

        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

        QLabel *iconLabel = new QLabel;
        QPixmap customIcon(":/image/dau_hoi_cham.png");

        if (!customIcon.isNull()) {
            iconLabel->setPixmap(customIcon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        iconLabel->setAlignment(Qt::AlignCenter);

        QLabel *label = new QLabel("Bạn có muốn đọc dữ liệu từ file cccd.txt và bienso.txt?");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("font-size: 12pt; margin: 15px;");

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        QPushButton *yesBtn = new QPushButton("✅ Đọc dữ liệu");
        QPushButton *noBtn = new QPushButton("❌ Bỏ qua");

        yesBtn->setStyleSheet("QPushButton { font-size: 11pt; padding: 8px 16px; background: #27ae60; color: white; border: none; border-radius: 4px; }");
        noBtn->setStyleSheet("QPushButton { font-size: 11pt; padding: 8px 16px; background: #e74c3c; color: white; border: none; border-radius: 4px; }");

        buttonLayout->addStretch();
        buttonLayout->addWidget(yesBtn);
        buttonLayout->addWidget(noBtn);
        buttonLayout->addStretch();

        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(label);
        mainLayout->addLayout(buttonLayout);

        QObject::connect(yesBtn, &QPushButton::clicked, &dialog, [&dialog, &startup]() {
            dialog.accept();

            if (!hashtableXe || !hashtableNguoi) {
                startup.addStatusMessage("LỖI: Biến toàn cục chưa được khởi tạo!", false);
                return;
            }

            QFile cccdFile(finalCCCD);
            QFile biensoFile(finalbienSo);
            QFile policeFile(finalpolice);

            bool fileExist = cccdFile.exists() && biensoFile.exists() && policeFile.exists();

            if (!fileExist) {
                DataGenerator::taoDuLieuMau(finalCCCD, finalbienSo, 1000);
                startup.addStatusMessage("file không tồn tại", true);
            }

            try {
                Mylist<Violation> dsGop = dsMucPhatMotor;
                Node<Violation>* v = dsMucPhatCar.begin();
                while (v != nullptr) {
                    dsGop.push_back(v->getdata());
                    v = v->getnext();
                }

                DataGenerator::taoXeMau(hashtableXe, 0, *hashtableNguoi);
                docFilePolice(finalpolice);

                startup.addStatusMessage("[THÀNH CÔNG] Đọc dữ liệu thành công!", true);

            } catch (const std::exception& e) {
                startup.addStatusMessage(QString("Lỗi khi đọc dữ liệu: %1").arg(e.what()), false);
            }

            startup.onReadDataChoiceClicked(true);
        });

        QObject::connect(noBtn, &QPushButton::clicked, &dialog, [&dialog, &startup]() {
            dialog.reject();
            startup.onReadDataChoiceClicked(false);
        });

        dialog.exec();
    });
}

bool Menu::showLoginDialog(QString &id, QString &password)
{
    QDialog loginDialog;
    loginDialog.setWindowTitle("Đăng nhập hệ thống công an");
    loginDialog.setWindowIcon(QIcon(":/image/logo.png"));
    loginDialog.setFixedSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(&loginDialog);

    QLabel *titleLabel = new QLabel("ĐĂNG NHẬP CÔNG AN");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; margin-bottom: 20px;");

    QLabel *idLabel = new QLabel("ID:");
    QLineEdit *idEdit = new QLineEdit();
    idEdit->setPlaceholderText("Nhập ID...");

    QLabel *passLabel = new QLabel("Mật khẩu:");
    QLineEdit *passEdit = new QLineEdit();
    passEdit->setPlaceholderText("Nhập mật khẩu...");
    passEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("Đăng nhập");
    QPushButton *cancelBtn = new QPushButton("Thoát");

    layout->addWidget(titleLabel);
    layout->addWidget(idLabel);
    layout->addWidget(idEdit);
    layout->addWidget(passLabel);
    layout->addWidget(passEdit);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(loginBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);

    bool loginSuccess = false;

    QObject::connect(loginBtn, &QPushButton::clicked, [&]() {
        id = idEdit->text();
        password = passEdit->text();

        if (id.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(&loginDialog, "Lỗi", "Vui lòng nhập đầy đủ ID và mật khẩu!");
            return;
        }

        loginSuccess = true;
        loginDialog.accept();
    });

    QObject::connect(cancelBtn, &QPushButton::clicked, [&]() {
        loginDialog.reject();
    });

    int result = loginDialog.exec();

    return (result == QDialog::Accepted && loginSuccess);
}
