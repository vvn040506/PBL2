#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include "Mylist.h"
#include "pair.hpp"


void readToList(Mylist<Pair>& list, const string& filename);
#endif