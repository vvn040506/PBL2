#include <iostream>
#include <fstream>
#include "Mylist.h"
#include "pair.hpp"
using namespace std;

void readToList(Mylist<Pair>& list, const string& filename) {
    ifstream fs;
    fs.open(filename);
    if (fs.is_open()){
        cout <<"mo file thanh cong";
    }
    else {
        cout <<"mo file that bai";
    }
    string key, value;
    while (fs >> key >> value) {
        Pair p(key, value);
        list.push_back(p);
    }

    fs.close();
}

int main() {
    Mylist<Pair> provinces; 
    Mylist<Pair> vehicleTypes; 

    readToList(provinces, "provinces.txt");
    readToList(vehicleTypes, "vehiclestype.txt");

    cout << "Danh sach tinh thanh:\n";
    provinces.print();

    cout << "Danh sach loai xe:\n";
    vehicleTypes.print();

    return 0;
}