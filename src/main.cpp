#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../include/HashTable.h"

using namespace std;

void Usage()
{
	cerr <<"./lsh -d <input file> –q <query file> –k <int> -L <int> -ο <output file>"<<endl;
}

int main(int argc, char const *argv[])
{
	//default values
	int k = 4;
	int L = 5;
	char * input_file = NULL;
	char *query_file = NULL;
	char *output_file = NULL;
	// read arguments from command line
	for (int i=0;i<argc;i++)
	{
		if (!strcmp(argv[i],"-h"))
		{
			cout <<argv[0]<<" -d <input file> –q <query file> –k <int> -L <int> -ο <output file>"<<endl;
			exit(1);
		}
		else if (!strcmp(argv[i],"-d"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				input_file = (char *) malloc(len+1);
				strcpy(input_file,argv[i+1]);
				input_file[len] = '\0';
				cout << "Input file: " << input_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-q"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				query_file = (char *) malloc(len+1);
				strcpy(query_file,argv[i+1]);
				query_file[len] = '\0';
				cout << "Query file: " << query_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-k"))
		{
			if (i+1 < argc)
			{
				k = atoi(argv[i+1]);
				cout << "K: " << k << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-L"))
		{
			if (i+1 < argc)
			{
				L = atoi(argv[i+1]);
				cout << "L: " << L << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-o"))
		{
			if (i+1 < argc)
			{
				int len = strlen(argv[i+1]);
				output_file = (char *) malloc(len+1);
				strcpy(output_file,argv[i+1]);
				output_file[len] = '\0';
				cout << "Output file: " << output_file << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
	}

	string str;
	if (!input_file)
	{
		cout <<"Give input file: ";
		cin >> str;
		input_file = (char *) malloc(str.length()+1);
		strcpy(input_file,str.c_str());
		cout <<str<<endl<<input_file<<endl;
	}

	//construct lsh
	std::vector<int> test;
	int hashTable_lines = 0;
    std::string line;
    std::ifstream myfile(input_file);
    while (std::getline(myfile, line))
    {
	    std::string stringvalues = line;
		std::istringstream iss (stringvalues);

		int val;
		iss >> val;
		iss >> val;
		// iss >> val;
		// cout <<val<<endl;
		// break;
        if (hashTable_lines == 9998)
        {	
        	cout <<stringvalues<<endl;
			while (!iss.eof())
			{
				cout <<"Inserting "<<val<<endl;
				test.push_back(val);
				// break;
				iss >> val;
				std::cout <<"EInai "<< val << ' ';
			}
		}
        ++hashTable_lines;
    }
    std::cout <<"Size "<<test.size()<<std::endl;
    // for (std::vector<int>::iterator it=test.begin();it!=test.end();it++ )
    // 	cout <<*it<<endl;


    std::cout <<endl<< "Number of lines in input file: " << hashTable_lines<<std::endl;;




    //create L hash_tables
    // HashTable **hashTables;	
    // hashTables = new HashTable*[L];
    // for (int i=0;i<L;i++)
    // 	hashTables[i] = new HashTable(hashTable_lines);
    
    // string in="kalimera";
    // //test vectors
    // std::vector<int> v1={1,1,1,1};
    // std::vector<int> v2={2,2,2,2};
    // std::vector<int> v3={3,3,3,3};
    // hashTables[1]->insertPoint(3, "43", v1);
    // hashTables[1]->insertPoint(3, in, v2);
    // in="kalinixta";
    // hashTables[1]->insertPoint(3, in, v3);

    // hashTables[1]->printBucket(3);
    // hashTables[1]->printBucket(5);

    // hashTables[4]->insertPoint(5, in, v2);
    // hashTables[4]->printBucket(5);
	

	// if (!query_file)
	// {
	// 	cout <<"Give query file: ";
	// 	cin >> str;
	// 	query_file = (char *) malloc(str.length()+1);
	// 	strcpy(query_file,str.c_str());
	// 	cout <<str<<endl<<query_file<<endl;
	// }
	// if (!output_file)
	// {
	// 	cout <<"Give output file: ";
	// 	cin >> str;
	// 	output_file = (char *) malloc(str.length()+1);
	// 	strcpy(output_file,str.c_str());
	// 	cout <<str<<endl<<output_file<<endl;
	// }

	//ask user to rerun program or not 



	//free memory
	// for (int i=0;i<L;i++)
	// 	delete hashTables[i];
	// delete[] hashTables;

	// free(input_file);
	// free(query_file);
	// free(output_file);
	return 0;
}