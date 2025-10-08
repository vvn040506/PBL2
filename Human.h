#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string.h>
using namespace std;

class Human{
        string age;
        string name;
        string cccd;
        string phone;

    public :
        Human();
        Human(string a, string b, string c, string d);
        virtual ~Human();
        virtual void show();
};

class user : public Human{
    public :
        user();
        user(string a,string b, string c, string d);
        ~user();
        void show() override;
};

class police : public Human {
    private :
        string id;
    public :
        police();
        police(string a, string b, string c, string d,string id);
        void show() override;
};
#endif