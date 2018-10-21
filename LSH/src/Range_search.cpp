#include "../include/Range_search.h"

using namespace std;


void Range_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, double &R, bool Euclidean, std::ofstream &output, double &TrueDist)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<int> b;
	string pid;

	output <<"R-near neighbors:"<<std::endl;

	clock_t begin = clock();
	for (int i=0;i<L;i++)
	{
		tmpfi = fi[i];
		std::vector<int> tmpg(g[i]);
	
		if (!(hashTables[i]->bucket_exist(tmpfi)))
		{
			// cout <<"*****MPIKA*****"<<std::endl;
			continue;
		}
		Buckets* bucket = hashTables[i]->access_bucket(tmpfi);
		if (bucket == NULL)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<tmpfi<<std::endl;
		int count_lines=0;
		int passed=0;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			bool g_flag = 1;
			std::vector<int> p(it->get_p());  
			
			if (Euclidean)
			{
				// find distance for trueNN_neighbor
				distance = Euclidean_Distance(query,p,k);
				std::vector<int> pq(it->get_g());
				// check if g(q) and q(p) are same for Range_search
				// if g's different flag = 0, else flag = 1
				if (tmpg != pq)
					g_flag = 0;
					// continue;
			}
			else
			{
				distance = Cosine_Similarity(query,p);
				g_flag = 1;
			}

			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			
			if (g_flag)
			{
				if (distance < R)
				{
					passed++;
					output <<it->get_id()<<" -> distance "<<distance<<std::endl;
				}
			}
			// test purposes
			count_lines++;
		}
		output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	}
	clock_t end = clock();
	double elapsed_time = (double)(end-begin)/CLOCKS_PER_SEC;

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
	output <<"tTrue: "<<elapsed_time<<std::endl;
	TrueDist = db;
}