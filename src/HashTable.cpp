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

void HashTable::hashDataset(std::vector<std::vector<int>>& dataset, std::vector<int> &r, int k, int w)
{
	//must find position of bucket first
	int counter=0;
	int fi;
	int h;
	double t;
	std::vector<double> v;
	//holds all values from h
	std::vector<int> g;
	// std::vector<int> r;
	int M = (int)(pow(2, 32)) - 5;
		

	// use current time as seed for random generator
	std::srand(std::time(nullptr)); 
	
	//randomly pick k numbers for r , these values are same for every entry
	// for (int i=0;i<k;i++)
	// {
	// 	int num = rand() % 100000 + (-100000);
	// 	r.push_back(num);
	// }
	
	// for (std::vector<int>::iterator t=r.begin();t!=r.end();t++)
	// 	cout <<*t<<' ';
	// cout <<std::endl;

	for(vector< vector<int> >::iterator row = dataset.begin(); row != dataset.end(); ++row)
	{
		// unique id 
		counter++;
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
		this->insertPoint(fi, std::to_string(counter), *row,g);
		g.erase(g.begin(), g.end());
		// for(vector<int>::iterator col = row->begin(); col != row->end(); ++col)
		// 	cout << *col<<' ';
		// cout <<"here"<<std::endl; 
		// break;
	}
}

void HashTable::Nearest_Neighbor(std::vector<int> &b, long double &db,std::vector<int> &query, std::vector<int> &g, int &fi, int &k, int &L)
{
	int counter=0;
	long double dist=0;
	// std::vector<int> b;
	// long double db = 9999999.0;
	// this->buckets[fi]->bucket_size();
	cout <<"Nearest Neighbor print for fi  "<<fi<<std::endl;
	if (this->buckets[fi])
	{
		cout <<"MPIKa"<<std::endl;
		for (list<Node>::iterator it=this->buckets[fi]->List.begin();it!=this->buckets[fi]->List.end();it++)
		{
			// cout <<"Compare g "<<std::endl;
			// if (g != it->get_g())
			// 	continue;
			// cout <<"Idia g"<<std::endl;

			// trick
			counter++;
			if (counter > 3*L)
			{
				cout <<"Trick with dist "<<dist<<std::endl;
				exit(1);
				// return b;
			}
			
			dist = this->Euclidean_Distance(query,it->get_p(),k);
			cout <<"Dist is "<<dist<<std::endl;
			if (dist < db)
			{
				cout <<"Changing d from "<<db<<" to "<<dist<<std::endl;
				b = it->get_p();
				db = dist;
			}
		}
		cout <<"Min dist is "<<db<<std::endl;
		// return b;
	}
}

void HashTable::Range_Neighbor(std::vector<int> &query, std::vector<int> &g, int &fi)
{

}	


long double HashTable::Euclidean_Distance(const std::vector<int> & v1,const std::vector<int> &v2,int &k)
{
 	long double sum = 0;
 	for(unsigned int i = 0;i<v1.size();i++){
 		sum += pow((v1[i] - v2[i]),k);
 	}
 	return pow(sum,1.0/k);
};

// template <typename T>
// long double HashTable::Euclidean_Distance(const std::vector<T> & v1,const std::vector<T> &v2,int &k)
// {
//  	long double sum = 0;
//  	for(unsigned int i = 0;i<v1.size();i++){
//  		sum += pow((v1[i] - v2[i]),k);
//  	}
//  	return pow(sum,1.0/k);
// };