#include "../include/Range_search.h"

using namespace std;


void Range_search(HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, double &r, int &c, bool Cosine, std::ofstream &output)
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

	output <<"R-near neighbors:"<<std::endl;

	// if (!Cosine)
	// 	cout <<std::endl<<"-------------------------------Start Range_Search----------------------------------------"<<std::endl;
	// else
	// 	cout <<std::endl<<"-------------------------------Start Cosine Range_Search----------------------------------------"<<std::endl;
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
		
		// cout <<"Start HashTable "<<i<<std::endl;
		output <<"Size of List is "<<List.size()<<" bucket "<<tmpfi<<std::endl;
		int count_lines=0;
		int passed=0;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			std::vector<int> p(it->get_p());
			// std::vector<int> pq(it->get_g());
			// if (tmpg != pq)
			// 	continue;
			
			if (!Cosine)
				distance = Euclidean_Distance(query,p,k);
			else
				distance = Cosine_Similarity(query,p);
			if (distance < db)
			{
				b = p;
				db = distance;
				pid = it->get_id();
			}
			if (distance < c*r)
			{
				passed++;
				output <<it->get_id()<<" -> distance "<<distance<<std::endl;
				// cout <<"Dist is "<<distance<< endl;
				// cout <<"NEIGHBOR:"<<std::endl;
				// for (std::vector<int>::iterator iter = p.begin(); iter!= p.end(); iter++)
				// 	cout <<*iter<<" ";
				// cout <<std::endl;
				// cout <<"QUERY:"<<std::endl;
				// for (std::vector<int>::iterator iter = query.begin(); iter!= query.end(); iter++)
				// 	cout <<*iter<<" ";
				// cout <<std::endl;
				// cout <<"-------------------------------------------------------------------------"<<std::endl;
			}
			count_lines++;
		}
		output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
		// cout <<"End HashTable "<<i<<std::endl;
	}
	// if (!Cosine)
	// 	cout <<std::endl<<"--------------------------------End Range_Search----------------------------------------"<<std::endl;
	// else
	// 	cout <<std::endl<<"--------------------------------End Cosine Range_Search----------------------------------------"<<std::endl;

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
}