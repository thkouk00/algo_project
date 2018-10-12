#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "../include/HashTable.h"
#include "../include/general_functions.h"

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
	int w = 4;
	char *input_file = NULL;
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
	// std::vector<int> test;
	int hashTable_lines = 0;
	std::vector<std::vector<int>> dataset;
	//store dataset in memory for faster access 
	storeDataset(dataset, input_file, hashTable_lines);
	std::cout <<endl<< "Number of lines in input file: " << hashTable_lines<<std::endl;;

	cout <<"Ready to print"<<endl;

	//print all elements of vector of vectors
	// int count = 0;
	// for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	// {
	// 	count++;
	// 	if (count != 5000)
	// 		continue;
	// 	for(vector<int>::iterator col = row->begin(); col != row->end(); ++col)
	// 		cout << *col<<' ';
	// 	cout <<std::endl; 
	// }
    
    //number of buckets in each hash Table
	int number_of_buckets = hashTable_lines/4;

    //create L hash_tables
    HashTable **hashTables;	
    hashTables = new HashTable*[L];
    for (int i=0;i<L;i++)
    // for (int i=0;i<1;i++)
    {
    	hashTables[i] = new HashTable(number_of_buckets);
    	hashTables[i]->hashDataset(dataset, k,w);
    }
    
    // cout <<"H2:"<<std::endl;
    // for (int i =0;i<number_of_buckets;i++)
    // 	hashTables[1]->printBucket(i);
    // cout <<"H4:"<<std::endl;
    // hashTables[3]->printBucket(523);
	
	// ask user for query file and output file
	if (!query_file)
	{
		cout <<"Give query file: ";
		cin >> str;
		query_file = (char *) malloc(str.length()+1);
		strcpy(query_file,str.c_str());
		cout <<str<<endl<<query_file<<endl;
	}
	if (!output_file)
	{
		cout <<"Give output file: ";
		cin >> str;
		output_file = (char *) malloc(str.length()+1);
		strcpy(output_file,str.c_str());
		cout <<str<<endl<<output_file<<endl;
	}

	//search in query


	//ask user to rerun program or not 

	//free memory
	for (int i=0;i<L;i++)
		delete hashTables[i];
	delete[] hashTables;

	free(input_file);
	free(query_file);
	free(output_file);
	return 0;
}