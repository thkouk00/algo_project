#include "../include/general_functions.h"

using namespace std;

//stores Dataset and QuerySet
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

void search_neighbors(HashTable **hashTables,std::vector<int> &r,char *query_file,int &L,int &k,int &w, int &num_of_buckets)
{
	int tmpfi;
	long double dist = 0;
	std::vector<int> neighbor; 
	std::vector<int> fi;
	std::vector<int> query;
	std::vector<int> tmpg; 
	std::vector<std::vector<int>> g;
	std::string line;
    std::ifstream myfile(query_file);
    while (std::getline(myfile, line))
    {
	    std::string stringvalues = line;
		std::istringstream iss (stringvalues);

		int val;
		iss >> val;
	
		while (!iss.eof())
		{
			query.push_back(val);
			iss >> val;
		}

		// create L*fi hashFunctions and L*g Functions for every query
		for (int i=0;i<L;i++)
		{
			find_hashFunction(tmpg, query, r, k, w, num_of_buckets, tmpfi);
			g.push_back(tmpg);
			fi.push_back(tmpfi);
			tmpg.erase(tmpg.begin(),tmpg.end());
		}

		// Range_search(hashTables);
		// ApproxNN_search(neighbor,hashTables,g,query,fi,L,k,dist);
		NN_search(neighbor,hashTables,g,query,fi,L,k,dist,1);

		cout <<std::endl<<"-------------------------------Start NN_Search----------------------------------------"<<std::endl;
		cout <<"Dist is "<<dist<< endl;
		cout <<"NEIGHBOR:"<<std::endl;
		for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
			cout <<*it<<" ";
		cout <<std::endl;
		cout <<"QUERY:"<<std::endl;
		for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
			cout <<*it<<" ";
		cout <<std::endl<<"--------------------------------End NN_Search----------------------------------------"<<std::endl;

		neighbor.erase(neighbor.begin(),neighbor.end());
		


		NN_search(neighbor,hashTables,g,query,fi,L,k,dist,0);
		cout <<std::endl<<"-------------------------------Start ApproxNN_Search----------------------------------------"<<std::endl;
		cout <<"Dist is "<<dist<< endl;
		cout <<"NEIGHBOR:"<<std::endl;
		for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
			cout <<*it<<" ";
		cout <<std::endl;
		cout <<"QUERY:"<<std::endl;
		for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
			cout <<*it<<" ";
		cout <<std::endl<<"--------------------------------End ApproxNN_Search----------------------------------------"<<std::endl;

		neighbor.erase(neighbor.begin(),neighbor.end());

		int R = 52;
		int c = 4; 
		Range_search(neighbor,hashTables,g,query,fi,L,k,R,c);
		// cout <<std::endl<<"-------------------------------Start Range_Search----------------------------------------"<<std::endl;
		// cout <<"Dist is "<<dist<< endl;
		// cout <<"NEIGHBOR:"<<std::endl;
		// for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
		// 	cout <<*it<<" ";
		// cout <<std::endl;
		// cout <<"QUERY:"<<std::endl;
		// for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
		// 	cout <<*it<<" ";
		// cout <<std::endl<<"--------------------------------End Range_Search----------------------------------------"<<std::endl;

		neighbor.erase(neighbor.begin(),neighbor.end());

		query.erase(query.begin(),query.end());
	}

}

int find_hashFunction(std::vector<int> &g, std::vector<int> &query, std::vector<int> &r, int &k, int &w, int &num_of_buckets, int &fi)
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
		//rerun generator in case of overflow
		while (1)
		{	
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,query.size());

			//random pick of t in [0,w) , double
			t = ((double)rand() / RAND_MAX) * w ;
			// double in_product = std::inner_product(row->begin(), row->end(), v.begin(), 0);
			double in_product = std::inner_product(v.begin(), v.end(), query.begin(), 0);
			//compute h(p)
			h = ((in_product+t)/w);
			// cout <<"h= "<<h<<std::endl;
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
		g.push_back(h);
		//empty vector to take new values
		v.erase(v.begin(),v.end());
	}
	//compute fi , num_of_buckets = tablesize/4
	fi = (std::inner_product(g.begin(), g.end(), r.begin(), 0)%M)%num_of_buckets;
	if (fi<0)
		fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%num_of_buckets);
	return fi;
}


// void search_neighbors(HashTable **hashTables,std::vector<int> &r,char *query_file,int &L,int &k,int &w, int &num_of_buckets)
// {
// 	int fi;
// 	int R;
// 	int count=0;
// 	std::string line;
//     std::ifstream myfile(query_file);
//     std::vector<int> g;
//     std::vector<int> query;
//     std::vector<int> neighbor;
//     long double db = 9999999.0;

//     cout <<"SEARCH NEIGHBORS"<<std::endl;
//     //for loop for every hashTable
//     while (std::getline(myfile, line))
//     {
// 	    std::string stringvalues = line;
// 		std::istringstream iss (stringvalues);

// 		int val;
// 		iss >> val;
	
// 		while (!iss.eof())
// 		{
// 			query.push_back(val);
// 			iss >> val;
// 		}
// 		// in case there is R at first line
// 		// if (count == 0)
// 		// {
// 		// 	R = val;
// 		// 	count++;
// 		// }
// 		// else
		
// 		for (int i=0;i<L;i++)
// 		{
// 			cout <<"Loop "<<i<<" neighbor is "<<std::endl;
// 			//bucket position
// 			fi = find_hashFunction(g,query,r,k,w,num_of_buckets);
// 			cout <<"FI is "<<fi<<std::endl;
// 			if (!hashTables[i]->bucket_exist(fi))
// 			{
// 				cout <<"NOT EXIST"<<std::endl;
// 				g.erase(g.begin(),g.end());
// 				continue;
// 			}
// 			hashTables[i]->Nearest_Neighbor(neighbor, db, query, g, fi,k,L);
			
// 			// cout <<"Size of neigh "<<neighbor.size()<<std::endl;
// 			// cout <<"NEIGHBOR:"<<std::endl;
// 			// for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
// 			// 	cout <<*it<<" ";
// 			// cout <<std::endl;
// 			// cout <<"QUERY:"<<std::endl;
// 			// for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
// 			// 	cout <<*it<<" ";
// 			// cout <<std::endl;
// 			// cout <<std::endl;
// 			// Range
// 			// NN	
// 			g.erase(g.begin(),g.end());
// 		}
// 		cout <<std::endl<<"-------------------------------Start----------------------------------------"<<std::endl;
// 		cout <<"NEIGHBOR:"<<std::endl;
// 		for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
// 			cout <<*it<<" ";
// 		cout <<std::endl;
// 		cout <<"QUERY:"<<std::endl;
// 		for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
// 			cout <<*it<<" ";
// 		cout <<std::endl<<"--------------------------------End----------------------------------------"<<std::endl;
		
// 		neighbor.erase(neighbor.begin(),neighbor.end());
// 		db = 9999999.0;
// 		// break;

// 		//empty vector for next query
// 		query.erase(query.begin(),query.end());
//     }
// }