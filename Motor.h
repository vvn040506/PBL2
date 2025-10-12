#include<bits/stdc++.h>
#include"Vehicle.h"

class Bike: public Vehicle{
    private:
        string type;
    public:
        Bike();
        void display() override;

};
