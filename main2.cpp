#include "DataGenerator.h"
#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include "Motor.h"
#include "Car.h"
#include "HashFunction.h"
#include "Person.h"
#include "HashTable.h"
#include "DataGenerator.h"
#include "main1.h"
using namespace std;

int main() {
    DataGenerator::taoDuLieuMau("cccd.txt", "bienso.txt", 10000);
    cout << "Data generation completed." << endl;
    return 0;
}