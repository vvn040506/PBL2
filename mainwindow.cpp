#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/logo.png"));
    setWindowTitle("Menu Chính - Hệ Thống Quản Lý Xe");

    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/image/logo.png");
    logoPixmap = logoPixmap.scaled(1, 1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setAlignment(Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}
