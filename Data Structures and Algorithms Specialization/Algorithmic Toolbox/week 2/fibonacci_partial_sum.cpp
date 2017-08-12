#include <iostream>
#include<cmath>
using namespace std;
//pisano period of 10 is 60 from previous problem
int pi[61];
 void fillPisanoOf10 ()
 {
      pi[0]=0;
      pi[1]=1;
     for (int i=2;i<=60;i++)
        pi[i]=(pi[i-1]+pi[i-2]);
 }
int main()
{
  long long n,m;
  cin>>m>>n;
  n%=60,m%=60;
  fillPisanoOf10 ();
  cout << abs((pi[n+2]-pi[m+1])%10);
    return 0;
}
