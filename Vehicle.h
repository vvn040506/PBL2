#include<iostream>
#include<string.h>
#include<map>
using namespace std;

struct NodeInfo;
typedef NodeInfo* Node;

struct HashTableInfo;
typedef HashTableInfo* HashTable;

class Vehicle{
    protected:
        string name, birth, vehicle, punish, licensePlate;
    public:
        Vehicle(){
            name = birth = vehicle = punish = licensePlate = " ";
        };
        int getLicensePlate(){
            int bien_so = stoi(licensePlate);
            return bien_so;
        }
        virtual map <string, string> tien_phat(){}
        void setvehicle(){}
        virtual void dong_phat(){}
        friend struct NodeInfo;
        friend struct HashTableInfo;
        friend istream& operator >> (istream& in, Vehicle& p);
        friend ostream& operator << (ostream& out, Vehicle p);
        friend void add(Vehicle p, HashTable H);
        friend int hash_function(int key, HashTable H);
        friend Node search(HashTable H, string bienso);
};