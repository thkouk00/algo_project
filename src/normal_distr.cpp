#include "../include/normal_distr.h"

using namespace std;

// Function to check integer overflow 
int check_overflow(int num) 
{ 
    // Checking if addition will cause overflow 
    if (num >= INT_MAX) 
      return -1; 
    // No overflow occured 
    else
      return 1; 
} 


void normal_distr_generator(std::vector<double> &v,int elements)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution(0.0,1.0);
  
  for (int i=0; i<elements; ++i) 
  {
    double number = distribution(generator);
    v.push_back(number);
    // std::cout << number<<std::endl;
    // if (j<4)
    // {
    //   v.push_back(number);
    //   j++;
    // }
    // else
    // {
    //   for (int it = 0;it<v.size();it++)
    //   { 
    //     cout <<v[it]<<" ";
    //   }
    //   cout <<std::endl;
    //   j=0;
    //   v.erase(v.begin(),v.end());
    // }
    // if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
  }
}

