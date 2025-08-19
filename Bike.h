#include<bits/stdc++.h>
#include<map>
#include<fstream>
#include"Vehicle.h"
using namespace std;

class Bike: public Vehicle{
    public:
        friend istream& operator >> (istream& in, Bike& p);
        friend ostream& operator << (ostream& out, Bike p);
        void setvehicle(){}
        void tien_phat(){}
        void dong_phat(){}
};