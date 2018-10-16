#include "../include/general_functions.h"

using namespace std;

//stores Dataset and QuerySet
void storeDataset(std::vector<std::vector<int>> &dataset, std::vector<std::string> &id,char *input_file,int &hashTable_lines, bool &euclidean_flag, double &Radius)
{
    std::string line;
    std::ifstream myfile(input_file);
    // std::vector<int> tmpv;
	while (std::getline(myfile, line))
	{
		string str, tmpstr;
		std::vector<int> tmpv;
		std::istringstream iss (line);

		int val;
		double num;
		iss >> str;
		// cout <<"ID-> "<<str<<std::endl;
		if (hashTable_lines == 0)
		{
			// cout <<"MPAINW GIA CJECK "<<str<<std::endl;
			tmpstr = str;
			// if (iss.eof())
			// {
				if ( !str.compare("Euclidean") || !str.compare("euclidean") )
					euclidean_flag = 1;
				else if ( !str.compare("Cosine") || !str.compare("cosine") )
					euclidean_flag = 0;
				else if (!str.compare("Radius:") || !str.compare("radius:") )
				{
					cout <<str<<std::endl;
					// double num;
					iss >> Radius;
					cout <<"Radius "<<Radius<<std::endl;
					// Radius = num;
					// continue;
				}
				else
				{
					// default metric -> euclidean
					euclidean_flag = 1;
					cout <<"3rd choice Euclidean"<<std::endl;
				}

				hashTable_lines++;
				continue;
			// }
		}
		id.push_back(str);
		
		// cout <<"ID-> "<<str<<std::endl;
		//first element
		iss >> val;
		while (!iss.eof())
		{
			tmpv.push_back(val);	
			iss >> val;
		}
		dataset.push_back(tmpv);
		// // cout <<"**********START INFO**********"<<std::endl;
		// // cout <<"Size dataset: "<<dataset.size()<<std::endl;
		// // cout <<"Size tmpv: "<<tmpv.size()<<" and line "<<hashTable_lines+1<<std::endl; 
		// // cout <<"**********END INFO**********"<<std::endl;
		tmpv.erase(tmpv.begin(),tmpv.end());	
		++hashTable_lines;
	}
	// myfile.close();
}

