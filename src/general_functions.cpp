#include "../include/general_functions.h"

void storeDataset(std::vector<std::vector<int>>& dataset,char *input_file,int &hashTable_lines)
{
	// int hashTable_lines = 0;
    std::string line;
    std::ifstream myfile(input_file);
    std::vector<int> tmpv;
    while (std::getline(myfile, line))
    {
	    std::string stringvalues = line;
		std::istringstream iss (stringvalues);

		int val;
		iss >> val;
		while (!iss.eof())
		{
			tmpv.push_back(val);
			iss >> val;
		}
		dataset.push_back(tmpv);
		tmpv.erase(tmpv.begin(),tmpv.end());
        ++hashTable_lines;
    }
}