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

	int count_lines=1;
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
		// int passed=0;
		cout <<"** START HASHTABLE "<<i<<"** "<<std::endl;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
		
			std::vector<int> p(it->get_p());
			if (Euclidean)
				distance = Euclidean_Distance(query,p,k);
			else
				distance = Cosine_Similarity(query,p);
			cout <<"Checking "<<it->get_id()<<" with distance "<<distance<<std::endl;
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
		cout <<"** END HASHTABLE "<<i<<"** "<<std::endl;
	}
	cout <<"ApproxNN neighbor "<<pid<<" with distance "<<db<<std::endl;
	// output <<"COUNT_LINES "<<count_lines<<" and passed "<<passed<<std::endl;
	output <<"NN_SEARCH "<<pid<<std::endl;
	output <<"DISTANCE "<<db<<std::endl;

	output <<"NN_search from range is "<<pid<<std::endl;
	output <<"Distance is "<<db<<std::endl;
}






// void NN_search(std::vector<int> &neighbor, HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, long double &dist, string &id, bool Cosine, std::ofstream &output)
// {
// 	int counter = 1;
// 	int tmpfi;
// 	long double distance;
// 	string pid;
// 	// std::vector<int> tmpg;
// 	std::vector<int> p;
	
// 	std::vector<int> b;
// 	long double db = 9999999.0;
// 	// for every hashTable
// 	for (int i=0;i<L;i++)
// 	{
// 		tmpfi = fi[i];
// 		cout <<"TMPFI "<<tmpfi<<std::endl;
// 		std::vector<int> tmpg(g[i]);
// 		// tmpg = g[i];
// 		if (!(hashTables[i]->bucket_exist(tmpfi)))
// 		{
// 			cout <<"*****MPIKA BUCKET DONT EXIST*****"<<std::endl;
// 			tmpg.erase(tmpg.begin(),tmpg.end());
// 			continue;
// 		}
// 		cout <<"MPAINW BUCKET"<<std::endl;
// 		Buckets* bucket =  hashTables[i]->access_bucket(tmpfi);
// 		if (bucket == (Buckets*)-1)
// 			continue;
// 		list<Node> List = bucket->access_list();
// 		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
// 		{
// 			// std::vector<int> p(it->get_p());
// 			p = it->get_p();
// 			// cout <<std::endl;
// 			// for (std::vector<int>::iterator j=p.begin();j!=p.end();j++)
// 			// 	cout <<*j<<' ';
// 			// cout <<std::endl;
// 			// if (tmpg != it->get_g())
// 			// 	continue;
			
// 			//ApproxNN_search
// 			// if (!NNflag)
// 			// {
// 				// if (counter == 3*L)
// 				// {
// 				// 	cout <<"Trick used"<<std::endl;
// 				// 	//trick , finish and right result to output
// 				// 	neighbor = b;
// 				// 	dist = db;
// 				// 	break;
// 				// 	// exit(1);
// 				// }
// 				// counter++;
// 			// }
			
// 			if (!Cosine)
// 				distance = Euclidean_Distance(query,p,k);
// 			else
// 				distance = 1 - Cosine_Similarity(query,p);
			
// 			cout <<"COmpare: "<<distance<<"from "<<it->get_id()<<" and "<<db<<std::endl;
// 			if (distance < db)
// 			{
// 				b = p;
// 				db = distance;
// 				pid = it->get_id();
// 			}
			
// 		}
// 		// if (!NNflag)
// 		// 	break;
// 		// break;

// 		// tmpg.erase(tmpg.begin(),tmpg.end());
// 	}
// 	neighbor = b;
// 	dist = db;
// 	output <<"ApproxNN_search "<<pid<<std::endl;
// 	output <<"Distance is "<<db<<std::endl;
// }