void search_neighbors(HashTable **hashTables,std::vector<std::string> &id,std::vector<int> &r,std::vector<std::vector<int>> &queryset,int &L,int &k,int &w, int &num_of_buckets, bool Cosine,std::ofstream &output)
{
	int counter=0;
	string str = "item_";
	int tmpfi;
	// long double dist = 0;
	// std::vector<int> neighbor; 
	std::vector<int> fi;
	std::vector<int> query;
	std::vector<int> tmpg; 
	std::vector<std::vector<int>> g;
	// string id;
	string id_query;  

	std::vector<string>::iterator id_iter;
	std::vector<std::vector<int>>::iterator it;	
	for (id_iter=id.begin(), it=queryset.begin();it!=queryset.end();it++, id_iter++)
    {
    	counter++;
    	// if (counter == 2)
    	// 	break;
    	// std::vector<int> neighbor; 
    	query = *it;
		// create L*fi hashFunctions and L*g Functions for every query
		for (int i=0;i<L;i++)
		{
			// std::vector<int> tmpg; 
			find_hashFunction(tmpg, query, r, k, w, num_of_buckets, tmpfi,Cosine);
			g.push_back(tmpg);
			fi.push_back(tmpfi);
			cout <<"TMPG-FINDHASH "<<std::endl;
			for (std::vector<int>::iterator g_iter=tmpg.begin();g_iter!=tmpg.end();g_iter++)
				cout <<*g_iter<<' ';
			cout <<std::endl;
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
	

		// if (!Cosine)
		// {
		// 	// output <<std::endl<<"-------------------------------Start NN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"-------------------------------Start NN_Search----------------------------------------"<<std::endl;
		// }
		// else
		// {
		// 	// output <<std::endl<<"-------------------------------Start Cosine NN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"-------------------------------Start Cosine NN_Search----------------------------------------"<<std::endl;
		// }
		// // output <<"Dist is "<<dist<< endl;
		// // output <<"NEIGHBOR:"<<id<<std::endl;
		// cout <<"Dist is "<<dist<< endl;
		// cout <<"NEIGHBOR:"<<std::endl;
		// for (std::vector<int>::iterator iter = neighbor.begin(); iter!= neighbor.end(); iter++)
		// 	cout <<*iter<<" ";
		// cout <<std::endl;
		// cout <<"QUERY:"<<std::endl;
		// for (std::vector<int>::iterator iter = query.begin(); iter!= query.end(); iter++)
		// 	cout <<*iter<<" ";
		// if (!Cosine)
		// {
		// 	// output <<std::endl<<"--------------------------------End NN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"--------------------------------End NN_Search----------------------------------------"<<std::endl;
		// }
		// else
		// {
		// 	// output <<std::endl<<"--------------------------------End Cosine NN_Search----------------------------------------"<<std::endl; 
		// 	cout <<std::endl<<"--------------------------------End Cosine NN_Search----------------------------------------"<<std::endl;
		// }

		// neighbor.erase(neighbor.begin(),neighbor.end());
		
		long double dist = 0;
		string id;
		double R;
		int c;
		if (!Cosine)
		{
			R = 52;
			c = 4;	
		}
		else
		{
			R = 0.5;
			c = 1;
		}	 
		// //ApproxNN_search
		NN_search(hashTables,g,query,fi,L,k,R,c,Cosine,output);
		// NN_search(neighbor,hashTables,g,query,fi,L,k,dist,id,Cosine,output);
		// output <<"Approximate Nearest neighbor: "<<id<<std::endl;
		// output <<"distanceLSH: "<<dist<<std::endl;


		// if (!Cosine)
		// {
		// 	// output <<std::endl<<"-------------------------------Start ApproxNN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"-------------------------------Start ApproxNN_Search----------------------------------------"<<std::endl;
		// }
		// else
		// {
		// 	// output <<std::endl<<"-------------------------------Start Cosine ApproxNN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"-------------------------------Start Cosine ApproxNN_Search----------------------------------------"<<std::endl;
		// }
		// // output <<"Dist is "<<dist<< endl;
		// // output <<"NEIGHBOR:"<<std::endl;
		// cout <<"Dist is "<<dist<< endl;
		// cout <<"NEIGHBOR:"<<std::endl;
		// for (std::vector<int>::iterator iter = neighbor.begin(); iter!= neighbor.end(); iter++)
		// 	cout <<*iter<<" ";
		// cout <<std::endl;
		// cout <<"QUERY:"<<std::endl;
		// for (std::vector<int>::iterator iter = query.begin(); iter!= query.end(); iter++)
		// 	cout <<*iter<<" ";
		// if (!Cosine)
		// {
		// 	// output <<std::endl<<"--------------------------------End ApproxNN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"--------------------------------End ApproxNN_Search----------------------------------------"<<std::endl;
		// }
		// else
		// {
		// 	// output <<std::endl<<"--------------------------------End Cosine ApproxNN_Search----------------------------------------"<<std::endl;
		// 	cout <<std::endl<<"--------------------------------End Cosine ApproxNN_Search----------------------------------------"<<std::endl;
		// }

		// neighbor.erase(neighbor.begin(),neighbor.end());

		// double R;
		// int c;
		if (!Cosine)
		{
			R = 52;
			c = 4;	
		}
		else
		{
			R = 0.5;
			c = 1;
		}	 
		Range_search(hashTables,g,query,fi,L,k,R,c,Cosine,output);
		// cout <<std::endl<<"-------------------------------Start Range_Search----------------------------------------"<<std::endl;
		// cout <<"Dist is "<<dist<< endl;
		// cout <<"NEIGHBOR:"<<std::endl;
		// for (std::vector<int>::iterator it = neighbor.begin(); it!= neighbor.end(); it++)
		// 	cout <<*it<<" ";
		// cout <<std::endl;
		// output <<"True Nearest neighbor: "<<id<<std::endl;
		// output <<"distanceTrue: "<<dist<<std::endl;
		// cout <<"QUERY:"<<std::endl;
		// for (std::vector<int>::iterator it = query.begin(); it!= query.end(); it++)
		// 	cout <<*it<<" ";
		// cout <<std::endl<<"--------------------------------End Range_Search----------------------------------------"<<std::endl;

		
		// neighbor.erase(neighbor.begin(),neighbor.end());
		query.erase(query.begin(),query.end());
		g.erase(g.begin(),g.end());
		fi.erase(fi.begin(),fi.end());
	}

}

int find_hashFunction(std::vector<int> &g, std::vector<int> &query, std::vector<int> &r, int &k, int &w, int &num_of_buckets, int &fi, bool Cosine)
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
			
			if (!Cosine)
			{
				//random pick of t in [0,w) , double
				t = ((double)rand() / (RAND_MAX + 1.0)) * w ;
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
	if (!Cosine)
	{
		//compute fi , num_of_buckets = tablesize/4
		fi = (std::inner_product(g.begin(), g.end(), r.begin(), 0)%M)%num_of_buckets;
		if (fi<0)
			fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%num_of_buckets);

	}
	else
		fi = binarytodecimal(g);
	// cout <<"FI "<<fi<<std::endl;
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