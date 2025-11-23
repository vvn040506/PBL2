#ifndef CITIZEN_H
#define CITIZEN_H

#include "Person.h"
#include "pair.hpp"
#include "Xe.h"
#include <QWidget>

class Citizen : public Person {
public:
    Citizen();
    Citizen(const QString& id);
    ~Citizen();
    QWidget* citizenMenuWidget;
};

#endif // CITIZEN_H
