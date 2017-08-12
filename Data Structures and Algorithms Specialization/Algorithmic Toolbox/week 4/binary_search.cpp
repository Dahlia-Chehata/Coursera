#include <iostream>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <math.h>
#include <string.h>
using namespace std;
int binearySearch (long long bi,long long a[],int l,int r)
{
    while (l<=r)
    {
        int m = l+((r-l)/2);
        if (a[m]==bi) return m;
        if (bi<a[m]) r=m-1;
        else l= m+1;
    }
    return -1;
}
/*int linearSearch(long long a[],long long bi,int n)
{
    for (int i=0;i<n;i++) {
        if (bi==a[i]) return i;
       // else return -1;
    }
    return -1;
}
 //Recursive
int binearySearch (long long bi,long long a[],int l,int r)
{
    int m =l+ ((r-l)/2);
    if (l>r) return -1;
    if (a[m]==bi)return m;
    if (bi<a[m]) binearySearch(bi,a,l,m-1,n);
    else binearySearch(bi,a,m+1,r,n);

}*/
int main()
{
   int n,k;
    cin>>n;
    long long  a[n];
    for(int i=0; i<n; i++)
        cin>>a[i];
    cin>>k;
    long long b[k];
    for (int i=0; i<k; i++)
        cin>>b[i];
    for (int i=0; i<k; i++)
        cout <<binearySearch(b[i],a,0,n-1)<<" ";
        cout <<endl;
    return 0;
}
