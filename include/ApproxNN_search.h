#ifndef _APPROXNN_SEARCH_H_
#define _APPROXNN_SEARCH_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include "../include/HashTable.h"
#include "../include/Buckets.h"
#include "../include/Euclidean_distance.h"

void ApproxNN_search(std::vector<int>&, HashTable **, std::vector<std::vector<int>>&, std::vector<int>&, std::vector<int>&, int&, int&, long double&);

#endif