#ifndef _GENERAL_FUNCTIONS_H_
#define _GENERAL_FUNCTIONS_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../include/HashTable.h"
#include "../include/normal_distr.h"

void storeDataset(std::vector<std::vector<int>>& ,char *,int &);
void search_neighbors(HashTable **, std::vector<int> &,char*, int&, int&, int&, int&);
int find_hashFunction(std::vector<int>&, std::vector<int>&, std::vector<int> &, int&, int&, int&);

#endif