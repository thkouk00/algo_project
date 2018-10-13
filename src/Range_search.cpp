#include "../include/Range_search.h"

using namespace std;


void Range_search(std::vector<int> &neighbor, HashTable **hashTables, std::vector<std::vector<int>> &g, std::vector<int> &query, std::vector<int> &fi, int &L, int &k, int &r, int &c)
{
	int tmpfi;
	long double distance;
	std::vector<int> tmpg;
	std::vector<int> p;
	
	cout <<"***CxR = "<<c*r<<"***"<<std::endl;

	cout <<std::endl<<"-------------------------------Start Range_Search----------------------------------------"<<std::endl;
	for (int i=0;i<L;i++)
	{
		tmpfi = fi[i];
		cout <<"TMPFI "<<tmpfi<<std::endl;
		tmpg = g[i];
		if (!hashTables[i]->bucket_exist(tmpfi))
		{
			cout <<"*****MPIKA*****"<<std::endl;
			continue;
		}
		Buckets* bucket = hashTables[i]->access_bucket(tmpfi);
		if (bucket == (Buckets*)-1)
			continue;
		list<Node> List = bucket->access_list();
		
		cout <<"Start HashTable "<<i<<std::endl;
		for (std::list<Node>::iterator it = List.begin(); it!=List.end(); it++)
		{
			p = it->get_p();
			if ((distance = Euclidean_Distance(query,p,k)) < c*r)
			{
				cout <<"Dist is "<<distance<< endl;
				cout <<"NEIGHBOR:"<<std::endl;
				for (std::vector<int>::iterator iter = p.begin(); iter!= p.end(); iter++)
					cout <<*iter<<" ";
				cout <<std::endl;
				cout <<"QUERY:"<<std::endl;
				for (std::vector<int>::iterator iter = query.begin(); iter!= query.end(); iter++)
					cout <<*iter<<" ";
				cout <<std::endl;
				cout <<"-------------------------------------------------------------------------"<<std::endl;
			}
		}
		cout <<"End HashTable "<<i<<std::endl;
	}
	cout <<std::endl<<"--------------------------------End Range_Search----------------------------------------"<<std::endl;
}