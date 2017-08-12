#include <iostream>
#include <vector>
using namespace std;
vector <long long> summands;
vector <long long> solve (long long k,long long l)
{
    /**recursion**/
 /*  if (k<=2*l)
  {  summands.push_back(k);
     return summands;
  }
  summands.push_back(l);
  solve (k-l,l+1);*/
  while (k>2*l)
  {
      summands.push_back(l);
      k-=l;
      l++;
  }
  summands.push_back(k);
  return summands;
}
int main()
{
  long long n;
   cin>>n;
  vector <long long> x = solve (n,1);
   cout <<summands.size()<<endl;
   for (vector<long long>::const_iterator i =summands.begin();i!=summands.end();i++)
    cout <<*i<<" ";
    return 0;
}
