#include <iostream>
#include <queue>
#include <string.h>
#include <map>
using namespace std;
typedef bool (*comp)(pair<long,char>, pair<long,char>);
bool compare(pair<long,char>x, pair<long,char>y)
{
    if (x.first==y.first)
        return x.second>y.second;
    return x.first>y.first;

}
int main()
{
    int s,p;
    cin>>s>>p;
    long points[p];
     map <long,int>sol;
    long x,y;
    priority_queue < pair<long,char> ,vector < pair<long,char> >,comp > pq(compare);
    for (int i=0; i<s; i++) {
        cin>>x>>y;
        pq.push(make_pair(x,'l'));
        pq.push(make_pair(y,'r'));
    }
    for (int i=0; i<p; i++){
        cin>> points[i];
        pq.push(make_pair(points[i],'p'));
    }
    int cnt=0,m=0;
    while (pq.size())
    {
        pair<long,long> x=pq.top();
        pq.pop();
        if (x.second=='l') cnt++;
        else if (x.second=='p')
        {
           sol.insert(pair<long,int>(x.first,cnt));
        }
        else
        {
            if (cnt>0) cnt--;
        }
    }
    for (int i=0; i<p; i++){
        cout<<sol.find(points[i])-> second <<" ";
    }
    return 0;
}
