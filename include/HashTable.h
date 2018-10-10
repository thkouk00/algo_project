#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <vector>
#include "../include/Buckets.h"

class HashTable
{
	int num_of_buckets;
	Buckets **buckets;
public:
	HashTable(int);
	~HashTable();
	void insertPoint(int,std::string,std::vector<int>&);
	void printBucket(int);
	
};




#endif