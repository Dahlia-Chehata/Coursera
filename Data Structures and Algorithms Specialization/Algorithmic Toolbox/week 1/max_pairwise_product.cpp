#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

long long slow (int n,const vector<int>& arr)
{
    long long  res=0;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (((long long)arr[i])*arr[j]>res)
                res= (long long)arr[i]*arr[j];
        }
    }
    return res;
}
long long int fast (int n,vector<int>const &arr)
{
    int idx1=-1,idx2=-1;
    int maxm =0;
    for (int i=0; i<n; i++)
    {
        if (arr[i]>=maxm)
        {
            maxm=arr[i];
            idx1=i;
        }
    }
    maxm=0;
    for (int i=0; i<n; i++)
    {
        if (arr[i]>=maxm&&i!=idx1)
        {
            maxm=arr[i];
            idx2=i;
        }

    }
    return (long long)arr[idx1]*arr[idx2] ;
}
int main()
{
    int n;
     /** stress testing **/
    /*
    while (true){
    n=rand()%10+2;
    cerr<<n<<endl;
    vector <int> tst;
    for (int i=0;i<n;i++)
    {
        tst.push_back(rand()%100000);
    }
    for (int i=0;i<n;i++)
        cerr<<tst[i]<<" ";
        cout <<endl;
    if (slow(n,tst) !=fast(n,tst)){
            cout<<"wrong"<<endl;;
            cout<<slow(n,tst)<<" "<<fast(n,tst)<<endl;
             break;
    }
    else {
        cout<<"OK"<<endl;
        cout<<slow(n,tst)<<" "<<fast(n,tst)<<endl;
    }
    }
    */
    cin >> n;
    vector <int>arr(n);
    for (int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    cout <<fast(n,arr);
    return 0;
}
