#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <string>

class Node
{
	// id int or string
	std::string id;
	std::vector<int> &p;
	std::vector<int> g;

public:
	Node(std::string,std::vector<int>&,std::vector<int>);
	~Node(){};
	void printPoints();
	std::vector<int> get_p();
	std::vector<int> get_g();
	
};

#endif
