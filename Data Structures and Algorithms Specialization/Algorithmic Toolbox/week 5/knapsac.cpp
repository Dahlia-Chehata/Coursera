#include <iostream>
#include <vector>
using namespace std;
/*
int withRepetition(int n,int W,int weigh[],int v[])
{
    int value [W+1];
    value[0]=0;
    for (int w=1;w<=W;w++)
    {
        value[w]=0;
        for (int i=1;i<=n;i++)
        {
            if (weigh[i]<=w)
               value[w]=max(value[w],value[w-weigh[i]]+v[i]);
        }
    }
 return value[W];
}
int withoutRepetition(int n,int W,int weigh[],int v[])
{
    int value[n+1][W+1];
    for (int i=0;i<=W;i++)value[0][i]=0;
    for (int i=0;i<=n;i++)value[i][0]=0;

    for (int i=1;i<=n;i++)
    {
        for (int w=1;w<=W;w++)
        {
            value[i][w]=value[i-1][w];
            if (weigh[i]<=w)
            value[i][w]=max(value[i][w],value[i-1][w-weigh[i]]+v[i]);
        }
    }
  return value[n][W];
}*/
int optimalWeight(int n,int W,int weigh[])
{
    //int value[n+1][W+1];

    vector<int> v1(W+1);
    vector <vector<int > > value (n+1,v1);
    for (int i=0;i<=W;i++)
    {

    }
    for (int i=0;i<=W;i++)value[0][i]=0;
    for (int i=0;i<=n;i++)value[i][0]=0;

    for (int i=1;i<=n;i++)
    {
        for (int w=1;w<=W;w++)
        {
            value[i][w]=value[i-1][w];
            if (weigh[i]<=w)
            value[i][w]=max(value[i][w],value[i-1][w-weigh[i]]+weigh[i]);
        }
    }
  return value[n][W];
}
int main()
{
    int W,n;
    cin>>W>>n;
    int w[n+1]/*,v[n+1]*/;
    for (int i=1;i<=n;i++)
        cin>>w[i];
   // for (int i=1;i<=n;i++)
        //cin>>v[i];
     // cout <<withoutRepetition(n,W,w,v)<<endl;
     // cout <<withRepetition(n,W,w,v)<<endl;
      cout <<optimalWeight(n,W,w)<<endl;

    return 0;
}
