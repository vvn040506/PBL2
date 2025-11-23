#include "mainwindow.h"
#include "StartupDialog.h"
#include "Menu.h"
#include "DataGenerator.h"
#include <QApplication>
#include <QMessageBox>

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern Mylist<Violation> dsMucPhatMotor;
extern Mylist<Violation> dsMucPhatCar;

void khoiTaoHeThong(StartupDialog& startup);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartupDialog startup;

    khoiTaoHeThong(startup);

    if (startup.exec() == QDialog::Accepted) {
        Menu menu;
        menu.show();
        return a.exec();
    }

    return 0;
}
