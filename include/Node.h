#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <vector>
#include <string>

class Node
{
	// id int or string
	std::string id;
	std::vector<int> v;

public:
	Node(std::string,std::vector<int>&);
	~Node(){};
	void printPoints();
	
};

#endif
