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
	cerr <<"./lsh -d <input file> –q <query file> –k <int> -L <int> -w <int> -ο <output file>"<<endl;
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
			cout <<argv[0]<<" -d <input file> –q <query file> –k <int> -L <int> -w <int> -ο <output file>"<<endl;
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
		else if (!strcmp(argv[i],"-w"))
		{
			if (i+1 < argc)
			{
				w = atoi(argv[i+1]);
				cout << "W: " << w << endl;
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

	while(1)
	{
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

		//construct lsh
		int hashTable_lines = 0;
		std::vector<std::string> id;
		std::vector<std::vector<int>> dataset;
		bool euclidean_flag = 1;
		double Radius=0;
		//store dataset in memory for faster and multiple times access 
		storeDataset(dataset, id,input_file, hashTable_lines,euclidean_flag,Radius);
		std::cout <<endl<< "Number of lines in input file: " << hashTable_lines<<std::endl;;
	    
	    //number of buckets in each hash Table
	    int number_of_buckets;
	    if (euclidean_flag)
			number_of_buckets = hashTable_lines/4;
		else
			number_of_buckets = pow(2,k);
		
	    //create L hash_tables
		HashTable **hashTables;	
		hashTables = new HashTable*[L];
		for (int i=0;i<L;i++)
		{
			hashTables[i] = new HashTable(number_of_buckets);
			if (euclidean_flag)
				hashTables[i]->hashDataset(dataset,id,k,w);
			else
				hashTables[i]->hashDataset(dataset,id,k);
		}
		
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

		int queryset_lines = 0;
		std::vector<std::vector<int>> queryset;
		
		id.erase(id.begin(),id.end());
		
		//store queryset in memory for faster and multiple times access 
		storeDataset(queryset, id,query_file, queryset_lines,euclidean_flag,Radius);
		cout <<"END QUERYSET STORE lines "<<queryset_lines<<std::endl;
		std::ofstream outputfile;
		outputfile.open (output_file, ios::out | ios::trunc);
		
		// outputfile <<"Euclidean Distance Results:"<<std::endl;
		// search neighbors from query_file ***Euclidean Distance***
		search_neighbors(hashTables, id, queryset, L, k, w, number_of_buckets, Radius,euclidean_flag, outputfile);
		
		string answer;
		cout <<"Do you want to rerun program? Y/N : ";
		cin >> answer;
		if (!answer.compare("Y") || !answer.compare("y"))
		{
			answer.clear();
			cout <<std::endl;
		}
		else
		{
			if (!answer.compare("N") || !answer.compare("n"))
				cout <<"Ending program"<<std::endl;
			else
				cout <<"Choice not found...Ending program"<<std::endl;	
			
			outputfile.close();
			//free memory
			for (int i=0;i<L;i++)
				delete hashTables[i];
			delete[] hashTables;

			free(input_file);
			free(query_file);
			free(output_file);
			break;	
		}

		outputfile.close();
		//free memory
		for (int i=0;i<L;i++)
			delete hashTables[i];
		delete[] hashTables;

		free(input_file);
		free(query_file);
		free(output_file);
		input_file = NULL;
		query_file = NULL;
		output_file = NULL;
		//ask user to rerun program or not 
	}
	
	return 0;
}
