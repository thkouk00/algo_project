#ifndef _NN_SEARCH_H_
#define _NN_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include "../include/HashTable.h"
#include "../include/Buckets.h"
#include "../include/Distance.h"

void NN_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, bool Cosine, std::ofstream &output,double &, double&);
// void NN_search(std::vector<int>&, HashTable **, std::vector<std::vector<int>>&, std::vector<int>&, std::vector<int>&, int&, int&, long double&, std::string&, bool, std::ofstream&);

#endif