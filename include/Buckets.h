#ifndef _BUCKETS_H_
#define _BUCKETS_H_

#include <iostream>
#include <list>
#include <vector>
#include "../include/Node.h"


class Buckets
{
	std::list<Node> List;
public:
	Buckets(std::string,std::vector<int>&,std::vector<int> &);
	~Buckets(){};
	void insertPointAtList(std::string,std::vector<int> &,std::vector<int> &);
	void printList();
	void bucket_size();
	std::list<Node> access_list();
	
	friend class HashTable;
};



#endif