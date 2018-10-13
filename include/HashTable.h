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
	void hashDataset(std::vector<std::vector<int>>&, std::vector<int>&, int, int);
	void Nearest_Neighbor(std::vector<int>&, long double&, std::vector<int>&, std::vector<int>&, int&, int&, int&);
	void Range_Neighbor(std::vector<int>&,std::vector<int>&, int&);
	
	// template <typename T>
	// long double Euclidean_Distance(const std::vector<T> & ,const std::vector<T> &, int&);
	long double Euclidean_Distance(const std::vector<int>& ,const std::vector<int>&, int&);

};




#endif