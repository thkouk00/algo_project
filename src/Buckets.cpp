#include "../include/Buckets.h"

using namespace std;

Buckets::Buckets(string str,vector<int> &v,vector<int> &g)
{
	Node node(str,v,g);
	this->List.push_back(node);
}

void Buckets::insertPointAtList(string str,vector<int> &v,vector<int> &g)
{
	Node node(str,v,g);
	this->List.push_back(node);
}

void Buckets::printList()
{
	// cout <<this->List.size()<<std::endl;
	for (list<Node>::iterator it=List.begin();it!=this->List.end();it++)
		it->printPoints();
	// cout <<std::endl;
}

void Buckets::bucket_size()
{
	cout <<this->List.size()<<std::endl;
}