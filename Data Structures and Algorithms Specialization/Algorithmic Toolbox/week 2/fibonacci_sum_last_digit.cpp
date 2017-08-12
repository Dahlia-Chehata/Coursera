#include <iostream>
//using pisano period
using namespace std;
  int pi[1000];

 int pisanoOf10 ()
 {
      int i;
      pi[0]=0;
      pi[1]=1;
     for (i=2;;i++)
     {
        if (pi[i-2]==0&&pi[i-1]==1&&i!=2) break;
        pi[i]=(pi[i-1]+pi[i-2])%10;
     }
   return i-2;
 }

int main()
{
  long long n;
  cin>>n;
  int index=n% pisanoOf10();
  cout <<((pi[index+2]-1)+10)%10;
    return 0;
}
