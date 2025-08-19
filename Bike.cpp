#include<bits/stdc++.h>
#include<fstream>
#include"Vehicle.h"
#include"Bike.h"
using namespace std;

istream& operator >> (istream& in, Bike& p);
ostream& operator << (ostream& out, Bike p);

void Bike::setVehicle(){
            this->vehicle = "xe may";
        }
void Bike::setPenalty()
{
            fstream fs;
            fs.open("bike.txt");
            string money, punishment;
            while(true)
            {
                fs >> money;
                fs.ignore();
                if(!getline(fs, punishment)) break;
                tien_phat[punishment] = money;
            }
            for(auto &x: tien_phat)
                cout << x.first << ", " << x.second << endl;
        }

void Bike::dong_phat()
{
    cout << "So tien phai dong la: " << tien_phat[this->punish] << endl;  
}

