#ifndef PAIR_H
#define PAIR_H

#include <string>
using namespace std;

struct Pair {
    
    string key;
    string value;
    bool State;

    Pair(){}
    Pair(string key, string value, bool State) : key(key), value(value),State(State){}

    friend ostream& operator<<(ostream& os, const Pair& p) {
        os << "(" << p.key << ", " << p.value << ")";
        return os;
    }

    bool operator==(const Pair& other) const {
        return key == other.key && value == other.value;
    }
};

#endif