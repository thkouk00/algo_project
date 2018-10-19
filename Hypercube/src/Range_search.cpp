#include "../include/Range_search.h"

using namespace std;


void Range_search(HashTable *cube, std::vector<int> &g, std::vector<int> &query, int &position, int &M, int &probes, int &k, double &R, bool Euclidean, std::ofstream &output)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<int> b;
	string pid;

	output <<"R-near neighbors:"<<std::endl;

	for (int i=0;i<L;i++)
	{
		// std::vector<int> tmpg(g[i]);
	
		if (!(cube->bucket_exist(tmpfi)))
			continue;
		Buckets* bucket = cube->access_bucket(position);
		if (bucket == (Buckets*)-1)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<tmpfi<<std::endl;
		int count_lines=0;
		int passed=0;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			std::vector<int> p(it->get_p());
			// check if gs are same
			// std::vector<int> pq(it->get_g());
			// if (g != pq)
			// 	continue;
			
			if (Euclidean)
				distance = Euclidean_Distance(query,p,k);
			else
				distance = Cosine_Similarity(query,p);
			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			
			if (distance < R)
			{
				passed++;
				output <<it->get_id()<<" -> distance "<<distance<<std::endl;
			}
			count_lines++;
		}
		output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	}

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
}