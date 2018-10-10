#include "../include/Buckets.h"

using namespace std;

Buckets::Buckets(string str,vector<int> &v)
{
	Node node(str,v);
	this->List.push_back(node);
}

void Buckets::insertPointAtList(string str,vector<int> &v)
{
	Node node(str,v);
	this->List.push_back(node);
}

void Buckets::printList()
{
	for (list<Node>::iterator it=List.begin();it!=this->List.end();it++)
		it->printPoints();
	// cout <<std::endl;
}