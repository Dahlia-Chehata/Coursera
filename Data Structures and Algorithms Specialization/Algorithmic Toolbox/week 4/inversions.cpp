#include <iostream>

using namespace std;
long long inversions;
void Merge (long a[],int l,int m,int r )
{
    int j=0;
    int b_size=m-l+1;
    int c_size=r-m;
    long b[b_size],c[c_size];
    for (int i=l;i<=m;i++) {
        b[j++]=a[i];
    }
    j=0;
    for (int i=m+1;i<=r;i++) {
        c[j++]=a[i];
    }
    int cnt=l,B=0,C=0;
    while (B<b_size&&C<c_size)
    {
        if (b[B]>c[C])
        {
            inversions+=(b_size-B);
            a[cnt]=c[C];
            C++;
        }
        else
        {
            a[cnt]=b[B];
            B++;
        }
        cnt++;
    }
    if (C<c_size)
    {
        for (int i=C;i<c_size;i++)
        {
            a[cnt]=c[i];
            cnt++;
        }
    }
    else
    {
        for (int i=B;i<b_size;i++)
        {
            a[cnt]=b[i];
            cnt++;
        }
    }
}
void mergeSort(long a[],int l,int r)
{
    if (l<r){
    int mid=l+(r-l)/2;
    mergeSort(a,l,mid);
    mergeSort(a,mid+1,r);
    Merge(a,l,mid,r);
    }
}
int main()
{
    int n;
    cin >>n;
    long a[n];
    for (int i=0; i<n; i++)
        cin>>a[i];
    mergeSort(a,0,n-1);
    cout <<inversions;
    return 0;
}
