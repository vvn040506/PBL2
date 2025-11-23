#include "StartupDialog.h"
#include <QTimer>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QScrollBar>

StartupDialog::StartupDialog(QWidget *parent)
    : QDialog(parent),
    progressBar(nullptr),
    statusLayout(nullptr),
    continueBtn(nullptr)
{
    setupUI();
    continueBtn->setVisible(false);
}

void StartupDialog::setupUI()
{
    setWindowTitle("Khởi Tạo Hệ Thống");
    setWindowIcon(QIcon(":/image/logo.png"));
    setFixedSize(600, 500);
    setModal(true);
    setStyleSheet("background-color: #fff9e6;");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel("🚀 KHỞI TẠO HỆ THỐNG");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);

    progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setFormat("%p%");
    progressBar->setAlignment(Qt::AlignCenter);

    progressBar->setStyleSheet(
        "QProgressBar {"
        "border: 2px solid #bdc3c7;"
        "border-radius: 8px;"
        "height: 25px;"
        "text-align: center;"
        "background-color: #f8f9fa;"
        "color: #2c3e50;"
        "font-weight: bold;"
        "}"
        "QProgressBar::chunk {"
        "background-color: #3498db;"
        "border-radius: 6px;"
        "}"
        );

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *statusWidget = new QWidget();
    statusLayout = new QVBoxLayout(statusWidget);
    statusLayout->setSpacing(5);

    scrollArea->setWidget(statusWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("border: 1px solid #bdc3c7; border-radius: 8px;");

    continueBtn = new QPushButton("Tiếp Tục");
    continueBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #27ae60; color: white; border: none;"
        "padding: 12px 30px; font-size: 14px; border-radius: 8px;"
        "min-width: 120px;"
        "}"
        "QPushButton:hover { background-color: #219a52; }"
        );
    continueBtn->setFixedSize(150, 60);

    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(progressBar);
    mainLayout->addWidget(scrollArea, 1);
    mainLayout->addWidget(continueBtn, 0, Qt::AlignCenter);

    connect(continueBtn, &QPushButton::clicked, this, [this]() {
        emit continueClicked();
        this->accept();
    });
}

void StartupDialog::addStatusMessage(const QString &message, bool isSuccess)
{
    QHBoxLayout *itemLayout = new QHBoxLayout();

    QLabel *iconLabel = new QLabel();
    iconLabel->setText(isSuccess ? "✅" : "❌");

    QLabel *msgLabel = new QLabel(message);
    msgLabel->setStyleSheet("padding: 5px; font-size: 12px;");

    itemLayout->addWidget(iconLabel);
    itemLayout->addWidget(msgLabel);
    itemLayout->addStretch();

    QWidget *itemWidget = new QWidget();
    itemWidget->setLayout(itemLayout);

    statusLayout->addWidget(itemWidget);

    QTimer::singleShot(50, [this]() {
        QScrollArea *scrollArea = qobject_cast<QScrollArea*>(statusLayout->parentWidget()->parentWidget());
        if (scrollArea) {
            QScrollBar *bar = scrollArea->verticalScrollBar();
            bar->setValue(bar->maximum());
        }
    });
}

void StartupDialog::updateProgress(int value)
{
    progressBar->setValue(value);
}

void StartupDialog::showContinueButton()
{
    continueBtn->setVisible(true);
    continueBtn->setEnabled(true);

    continueBtn->setStyleSheet(
        "QPushButton {"
        "background-color: #27ae60; color: white; border: none;"
        "padding: 12px 30px; font-size: 14px; border-radius: 8px;"
        "font-weight: bold;"
        "border: 2px solid #219a52;"
        "}"
        "QPushButton:hover { background-color: #219a52; }"
        "QPushButton:pressed { background-color: #1e8449; }"
        );
}

void StartupDialog::onReadDataChoiceClicked(bool readData)
{
    if (readData) {
        addStatusMessage("Bắt đầu đọc dữ liệu. Vui lòng đợi...", true);

        QTimer::singleShot(2000, [this]() {
            addStatusMessage("✅ Đọc dữ liệu thành công!", true);
            showContinueButton();
        });
    } else {
        addStatusMessage("Bỏ qua đọc dữ liệu từ file.", true);

        QTimer::singleShot(500, [this]() {
            showContinueButton();
        });
    }
}
