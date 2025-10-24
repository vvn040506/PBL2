#pragma once
#include"HashTable.h"
#include"Person.h"
#include "pair.hpp"
#include <iostream>
#include <string>
#include "HashFunction.h"
#include "Xe.h"
#include "Person.h"
using namespace std;


class Citizen: public Person{
    
    public:
        Citizen();
        Citizen(const string&);
        ~Citizen();
};