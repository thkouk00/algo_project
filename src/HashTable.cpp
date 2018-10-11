#include "../include/HashTable.h"

using namespace std;


HashTable::HashTable(int num): num_of_buckets(num)
{
	this->buckets = new Buckets*[num_of_buckets];
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
}

HashTable::~HashTable()
{
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
			delete this->buckets[i];
	}
	delete[] this->buckets;
}

void HashTable::insertPoint(int bucket_num,string id,vector<int> &v)
{
	if (!this->buckets[bucket_num])
		this->buckets[bucket_num] = new Buckets(id,v);
	else
		this->buckets[bucket_num]->insertPointAtList(id,v);
}

void HashTable::printBucket(int bucket_num)
{
	if (this->buckets[bucket_num])
		this->buckets[bucket_num]->printList();
	else
		cout <<"Bucket not initialized"<<std::endl;
}

void HashTable::hashDataset(std::vector<std::vector<int>>& dataset,int k,int w,int id)
{
	//must find position of bucket first
	int fi;
	int h;
	double t;
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;
	std::vector<int> r;
	int M = (int)(pow(2, 32)) - 5;
		

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 
	
	//randomly pick k numbers for r , these values are same for every entry
	for (int i=0;i<k;i++)
	{
		int num = rand() % INT_MAX + (INT_MIN + 1234567);
		r.push_back(num);
	}

	for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	{
		//must do this k times and put results in g
		for (int i=0;i<k;i++)
		{	
			//rerun generator in case of overflow
			while (1)
			{	
				//vector v same size as current vector size for use in inner_product
				normal_distr_generator(v,row->size());
				//random pick of t in [0,w)
				t = rand() % w;
				int in_product = std::inner_product(row->begin(), row->end(), v.begin(), 0);

				//compute h(p)
				h = floor((in_product+t)/w);
				//no overflow
				if (check_overflow(h))
					break;
				else
					//empty vector to take new values
					v.erase(v.begin(),v.end());
			}
			g.push_back(h);
			//empty vector to take new values
			v.erase(v.begin(),v.end());
		}

		//compute fi , num_of_buckets = tablesize/4
		fi = (std::inner_product(r.begin(), r.end(), g.begin(), 0)%M)%this->num_of_buckets;
		//check for overflow
		while (!check_overflow(fi))
		{
			r.erase(r.begin(), r.end());
			for (int i=0;i<k;i++)
			{
				//rand between [0,100000) to avoid overflow again
				int num = rand() % 100000;
				r.push_back(num);
			}
			fi = (std::inner_product(r.begin(), r.end(), g.begin(), 0)%M)%this->num_of_buckets;
			if (fi < 0)
				fi = abs(fi);
		}
		//insert point to hashTable at fi bucket
		this->insertPoint(fi, std::to_string(id), *row);
		
		// for(vector<int>::iterator col = row->begin(); col != row->end(); ++col)
		// 	cout << *col<<' ';
		// cout <<std::endl; 
	}
}