#include "../include/Node.h"
using namespace std;

Node::Node(string str,vector<int> &v,std::vector<int> g):id(str),p(v),g(g)
{
	// cout <<"INSERTPOINTNODE ";
	// for (std::vector<int>::iterator it=g.begin();it!=g.end();it++)
	// 	cout <<*it<<' ';
	// cout <<std::endl;
	
}

void Node::printPoints()
{
	cout <<"Id: "<<this->id<<std::endl;
	for (vector<int>::iterator it=p.begin();it!=p.end();it++)
		cout <<*it<<" ";
	cout <<endl;
}

std::vector<int>& Node::get_p()
{
	return this->p;
}

std::vector<int> Node::get_g()
{
	return this->g;
}

std::string Node::get_id()
{
	return this->id;
}