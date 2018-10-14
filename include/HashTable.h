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
	void insertPoint(int, std::string,std::vector<int>&, std::vector<int>&);
	void printBucket(int);
	int bucket_exist(int&);
	Buckets* access_bucket(int&);
	void hashDataset(std::vector<std::vector<int>>&, std::vector<int>&, int, int);
	//overloading function
	void hashDataset(std::vector<std::vector<int>>&, int);

};




#endif