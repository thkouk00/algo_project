#include "../include/HashTable.h"

using namespace std;


HashTable::HashTable(int num): num_of_buckets(num)
{
	this->buckets = new Buckets*[this->num_of_buckets];
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

void HashTable::setVals(int num)
{
	this->num_of_buckets = num;
	for (int i=0;i<num_of_buckets;i++)
		this->buckets[i] = NULL;
}

void HashTable::insertPoint(int bucket_num,string id,vector<int> &v,std::vector<int> g)
{
	cout <<"INSERTPOINT ";
	for (std::vector<int>::iterator it=g.begin();it!=g.end();it++)
		cout <<*it<<' ';
	cout <<std::endl;
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

void HashTable::printAll()
{
	int counter=0;		
	for (int i=0;i<this->num_of_buckets;i++)
	{
		if (this->buckets[i])
		{
			counter += this->buckets[i]->bucket_size();
			cout <<"Bucket "<<i<<" is Active"<<std::endl;
		}
		else
		{
			cout <<"Bucket "<<i<<" *NOT* Active"<<std::endl;
			int flag = this->bucket_exist(i);
			cout <<"**FLAG IS "<<flag<<std::endl;
		}
	}
	cout <<"Total size is "<<counter<<std::endl;
}

bool HashTable::bucket_exist(int position)
{
	if (this->buckets[position] == NULL)
		return 0;
	else
		return 1;
}

Buckets* HashTable::access_bucket(int &position)
{
	if (this->buckets[position])
		return this->buckets[position];
	else
		return (Buckets*)-1;
}

// Euclidean Distance
void HashTable::hashDataset(std::vector<std::vector<int>> &dataset, std::vector<int> &r, std::vector<std::string> &id,int k, int w)
{
	//must find position of bucket first
	int counter=0;
	int fi;
	int h;
	double t;
	// string id;
	// string tmpstr = "item_";
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;
	int M = (int)(pow(2, 32)) - 5;

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 

	vector<string>::iterator id_iter;
	vector< vector<int> >::iterator row;
	for(id_iter=id.begin(),row = dataset.begin(); row != dataset.end(); ++row,id_iter++)
	{
		// unique id 
		counter++;
		// cout <<"-->COUNTER "<<counter<<"<--"<<std::endl;
		//must do this k times and put results in g
		for (int i=0;i<k;i++)
		{	
			//rerun generator in case of overflow
			while (1)
			{	
				//vector v same size as current vector size for use in inner_product
				normal_distr_generator(v,row->size());
				//random pick of t in [0,w) , double
				t = ((double)rand() / (RAND_MAX + 1.0)) * w ;
				// if (v.size() == 0)
				// 	cout <<"***************SIZE OF V == 0******************"<<std::endl;
				double in_product = std::inner_product(v.begin(), v.end(), row->begin(), 0);
				//compute h(p)
				cout <<"INPRODUCT "<<in_product<<std::endl;
				h = ((in_product+t)/w);
				cout <<"H IS "<<h<<std::endl;
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
		fi = ((std::inner_product(g.begin(), g.end(), r.begin(), 0))%M)%(this->num_of_buckets);
		// make fi positive if not
		if (fi<0)
			fi = (((std::inner_product(g.begin(), g.end(), r.begin(), 0) % M + M) % M)%(this->num_of_buckets));
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
		// id = tmpstr + std::to_string(counter);
		// cout <<id<<std::endl;
		this->insertPoint(fi, *id_iter, *row,g);
		g.erase(g.begin(), g.end());
	}
}

// Cosine Similarity
void HashTable::hashDataset(std::vector<std::vector<int>> &dataset, std::vector<std::string> &id, int k)
{
	int h;
	int counter = 0;
	std::vector<int> g;
	std::vector<double> v;
	// string tmpstr = "item_";
	// string id;

	std::vector<string>::iterator id_iter;
	vector< vector<int> >::iterator row;
	for(id_iter=id.begin(), row = dataset.begin(); row != dataset.end(); ++row,++id_iter)
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
		// id = tmpstr + std::to_string(counter);
		this->insertPoint(position, *id_iter, *row,g);
		g.erase(g.begin(), g.end());
	}
}