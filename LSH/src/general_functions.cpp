#include "../include/general_functions.h"

using namespace std;

//stores Dataset and QuerySet
void storeDataset(std::vector<std::vector<int>> &dataset, std::vector<std::string> &id,char *input_file,int &hashTable_lines, bool &euclidean_flag, double &Radius)
{
    std::string line;
    std::ifstream myfile(input_file);
    int count_lines = 0;
   
	while (std::getline(myfile, line))
	{
		string str;
		std::vector<int> tmpv;
		std::istringstream iss (line);

		int val;
		double num;
		iss >> str;
		if (count_lines == 0)
		{
			
			
			if ( !str.compare("Euclidean") || !str.compare("euclidean") )
			{
				euclidean_flag = 1;
				count_lines++;
				continue;
			}	
			else if ( !str.compare("Cosine") || !str.compare("cosine") )
			{
				euclidean_flag = 0;
				count_lines++;
				continue;
			}
			else if (!str.compare("Radius:") || !str.compare("radius:") )
			{
				// cout <<str<<std::endl;
				
				iss >> Radius;
				cout <<"Radius "<<Radius<<std::endl;
				count_lines++;
				continue;
			}
			else
			{
				// default metric -> euclidean
				euclidean_flag = 1;
				cout <<"3rd choice Euclidean"<<std::endl;
				count_lines++;
				// hashTable_lines++;
			}
		}
		id.push_back(str);
		
		//first element
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

void search_neighbors(HashTable **hashTables,std::vector<std::string> &id,std::vector<std::vector<int>> &queryset,int &L,int &k,int &w, int &num_of_buckets, double &Radius,bool Euclidean,std::ofstream &output)
{
	int counter=0;
	int tmpfi;
	double maxfraction = 0;
	double ApproxDist = 0;
	double TrueDist = 0;
	double averageApproxtime = 0;
	std::vector<int> fi;
	std::vector<int> query;
	std::vector<int> tmpg; 
	std::vector<std::vector<int>> g;
	string id_query;  

	std::vector<string>::iterator id_iter;
	std::vector<std::vector<int>>::iterator it;	
	for (id_iter=id.begin(), it=queryset.begin();it!=queryset.end();it++, id_iter++)
    {
    	counter++;
    	 
    	query = *it;
		// create L*fi hashFunctions and L*g Functions for every query
		for (int i=0;i<L;i++)
		{
			// std::vector<int> tmpg; 
			find_hashFunction(tmpg, query, k, w, num_of_buckets, tmpfi,Euclidean);
			g.push_back(tmpg);
			fi.push_back(tmpfi);
			// cout <<"TMPG-FINDHASH "<<std::endl;
			// for (std::vector<int>::iterator g_iter=tmpg.begin();g_iter!=tmpg.end();g_iter++)
			// 	cout <<*g_iter<<' ';
			// cout <<std::endl;
			tmpg.erase(tmpg.begin(),tmpg.end());
		}

		//NN_search
		// NN_search(neighbor,hashTables,g,query,fi,L,k,dist,id,1,Cosine);
		
		// id_query = str+ std::to_string(counter);
		output <<std::endl<<"******************************************************************************************************************"<<std::endl;
		// output <<"Query: "<<id_query<<std::endl;
		output <<"Query: "<<*id_iter<<std::endl;
		// output <<"True Nearest neighbor: "<<id<<std::endl;
		// output <<"distanceTrue: "<<dist<<std::endl;
		
		long double dist = 0;
		string id;
		
		Range_search(hashTables,g,query,fi,L,k,Radius,Euclidean,output,TrueDist);
		
		if (Radius != 0)
		{
			//ApproxNN_search
			NN_search(hashTables,g,query,fi,L,k,Euclidean,output,ApproxDist,averageApproxtime);
			if (ApproxDist != 9999999.0 && TrueDist != 9999999.0 && TrueDist != 0)
			{
				double tmpfraction = ApproxDist/TrueDist; 
				if (tmpfraction > maxfraction)
				{
					cout <<"BEFORE FR: "<<maxfraction<<" AFTER FR: "<<tmpfraction<<std::endl;
					maxfraction = tmpfraction;
				}
			}
			
		}
		// output <<"Approximate Nearest neighbor: "<<id<<std::endl;
		// output <<"distanceLSH: "<<dist<<std::endl;

		
		query.erase(query.begin(),query.end());
		g.erase(g.begin(),g.end());
		fi.erase(fi.begin(),fi.end());
	}
	output <<"Max fraction: "<<maxfraction<<std::endl;
	output <<"Average Time of ApproxSearch: "<<averageApproxtime/(queryset.size())<<std::endl;
	output <<"SIZE IS "<<queryset.size()<<std::endl;
}

int find_hashFunction(std::vector<int> &g, std::vector<int> &query, int &k, int &w, int &num_of_buckets, int &fi, bool Euclidean)
{
	int counter=0;
	// int fi;
	int h;
	double t;
	std::vector<double> v;
	//holds all values from h
	// std::vector<int> g;
	// std::vector<int> r;
	int M = (int)(pow(2, 32)) - 5;
	for (int i=0;i<k;i++)
	{
		// std::vector<double> v;
		//rerun generator in case of overflow
		while (1)
		{	
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,query.size());

			// double in_product = std::inner_product(row->begin(), row->end(), v.begin(), 0);
			double in_product = std::inner_product(v.begin(), v.end(), query.begin(), 0);
			
			if (Euclidean)
			{
				//random pick of t in [0,w) , double
				t = ((double)rand() / (RAND_MAX + 1.0)) * w ;
				//compute h(p)
				h = ((in_product+t)/w);
				//no overflow
				if (!check_overflow(h))
				{	
					//empty vector to take new values
					v.erase(v.begin(),v.end());
					cout <<"**OVERFLOW***"<<std::endl;
				}
				else
					break;
			}
			else
			{
				if (in_product >= 0)
					h = 1;
				else
					h = 0;
				break;
			}
		}
		g.push_back(h);
		//empty vector to take new values
		v.erase(v.begin(),v.end());
	}
	if (Euclidean)
	{
		std::hash<std::string> hash_fn;
		string hashstr;
		for (std::vector<int>::iterator it=g.begin();it!=g.end();it++)
			hashstr += to_string(*it);

		fi = hash_fn(hashstr) % num_of_buckets;
		// //compute fi , num_of_buckets = tablesize/4
		// fi = (std::inner_product(g.begin(), g.end(), r.begin(), 0)%M)%num_of_buckets;
		// if (fi<0)
		// 	fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%num_of_buckets);

	}
	else
		fi = binarytodecimal(g);
	
	return fi;
}