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
};

#endif