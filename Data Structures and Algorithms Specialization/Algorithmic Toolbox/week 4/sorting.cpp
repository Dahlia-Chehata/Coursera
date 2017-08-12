#include <iostream>
#include <stdlib.h>
using namespace std;

/** 3-way partitioning **/

/*
pair <int,int> Partition(long a[],int l,int r,int n)
{
    long pivot= a[l];
     int j1=l,cnt=0;
    for (int i=l+1;i<n;i++)
    {
        if (a[i]<pivot)
        {
            while (a[i-1]>pivot)
            {
                swap(a[i],a[i-1]);
                i--;
            }

            swap(a[i],a[j1]);
            j1++;
        }
        else if (a[i]==pivot)
        {
           cnt++;
           swap(a[j1+cnt],a[i]);
  return make_pair(j1,j1+cnt);
}*/
pair <int,int> Partition(long a[],int l,int r,int n)
{
    long pivot=a[l];
    for (int i=l+1; i<=r;)
    {
        if (a[i]<pivot) swap(a[i++],a[l++]);
        else if (a[i]>pivot) swap(a[i],a[r--]);
        else i++ ;
    }
    return make_pair(l,r);

}

void QuickSort (long a[],int left,int right,int n)
{
    if(left>=right)return;
    int k =(left+right)/2;
    swap(a[k],a[left]);
   // int pivot1 = Partition(a,left,right,n).first;
   // int pivot2 = Partition(a,left,right,n).second;
    //cout <<"p1  :  "<<pivot1<<"    pivot2  : "<<pivot2<<endl;
     long pivot=a[left];
     int p1=left,p2=right;
/** partition**/
    for (int i=p1+1; i<=p2;)
    {
        if (a[i]<pivot) swap(a[i++],a[p1++]);
        else if (a[i]>pivot) swap(a[i],a[p2--]);
        else i++ ;
    }
    QuickSort(a,left,p1-1,n);
    QuickSort(a,p2+1,right,n);
}

int main()
{
    int n;
    cin >>n;
    long a[n];
    for (int i=0; i<n; i++)
        cin>>a[i];
    QuickSort(a,0,n-1,n);
    for (int i=0; i<n; i++)
        cout<<a[i]<<" ";
    return 0;
}
