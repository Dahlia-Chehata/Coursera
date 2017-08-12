#include <iostream>
#include <algorithm>
using namespace std;
bool compare (pair <long,long> a,pair <long,long>b)
{
    double valPerUnt_1= (double)a.first/a.second;
    double valPerUnt_2= (double)b.first/b.second;
    return valPerUnt_1>valPerUnt_2;
}
double knapsack (long W,int n, pair <long,long> lista[])
{
    double sol=0.0;
    for (int i=0; i<n; i++)
    {
        if (W==0) return sol;
        double weight = min (W,lista[i].second);
        sol+=(double)weight*((double)lista[i].first/lista[i].second);
        lista[i].second-=weight;
        W-=weight;
    }
    return sol;
}
int main()
{
    int n;
    long W,vi,wi;
    cin>>n>>W;
    pair <long,long> lista [n];
    for (int i=0; i<n; i++)
    {
        cin>>vi>>wi;
        lista[i]=make_pair(vi,wi);
    }
    sort(lista,lista+n,compare);
    double sol=knapsack(W,n,lista);
    cout.precision(4);
    cout.setf(ios::fixed,ios::floatfield);
    cout <<sol<<endl;
    return 0;
}
