#include "human.h"

using namespace std;

Human :: Human() : age("0"), name("Unknown"), cccd("000000000"), phone("0000000000") {}

Human :: Human(string a, string b, string c, string d) : age(a), name(b), cccd(c), phone(d) {}

Human :: ~Human() {}

void Human::show() {
    cout << "Ten: " << name << "\n";
    cout << "Tuoi: " << age << "\n";
    cout << "CCCD: " << cccd << "\n";
    cout << "SDT: " << phone << "\n";
}

user :: user() : Human() {}
user :: user(string a, string b, string c, string d) : Human(a,b,c,d) {}

void user :: show() {
    cout << "----- Thong tin nguoi tra cuu -----\n";
    Human::show();
}

police :: police() : Human(), id("NULL") {}

police :: police(string a, string b, string c, string d, string id) : Human(a, b, c, d), id(id) {}

void police :: show() {
    cout << "----- Thong tin canh sat -----\n";
    Human::show();
    cout << "Ma canh sat: " << id << "\n";
}

