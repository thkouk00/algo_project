#include "../include/normal_distr.h"

using namespace std;


int binarytodecimal(std::vector<int> &g)
{
  string str;
  long int n;
  for (std::vector<int>::iterator it=g.begin();it!=g.end();it++)
    str += std::to_string(*it);
  n = atoi(str.c_str());
  int decimalNumber = 0, i = 0, remainder;
  while (n!=0)
  {
      remainder = n%10;
      n /= 10;
      decimalNumber += remainder*pow(2,i);
      ++i;
  }
  return decimalNumber;
}


// Function to check integer overflow 
int check_overflow(int num) 
{ 
    // Checking if addition will cause overflow 
    if (num >= INT_MAX) 
      return 0; 
    // No overflow occured 
    else
      return 1; 
} 

//give vector v to fill with random numbers in normal distribution
void normal_distr_generator(std::vector<double> &v,int elements)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::normal_distribution<double> distribution(0.0,1.0);
  
  for (int i=0; i<elements; ++i) 
  {
    double number = distribution(generator);
    v.push_back(number);
  }
}

