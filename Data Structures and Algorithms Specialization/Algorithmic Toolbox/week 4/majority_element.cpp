#include <iostream>
#include <algorithm>
using namespace std;
/**O(n)
Boyer And Moore 's Voting Algorithm
**/
long isMajorityCandidate (long a[],int n)
{
    long majority = a[0];
    int cnt=1;
    for (int i=1; i<n; i++)
    {
        if (a[i]==majority) cnt++;
        else cnt--;
        if (cnt==0)
        {
            majority = a[i];
            cnt=1;
        }
    }
    return majority;
}
int isMajority(long x,long a[],int n)
{
    int cnt=0;
    for (int i=0; i<n; i++)
        if(x==a[i])
            cnt++;
    if (cnt>n/2)
        return 1;
    else return 0;
}
/** O(n log n)**/
int majority (long*a,int n)
{
    if (n==1)return a[0] ;
    long left = majority(a,n/2);
    long right= majority(a+n/2,n-n/2);
    if (left==right) return left;
    if (count(a,a+n,left)>n/2)return left;
    if (count(a,a+n,right)>n/2)return right;
    return -1;
}
int main()
{
    int n;
    cin>>n;
    long a[n];
    for (int i=0; i<n; i++)
        cin>>a[i];
    (majority(a,n)==-1)?cout <<"0":cout <<"1";
  //  cout<<endl;
  //  cout<<isMajority(isMajorityCandidate(a,n),a,n)<<endl;
    return 0;
}
