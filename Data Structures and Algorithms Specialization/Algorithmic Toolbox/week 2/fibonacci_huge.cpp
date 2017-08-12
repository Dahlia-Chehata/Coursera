#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
  int pi [1000000];

int pisanoLength (long long m)
{
   pi[0]=0;
   pi[1]=1;
   int i;
  for (i=2;;i++)
{
   if (pi[i-2]==0&&pi[i-1]==1 &&i!=2) break;
   pi[i] =(pi[i-1]+pi[i-2])% m;
}
return i-2;
}
/*long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}
*/
int main()
{ long long n,m;
  /** Stress Testing **/
  /* while (true)
   {
      n= rand()%10^18 +1;
      m=rand() %100000+2;
      long long x=get_fibonacci_huge_naive(n,m);
      int y=pi[n%pisanoLength(m)];

   }
   */
   cin>>n>>m;
   int index = n%pisanoLength(m);
   cout << pi[index];
    return 0;
}
