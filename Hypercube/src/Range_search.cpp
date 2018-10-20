#include "../include/Range_search.h"

using namespace std;


void Range_search(HashTable *cube, std::vector<int> &g, std::vector<int> &query, int &position, int &M, int &probes, int &k, double &R, bool Euclidean, std::ofstream &output, double &TrueDist)
{
	int tmpfi;
	long double distance;
	long double db = 9999999.0;
	std::vector<int> b;
	string pid;

	output <<"R-near neighbors:"<<std::endl;
	
	bitset<32> hamming_distance;
	// initial hamming distance
	int h_dist = 1;
	bool neighbor_flag = 0;

	clock_t begin = clock();
	// must find way to calculate next vertex
	for (int i=0;i<probes;i++)
	{
		if (i != 0)
		{
			int y;
			int tmp_pos;
			while (!neighbor_flag)
			{
				bitset<32> current_vertex(position);
				for (y=0;y<cube->get_num_of_buckets();y++)
				{
					if (y == position)
						continue;
					bitset<32> neighbor(y);
					hamming_distance = current_vertex ^ neighbor;
					// find new bucket position
					if (hamming_distance.count() == h_dist)
					{
						tmp_pos = (int)(neighbor.to_ulong());
						
						if (!(cube->bucket_exist(tmp_pos)))
							continue;
						
						position = tmp_pos;
						neighbor_flag = 1;
						break;
					}
				}
				// if no neighbor with hamming distance h_dist , search for h_dist+1
				if (y == cube->get_num_of_buckets() && !neighbor_flag)
					h_dist++;
			}
		}
		if (!(cube->bucket_exist(position)))
			continue;
		Buckets* bucket = cube->access_bucket(position);
		if (bucket == NULL)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<position<<std::endl;
		int count_lines=0;
		int passed=0;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			std::vector<int> p(it->get_p());
			
			if (Euclidean)
			{
				// check if gs are same
				std::vector<int> pq(it->get_g());
				if (g != pq)
					continue;

				distance = Euclidean_Distance(query,p,k);
			}
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
	clock_t end = clock();
	double elapsed_time = (double)(end-begin)/CLOCKS_PER_SEC;

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
	output <<"tTrue: "<<elapsed_time<<std::endl;
	TrueDist = db;
}