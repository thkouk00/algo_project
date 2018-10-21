#include "../include/NN_search.h"

using namespace std;

#include "../include/Range_search.h"

using namespace std;


void NN_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, bool Euclidean, std::ofstream &output, double &ApproxDist, double &averagetime)
{
	int tmpfi;
	long double distance;
	// std::vector<int> tmpg;
	// std::vector<int> p;

	std::vector<int> b;
	long double db = 9999999.0;
	string pid;

	output <<"ApproxNN neighbors:"<<std::endl;

	clock_t begin = clock();
	for (int i=0;i<L;i++)
	{
		tmpfi = fi[i];
		// cout <<"TMPFI "<<tmpfi<<std::endl;
		std::vector<int> tmpg(g[i]);
		// tmpg = g[i];
		if (!(hashTables[i]->bucket_exist(tmpfi)))
		// if (!hashTables[i]->bucket_exist(tmpfi))
		{
			cout <<"*****MPIKA*****"<<std::endl;
			continue;
		}
		Buckets* bucket = hashTables[i]->access_bucket(tmpfi);
		if (bucket == NULL)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<tmpfi<<std::endl;
		int count_lines=1;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
		
			std::vector<int> p(it->get_p());
			
			if (Euclidean)
			{
				// check if gs are same
				std::vector<int> pq(it->get_g());
				if (tmpg != pq)
					continue;
				distance = Euclidean_Distance(query,p,k);
			}
			else
				distance = Cosine_Similarity(query,p);
			// cout <<"Checking "<<it->get_id()<<" with distance "<<distance<<std::endl;
			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			
			//trick
			if (count_lines == 3*L)
			{
				cout <<"TRICK USED"<<std::endl;
				break;
			}
			count_lines++;	
		}
		// cout <<"** END HASHTABLE "<<i<<"** "<<std::endl;
	}
	clock_t end = clock();
	double elapsed_time = (double)(end-begin)/CLOCKS_PER_SEC;
	averagetime += elapsed_time;
	// cout <<"ApproxNN neighbor "<<pid<<" with distance "<<db<<std::endl;
	// output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	output <<"ApproxNN_SEARCH "<<pid<<std::endl;
	output <<"DISTANCE "<<db<<std::endl;
	ApproxDist = db;
	output <<"tLSH: "<<elapsed_time<<std::endl;
}