#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <numeric>
#include <bits/stdc++.h>
#include <functional>

using namespace std;


// takes two args sourcefile , destfile
// for input change string to item_
// for query change string to query_
int main(int argc, char const *argv[])
{


	string input_file = argv[1];
	string output_file = argv[2];
	ifstream input(input_file);
	ofstream output;
	output.open (output_file, ios::out | ios::trunc);

	cout <<input_file<<std::endl;
	cout <<output_file<<std::endl;

	std::string line;
    std::ifstream myfile(input_file);
    // std::vector<int> tmpv;
    int counter=0;
    string str;
    while (std::getline(myfile, line))
    {
    	counter++;
		std::vector<int> tmpv;

		int val;
		// iss >> str;
		// cout <<"STR is "<<str<<std::endl;
		output <<"item_"<<counter<<' ';
		// output <<"query_"<<counter<<' ';
		// iss >> val;
		// while (!iss.eof())
		// {
		// 	output <<val<<' ';
		// 	// cout <<val<<' ';
		// 	// tmpv.push_back(val);
		// 	iss >> val;
		// }
		output <<line;
		output <<std::endl;
		//cout <<std::endl;
		// dataset.push_back(tmpv);
		// // cout <<"**********START INFO**********"<<std::endl;
		// // cout <<"Size dataset: "<<dataset.size()<<std::endl;
		// // cout <<"Size tmpv: "<<tmpv.size()<<" and line "<<hashTable_lines+1<<std::endl; 
		// // cout <<"**********END INFO**********"<<std::endl;
		// tmpv.erase(tmpv.begin(),tmpv.end());
		//       ++hashTable_lines;
    }
	return 0;
}