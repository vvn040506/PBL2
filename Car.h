#include<bits/stdc++.h>
#include"Vehicle.h"

using namespace std;

class Car: public Vehicle{
    private:
        string type;
    public:
        Car();
        void display() override;
        void setType();
};