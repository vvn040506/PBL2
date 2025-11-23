#ifndef PAIR_H
#define PAIR_H

#include <QString>

struct Pair {

    QString key;
    QString value;
    bool State;

    Pair(){}
    Pair(QString key, QString value, bool State) : key(key), value(value),State(State){}


    bool operator==(const Pair& other) const {
        return key == other.key && value == other.value;
    }
};

#endif
