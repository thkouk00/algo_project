#include "../include/Node.h"
using namespace std;

Node::Node(string str,vector<int> &v,std::vector<int> g):id(str),p(v)
{
	this->g = g;
}

void Node::printPoints()
{
	cout <<"Id: "<<this->id<<std::endl;
	for (vector<int>::iterator it=p.begin();it!=p.end();it++)
		cout <<*it<<" ";
	cout <<endl;
}