#include "../include/Euclidean_distance.h"

long double Euclidean_Distance(std::vector<int> & v1, std::vector<int> &v2,int &k)
{
 	long double sum = 0;
 	for(unsigned int i = 0;i<v1.size();i++){
 		sum += pow((v1[i] - v2[i]),k);
 	}
 	return pow(sum,1.0/k);
};