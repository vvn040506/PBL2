#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include "HashTable.h"
#include "HashFunction.h"
#include "Violation.h"
#include "Mylist.h"

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);

private slots:
    void showMainMenu();
    void showPoliceMenu();
    void showCitizenMenu();
    void logIn();

private:
    void setupMainMenu();
    void setupPoliceMenu();
    void setupCitizenMenu();
    void SetupHeThong();
    bool showLoginDialog(QString &id, QString &password);
    QStackedWidget *stackedWidget;
    QWidget *mainMenuWidget;
    QWidget *policeMenuWidget;
    QWidget *citizenMenuWidget;
};

extern vehicleshash* hashtableXe;
extern HashTable<Person>* hashtableNguoi;
extern Mylist<Violation> dsMucPhatMotor;
extern Mylist<Violation> dsMucPhatCar;
#endif // MENU_H
