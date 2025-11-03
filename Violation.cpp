#include<iostream>
#include<fstream>
#include"Violation.h"
using namespace std;
Violation::Violation(const int& id, const string& loi, const int& tien,bool State)
    : id_loi(id), loiViPham(loi), mucPhat(tien),State(State){} 

Violation::~Violation() {}
void Violation::display(){
    cout << "Loi vi pham: " << loiViPham<< " - " << " muc phat tien " << mucPhat << "-";
    if (State == true) cout << "da dong phat" << endl;
        else cout << "chua dong phat" <<endl;
}
int Violation::getID(){
    return id_loi;
}
string Violation::getLoiViPham(){
    return loiViPham;
}
int Violation::getMucPhat(){
    return mucPhat;
}
bool Violation::getState(){
    return State;
}
void Violation :: setState(bool state){
    this->State = state;
}
void Violation::setLoiViPham(const string &name){
    this->loiViPham = name;
}
void Violation::setMucPhat(const double &fine){
    this->mucPhat = fine;
}

void readDSLoi(Mylist<Violation>& list, const string& filename) {
    ifstream fs(filename);
    if (!fs.is_open()){
        cout << "mo file that bai" << endl;
        return;
    }
    cout << "mo file thanh cong" << endl;

    string line;
    int id;
    int mucPhat;
    string tenLoi;

    while (getline(fs, line)) {
        if (line.empty()) continue;
        
        size_t first_space = line.find(' '); 
        if (first_space == string::npos) continue;

        size_t last_space = line.find_last_of(' ');
        if (last_space == string::npos || last_space <= first_space) continue;

        string idStr = line.substr(0, first_space);
        string mucPhatStr = line.substr(last_space + 1);

        tenLoi = line.substr(first_space + 1, last_space - (first_space + 1));
        
            id = stoi(idStr);
            mucPhat = stoi(mucPhatStr);

            Violation p(id, tenLoi, mucPhat,true);
            list.push_back(p);
    }
    fs.close();
}
