#ifndef PAIR_H
#define PAIR_H

#include <string>
using namespace std;

struct Pair {
    string key;
    string value;
    Pair(){}
    Pair(string key, string value) : key(key), value(value){}
    friend ostream& operator<<(ostream& os, const Pair& p) {
        os << "(" << p.key << ", " << p.value << ")";
        return os;
    }
    bool operator==(const Pair& other) const {
        return key == other.key && value == other.value;
    }
    Pair& operator=(const Pair& other) {
        if (this == &other) return *this;
        key = other.key;
        value = other.value;
        return *this;
    }
};

#endif