#include "../include/NN_search.h"

using namespace std;

#include "../include/Range_search.h"

using namespace std;


void NN_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, bool Euclidean, std::ofstream &output)
{
	int tmpfi;
	long double distance;
	// std::vector<int> tmpg;
	// std::vector<int> p;

	//test
	std::vector<int> b;
	long double db = 9999999.0;
	string pid;
	
	// cout <<"***CxR = "<<c*r<<"***"<<std::endl;

	output <<"ApproxNN neighbors:"<<std::endl;

	// int count_lines=1;
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
		if (bucket == (Buckets*)-1)
			continue;
		list<Node> List = bucket->access_list();
		
		output <<"Size of List is "<<List.size()<<" bucket "<<tmpfi<<std::endl;
		int count_lines=1;
		// int passed=0;
		// cout <<"** START HASHTABLE "<<i<<"** "<<std::endl;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
		
			std::vector<int> p(it->get_p());
			// check if gs are same
			std::vector<int> pq(it->get_g());
			if (tmpg != pq)
				continue;
			
			if (Euclidean)
				distance = Euclidean_Distance(query,p,k);
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
	// cout <<"ApproxNN neighbor "<<pid<<" with distance "<<db<<std::endl;
	// output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	output <<"NN_SEARCH "<<pid<<std::endl;
	output <<"DISTANCE "<<db<<std::endl;

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
}