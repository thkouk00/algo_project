#include "../include/NN_search.h"

using namespace std;


void NN_search(HashTable *cube, std::vector<int> &g, std::vector<int> &query, int &position, int &M, int &probes ,int &k, bool Euclidean, std::ofstream &output, double &ApproxDist, double &averagetime)
{
	int tmpfi;
	long double distance;

	std::vector<int> b;
	long double db = 9999999.0;
	string pid;
	

	output <<"ApproxNN neighbors:"<<std::endl;
	bitset<32> hamming_distance;
	// initial hamming distance
	int h_dist = 1;
	bool neighbor_flag = 0;
	// points searched
	int count_lines=1;
	clock_t begin = clock();
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
						
						output <<"Initial position "<<position<<std::endl;
						position = tmp_pos;
						neighbor_flag = 1;
						output <<"Position to neighbor vertex "<<position<<std::endl;
						break;
					}
				}
				// if no neighbor with hamming distance h_dist , search for h_dist+1
				if (y == cube->get_num_of_buckets() && !neighbor_flag)
					h_dist++;
			}
		}
		if (!(cube->bucket_exist(position)))
		{
			cout <<"*****MPIKA*****"<<std::endl;
			continue;
		}
		Buckets* bucket = cube->access_bucket(position);
		if (bucket == NULL)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<position<<std::endl;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
		
			std::vector<int> p(it->get_p());
			
			if (Euclidean)
			{
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
			
			//trick
			if (count_lines == M)
			{
				cout <<"TRICK USED"<<std::endl;
				break;
			}
			count_lines++;	
		}
	}
	clock_t end = clock();
	double elapsed_time = (double)(end-begin)/CLOCKS_PER_SEC;
	averagetime += elapsed_time;
	// cout <<"ApproxNN neighbor "<<pid<<" with distance "<<db<<std::endl;
	// output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	output <<"NN_SEARCH "<<pid<<std::endl;
	output <<"DISTANCE "<<db<<std::endl;
	ApproxDist = db;
	output <<"tLSH: "<<elapsed_time<<std::endl;
}