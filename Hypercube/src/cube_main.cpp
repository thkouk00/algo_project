#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <list>
#include <map>
#include "../include/general_functions.h"
#include "../include/HashTable.h"

using namespace std;

void Usage()
{
	cerr <<"./lsh -d <input file> –q <query file> –k <int> -L <int> -ο <output file>"<<endl;
}

int main(int argc, char const *argv[])
{
	//default values
	int k = 3;
	int w = 4;
	int M = 10;
	int probes = 2;

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
		else if (!strcmp(argv[i],"-probes"))
		{
			if (i+1 < argc)
			{
				probes = atoi(argv[i+1]);
				cout << "Probes: " << k << endl;
			}
			else
			{
				Usage();
				exit(1);
			}
		}
		else if (!strcmp(argv[i],"-M"))
		{
			if (i+1 < argc)
			{
				M = atoi(argv[i+1]);
				cout << "M: " << M << endl;
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
	
	// map values to {0,1}
	std::map<int,bool> mymap;
	std::map<int,bool>::iterator it;

	std::vector<std::string> id;
	std::vector<std::vector<int>> dataset;
	bool euclidean_flag = 1;
	double Radius = 0.0;
	int table_lines = 0;

	string str;
	if (!input_file)
	{
		cout <<"Give input file: ";
		cin >> str;
		input_file = (char *) malloc(str.length()+1);
		strcpy(input_file,str.c_str());
		cout <<str<<endl;
		cout <<input_file<<endl;
	}
	
	storeDataset(dataset, id,input_file, table_lines,euclidean_flag,Radius);
	int number_of_vertices = pow(2,k); 	
	cout <<"Table_lines "<<table_lines<<std::endl;
	cout <<"Radius "<<Radius<<std::endl;
	cout <<"Number of vertices "<<number_of_vertices<<std::endl;
	
	// hypercube structure to hold vertices
	HashTable *cube = new HashTable[number_of_vertices];
	cube->hashDataset(dataset, id, mymap, k, w);
	
	str.clear();
	if (!query_file)
	{
		cout <<"Give query file: ";
		cin >> str;
		query_file = (char *) malloc(str.length()+1);
		strcpy(query_file,str.c_str());
		cout <<str<<endl;
		cout <<query_file<<endl;
	}

	str.clear();
	if (!output_file)
	{
		cout <<"Give query file: ";
		cin >> str;
		output_file = (char *) malloc(str.length()+1);
		strcpy(output_file,str.c_str());
		cout <<str<<endl;
		cout <<output_file<<endl;
	}
	
	int queryset_lines = 0;
	std::vector<std::vector<int>> queryset;
	id.clear();
	storeDataset(queryset, id,query_file, queryset_lines,euclidean_flag,Radius);

	std::ofstream outputfile;
	outputfile.open (output_file, ios::out | ios::trunc);

	// search neighbors from query_file ***Euclidean Distance***
	search_neighbors(cube, id, queryset, M, probes,k, w, number_of_buckets, Radius,euclidean_flag, outputfile);









	
	delete[] cube;
	
	return 0;
}