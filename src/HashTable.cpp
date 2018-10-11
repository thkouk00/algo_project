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
		int num = rand() % 100000 + (-100000);
		r.push_back(num);
	}
	
	for (std::vector<int>::iterator t=r.begin();t!=r.end();t++)
		cout <<*t<<' ';
	cout <<std::endl;

	for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	{
		// for(vector<int>::iterator col = row->begin(); col != row->end(); ++col)
		// 	cout << *col<<' ';
		// cout <<endl;
		//must do this k times and put results in g
		for (int i=0;i<k;i++)
		// for (int i=0;i<1;i++)
		{	
			//rerun generator in case of overflow
			while (1)
			{	
				//vector v same size as current vector size for use in inner_product
				normal_distr_generator(v,row->size());
				// cout <<"V:"<<std::endl;
				// for (std::vector<double>::iterator it=v.begin();it!=v.end();it++)
				// 	cout <<*it<<' ';
				// cout <<std::endl;
				//random pick of t in [0,w) , double
				t = ((double)rand() / RAND_MAX) * w ;
				// double in_product = std::inner_product(row->begin(), row->end(), v.begin(), 0);
				double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
				double prod;
				cout <<"inner_product: "<<in_product<<std::endl;
				//compute h(p)
				h = ((in_product+t)/w);
				cout <<"h= "<<h<<std::endl;
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
		fi = (std::inner_product(g.begin(), g.end(), r.begin(), 0)%M)%this->num_of_buckets;
		cout <<"FI= "<<fi<<std::endl;
		cout <<"and "<<std::inner_product(r.begin(), r.end(), g.begin(), 0)<<std::endl;
		cout <<"    **********"<<std::endl;
		fi = abs(fi);
		cout <<"FI2= "<<fi<<std::endl;
		// if (fi<0)
			// fi = fi*(-1);
		//check for overflow
		while (!check_overflow(fi))
		{
			cout <<"**OVERFLOW**"<<std::endl;
			r.erase(r.begin(), r.end());
			for (int i=0;i<k;i++)
			{
				//rand between [0,100000) to avoid overflow again
				int num = rand() % 1000;
				r.push_back(num);
			}
			fi = ((std::inner_product(r.begin(), r.end(), g.begin(), 0))%M)%this->num_of_buckets;
			if (fi < 0)
				fi = abs(fi);
		}
		//insert point to hashTable at fi bucket
		this->insertPoint(fi, std::to_string(id), *row);
		g.erase(g.begin(), g.end());
		// for(vector<int>::iterator col = row->begin(); col != row->end(); ++col)
		// 	cout << *col<<' ';
		// cout <<"here"<<std::endl; 
		// break;
	}
}