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

void HashTable::insertPoint(int bucket_num,string id,vector<int> &v,std::vector<int> &g)
{
	if (!this->buckets[bucket_num])
		this->buckets[bucket_num] = new Buckets(id,v,g);
	else
		this->buckets[bucket_num]->insertPointAtList(id,v,g);
}

void HashTable::printBucket(int bucket_num)
{
	if (this->buckets[bucket_num])
		this->buckets[bucket_num]->printList();
	else
		cout <<"Bucket not initialized"<<std::endl;
}

int HashTable::bucket_exist(int &fi)
{
	if (this->buckets[fi])
		return 1;
	else
		return -1;
}

Buckets* HashTable::access_bucket(int &position)
{
	if (this->buckets[position])
		return this->buckets[position];
	else
		return (Buckets*)-1;
}

// Euclidean Distance
void HashTable::hashDataset(std::vector<std::vector<int>> &dataset, std::vector<int> &r, int k, int w)
{
	//must find position of bucket first
	int counter=0;
	int fi;
	int h;
	double t;
	string id;
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;
	int M = (int)(pow(2, 32)) - 5;
		

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 

	for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	{
		// unique id 
		counter++;
		//must do this k times and put results in g
		for (int i=0;i<k;i++)
		{	
			//rerun generator in case of overflow
			while (1)
			{	
				//vector v same size as current vector size for use in inner_product
				normal_distr_generator(v,row->size());
				//random pick of t in [0,w) , double
				t = ((double)rand() / RAND_MAX) * w ;
				double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
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
			g.push_back(h);
			//empty vector to take new values
			v.erase(v.begin(),v.end());
		}

		//compute fi , num_of_buckets = tablesize/4
		fi = (std::inner_product(g.begin(), g.end(), r.begin(), 0)%M)%this->num_of_buckets;
		// fi = abs(fi);
		// make fi positive if not
		if (fi<0)
			fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%this->num_of_buckets);
		// cout <<"FI= "<<fi<<std::endl;
		// check for overflow
		// while (!check_overflow(fi))
		// {
		// 	cout <<"**OVERFLOW**"<<std::endl;
		// 	r.erase(r.begin(), r.end());
		// 	for (int i=0;i<k;i++)
		// 	{
		// 		//rand between [0,100000) to avoid overflow again
		// 		int num = rand() % 1000;
		// 		r.push_back(num);
		// 	}
		// 	fi = ((std::inner_product(r.begin(), r.end(), g.begin(), 0))%M)%this->num_of_buckets;
		// 	if (fi < 0)
		// 		fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%this->num_of_buckets);
		// }
		//insert id and point to hashTable at fi bucket
		id = "item_" + std::to_string(counter);
		this->insertPoint(fi, id, *row,g);
		g.erase(g.begin(), g.end());
	}
}

// Cosine Similarity
void HashTable::hashDataset(std::vector<std::vector<int>> &dataset, int k)
{
	int h;
	int counter = 0;
	std::vector<int> g;
	std::vector<double> v;
	string id;

	for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	{
		counter++;
		for (int i=0;i<k;i++)
		{		
			//vector v same size as current vector size for use in inner_product
			normal_distr_generator(v,row->size());
			//random pick of t in [0,w) , double
			// t = ((double)rand() / RAND_MAX) * w ;
			double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
			//compute h(p)
			if (in_product>=0)
				h = 1;
			else
				h = 0;

			g.push_back(h);
			//empty vector to take new values
			v.erase(v.begin(),v.end());
		}
		long int position = binarytodecimal(g);
		id = "item_" + std::to_string(counter);
		this->insertPoint(position, id, *row,g);
		g.erase(g.begin(), g.end());
	}
}