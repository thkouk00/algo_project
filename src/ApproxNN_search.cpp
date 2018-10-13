#include "../include/ApproxNN_search.h"

using namespace std;


void ApproxNN_search(std::vector<int> &neighbor, HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, long double &dist)
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
		tmpg = g[i];
		if (!hashTables[i]->bucket_exist(tmpfi))
			continue;
		Buckets* bucket =  hashTables[i]->access_bucket(tmpfi);
		list<Node> List = bucket->access_list();
		for (std::list<Node>::iterator it = List.begin(); it!= List.end(); it++)
		{
			p = it->get_p();
			// if (tmpg != it->get_g())
			// 	continue;
			counter++;
			if (counter == 3*L)
			{
				cout <<"Trick used"<<std::endl;
				//trick , finish and right result to output
				neighbor = b;
				dist = db;
			}
			if ((distance = Euclidean_Distance(query,p,k)) < db)
			{
				b = p;
				db = distance;
			}
		}
		neighbor = b;
		dist = db;
		break;
	}
}