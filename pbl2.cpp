#include<bits/stdc++.h>
#include<map>
using namespace std;

const int capacity = 100;

struct NodeInfo;
typedef NodeInfo* Node;

struct HashTableInfo;
typedef HashTableInfo* HashTable;

class Vehicle{
    protected:
        string name, birth, vehicle, punish, bienso;
    public:
        Vehicle(){
            name = birth = vehicle = punish = bienso = " ";
        };
        int get_bien_so(){
            int bien_so = stoi(bienso);
            return bien_so;
        }
        virtual void tien_phat(map<string, int> &phat){}

        virtual void dong_phat(){}
        friend struct NodeInfo;
        friend struct HashTableInfo;
        friend istream& operator >> (istream& in, Vehicle& p);
        friend ostream& operator << (ostream& out, Vehicle& p);
        friend void add(Vehicle p, HashTable H);
        friend int hash_function(int key, HashTable H);
        friend Node search(HashTable H, string bienso);
};

class Bike: public Vehicle{
    public:
        // friend istream& operator >> (istream& in, Bike& p);
        // friend ostream& operator << (ostream& out, Bike p);
        void setVehicle(){
            this->vehicle = "xe may";
        }
        void tien_phat(map<string, int> &phat){
            phat["Vuot den do"] = 5000000;
        }
        void dong_phat(){
            map<string, int> phat;
            tien_phat(phat);
            if(phat.find(this->punish) != phat.end()){
                cout << "So tien phat phai dong la: " << phat[this->punish] << endl;
            }
        }

};

istream& operator >> (istream &in, Vehicle& p){
    cout << "Nhap bien so xe vi pham: "; in >> p.bienso;
    cout << "Nhap ten chu xe vi pham: "; in.ignore(); getline(in, p.name);
    cout << "Nhap ngay sinh cua chu xe vi pham: "; in >> p.birth;
    // cout << "Nhap loai xe vi pham: "; in.ignore(); getline(in, p.vehicle);
    cout << "Nhap loi vi pham: "; in.ignore(); getline(in, p.punish);
    if(p.birth[2] != '/') p.birth =  "0" + p.birth;
    if(p.birth[4] == '/') p.birth.insert(3, "0");
    while(p.bienso.length() < 5){
        p.bienso = "0" + p.bienso;
    } 
    Bike* bikePtr = dynamic_cast<Bike*>(&p);
    if (bikePtr) bikePtr->setVehicle();
    return in;
}

ostream& operator << (ostream &out, Vehicle &p){
    out << "Thong tin ve xe vi pham: " << endl;
    out << "Bien so xe: " << p.bienso << endl;
    out << "Ten chu so huu xe: " << p.name << endl;
    out << "Ngay sinh cua chu so huu xe: " << p.birth << endl;
    out << "Loai xe vi pham: " << p.vehicle << endl;
    out << "Loi vi pham: " << p.punish << endl;
    p.dong_phat();
    // out << "So tien phat phai dong: ";
    return out;
}

typedef struct NodeInfo{
    Vehicle p;
    struct NodeInfo *next;
} *Node;

typedef struct HashTableInfo{
    unsigned int capacity;
    Node *T;
} *HashTable;

HashTable create_Hash_Table(unsigned int capacity){
    HashTable H = new HashTableInfo;
    H->capacity = capacity;
    H->T = new Node[capacity];
    for(int i = 0; i < capacity; i++){
        H->T[i] = new NodeInfo;
        H->T[i]->next = nullptr;
    }
    return H;
}

int hash_function(int key, HashTable H){
    return key % H->capacity;
}

//thêm xe ph?t

void add(Vehicle p, HashTable H){
    Node newNode = new NodeInfo;
    newNode->p = p;
    int pos = hash_function(p.get_bien_so(), H);
    newNode->next = H->T[pos]->next;
    H->T[pos]->next = newNode;
}

int main(){
    Bike *b = new Bike;
    cin >> *b;
    cout << *b;
}