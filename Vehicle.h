#include<bits/stdc++.h>
#include<vector>
#include"Violation.h"
using namespace std;

class Vehicle{
    protected:
        string plate; // biển số xe
        string owner; // tên chủ sở hữu
        vector<Violation> violations;// ds vi phạm
    public:
        Vehicle();
        void setPlate(string);
        void setOwner(string);
        string getPlate();
        string getOwner();
        virtual void display();
        void addViolation(const Violation& v); 
        double totalFine(); 
};