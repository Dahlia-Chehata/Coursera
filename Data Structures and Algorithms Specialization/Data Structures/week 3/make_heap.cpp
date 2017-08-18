#include <iostream>
#include <vector>
using namespace std;
vector <pair <int,int > > v;
void ShiftDown(int i,int siz,long *H)
{
    int minIdx=i;
    int leftChildIdx=2*i;
    int rightChildIdx =2*i+1;
    if (leftChildIdx<=siz && H[leftChildIdx]<H[minIdx])
        minIdx=leftChildIdx;
    if (rightChildIdx<=siz && H[rightChildIdx]<H[minIdx])
        minIdx=rightChildIdx;
    if (minIdx!=i)
    {
        swap(H[minIdx],H[i]);
        v.push_back(make_pair(i-1,minIdx-1));
        ShiftDown(minIdx,siz,H);
    }
}
 void buildHeap(long*A,int n)
 {
     for (int i=n/2;i>0;i--)
     {
        ShiftDown(i,n,A);
     }
 }
int main()
{
int n;
cin>>n;
long a[n];
for (int i=1;i<=n;i++)
    cin>>a[i];
buildHeap(a,n);
cout <<v.size()<<endl;
for (vector <pair <int,int> > ::iterator it =v.begin();it !=v.end();it++)
    cout << (*it).first <<" "<<(*it).second<<endl;
    return 0;
}
