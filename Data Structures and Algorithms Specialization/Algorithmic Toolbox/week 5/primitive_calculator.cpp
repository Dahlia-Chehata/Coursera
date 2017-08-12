#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#define pb push_back
using namespace std;
vector <long> sq ;
long func (long n)
{
    //forward filling
    long operations[n+1];
    operations[1]=0;
    for (int i=2;i<=n;i++)
    {
        long a= (i%2)? 999999999 : operations [i/2];
        long b= (i%3)? 999999999 : operations [i/3];
        long c= operations [i-1];
        operations[i]=min(a,min(b,c))+1;
    }
     long sol=n;
    //backtracking
   sq.pb(n);
   while (n>1)
   {
      if (n/2>=1 && operations[n/2]==operations[n]-1)n/=2;
      else if (n/3>=1 && operations[n/3]==operations[n]-1)n/=3;
      else if(n - 1 >= 1 &&operations[n - 1]==operations[n] - 1) n-=1;
        sq.pb(n);
   }
    reverse(sq.begin(),sq.end());
    return operations[sol];
}
int main()
{
   long n;
   cin>>n;
   cout <<func(n)<<endl;
   for (vector <long>::iterator it=sq.begin();it!=sq.end();++it)
     cout <<*it <<" ";
    return 0;
}
