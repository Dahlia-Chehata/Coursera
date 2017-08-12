#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
bool compare(pair <long long,long long> one,pair <long long,long long> two)
{
    return one.second<two.second;
}
pair <int,vector <long long> >func(pair <long long,long long> coordiantes[],int n)
{
    long long prevb=coordiantes[0].second;
    int cnt=1;
    vector <long long> sol;
    sol.push_back(prevb);
    for (int i=1; i<n; i++)
    {
        if (!(coordiantes[i].second >=prevb &&coordiantes[i].first<=prevb))

        {
            prevb=coordiantes[i].second;
            sol.push_back(prevb);
            cnt++;
        }
    }
    return make_pair(cnt,sol);
}
int main()
{
    int n;
    cin>>n;
    pair <long long,long long> coordiantes[n];
    for (int i=0; i<n; i++)
    {
        cin>>coordiantes[i].first>>coordiantes[i].second;
    }
    sort(coordiantes,coordiantes+n,compare);
    //cout <<endl;
    // for (int i=0;i<n;i++)
    // cout <<coordiantes[i].first<<" " <<coordiantes[i].second<<endl;
    pair <int,vector <long long> > x=func(coordiantes,n);
    cout <<x.first<<endl;
    for (vector<long long>::const_iterator i = x.second.begin(); i != x.second.end(); ++i)
        cout << *i << ' ';
    return 0;
}
