#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <numeric>
using namespace std;


int main()
{
  const int nrolls=20;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute

  std::default_random_engine generator;
  std::normal_distribution<double> distribution(0.0,1.0);
  std::vector<double> v;
  int p[10]={};
  int j=0;
  for (int i=0; i<nrolls; ++i) 
  {
    double number = distribution(generator);
    // std::cout << number<<std::endl;
    if (j<4)
    {
      v.push_back(number);
      j++;
    }
    else
    {
      for (int it = 0;it<v.size();it++)
      { 
        cout <<v[it]<<" ";
      }
      cout <<std::endl;
      j=0;
      v.erase(v.begin(),v.end());
    }
    // if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
  }
   std::vector<int> a{1, 1, 1, 1};
    std::vector<int> b{1,0,0,1};
 
    int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Inner product of a and b: " << r1 << '\n';
 
    int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
                                std::plus<>(), std::equal_to<>());
    std::cout << "Number of pairwise matches between a and b: " <<  r2 << '\n';

  return 0;
}