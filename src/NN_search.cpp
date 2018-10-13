#include "../include/NN_search.h"

using namespace std;


void NN_search(std::vector<int> &neighbor, HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, long double &dist, bool flag)
{
	int counter = 0;
	int tmpfi;
	long double distance;
	std::vector<int> tmpg;
	
	std::vector<int> p;
	std::vector<int> b;
	long double db = 9999999.0;
	// for every hashTable
	for (int i=0;i<L;i++)
	{
		tmpfi = fi[i];
		cout <<"TMPFI "<<tmpfi<<std::endl;
		tmpg = g[i];
		if (!hashTables[i]->bucket_exist(tmpfi))
		{
			cout <<"*****MPIKA BUCKET DONT EXIST*****"<<std::endl;
			continue;
		}
		cout <<"MPAINW BUCKET"<<std::endl;
		Buckets* bucket =  hashTables[i]->access_bucket(tmpfi);
		if (bucket == (Buckets*)-1)
			continue;
		list<Node> List = bucket->access_list();
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			p = it->get_p();

			// if (tmpg != it->get_g())
			// 	continue;
			
			//ApproxNN_search
			if (!flag)
			{
				counter++;
				if (counter == 3*L)
				{
					cout <<"Trick used"<<std::endl;
					//trick , finish and right result to output
					neighbor = b;
					dist = db;
					exit(1);
				}
			}
			
			if ((distance = Euclidean_Distance(query,p,k)) < db)
			{
				b = p;
				db = distance;
			}
		}
		if (!flag)
			break;
	}
	neighbor = b;
	dist = db;
	cout <<"Distance is "<<dist<<std::endl;
}