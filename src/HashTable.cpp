#include "../include/HashTable.h"

using namespace std;


HashTable::HashTable(int num): num_of_buckets(num)
{
	this->buckets = new Buckets*[num_of_buckets];
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
	// 	this->buckets[i] = new Buckets(); 
}

HashTable::~HashTable()
{
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
			delete this->buckets[i];
	}
	delete[] this->buckets;
}

void HashTable::insertPoint(int bucket_num,string str,vector<int> &v)
{
	if (!this->buckets[bucket_num])
		this->buckets[bucket_num] = new Buckets(str,v);
	else
		this->buckets[bucket_num]->insertPointAtList(str,v);
}

void HashTable::printBucket(int bucket_num)
{
	if (this->buckets[bucket_num])
		this->buckets[bucket_num]->printList();
	else
		cout <<"Bucket not initialized"<<std::endl;
}