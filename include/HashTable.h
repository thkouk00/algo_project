#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../include/Buckets.h"
#include "../include/normal_distr.h"

class HashTable
{
	int num_of_buckets;
	Buckets **buckets;
public:
	HashTable(int);
	~HashTable();
	void insertPoint(int,std::string,std::vector<int>&);
	void printBucket(int);
	void hashDataset(std::vector<std::vector<int>>&,int,int);
};




#endif