#include "Violation.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Violation::Violation(const int& id, const QString& loi, const int& tien, bool State)
    : id_loi(id), loiViPham(loi), mucPhat(tien), State(State){}

Violation::~Violation() {}

void Violation::display(){
    qDebug() << "Loi vi pham: " << loiViPham<< " - " << " muc phat tien " << mucPhat << "-";
    if (State == true) qDebug() << "da dong phat";
    else qDebug() << "chua dong phat";
}

bool Violation::getState(){
    return State;
}
void Violation :: setState(bool state){
    this->State = state;
}

int Violation::getID() {
    return id_loi;
}

QString Violation::getLoiViPham() {
    return loiViPham;
}

int Violation::getMucPhat() {
    return mucPhat;
}

void Violation::setLoiViPham(const QString& name) {
    this->loiViPham = name;
}

void Violation::setMucPhat(const double& fine) {
    this->mucPhat = fine;
}

void readDSLoi(Mylist<Violation>& list, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "mo file that bai";
        return;
    }
    qDebug() << "mo file thanh cong";

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
        list.push_back(p);
    }
    file.close();
}
