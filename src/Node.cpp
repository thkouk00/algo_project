#include "../include/Node.h"
using namespace std;

Node::Node(string str,vector<int> &v):id(str)
{
	this->v = v;
}

void Node::printPoints()
{
	cout <<"Id: "<<this->id<<std::endl;
	for (vector<int>::iterator it=v.begin();it!=v.end();it++)
		cout <<*it<<" ";
	cout <<endl;
}