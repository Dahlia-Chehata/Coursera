#include <iostream>
#include <vector>
#include <limits>

using namespace std;
struct edge
{
    int u,v,weigh;
    edge(int u,int v,int weigh)
    {
        this->u=u;
        this->v=v;
        this->weigh=weigh;
    }
};
vector <edge> edgeList;
bool BellmanFord(int n,int m)
{
    long long dist [n+1];
    for (int i=1; i<=n; i++) dist[i]=numeric_limits<int>::max();
    dist[1]=0;
    for (int i=1;i<=n-1;i++)
    {
        for (int j=0; j<edgeList.size(); j++)
        {
            edge E=edgeList[j];
            if (dist[E.v]> dist[E.u]+E.weigh)
                dist[E.v]= dist[E.u]+E.weigh;
        }
    }
    for (int i=0;i<m;i++)
    {
        edge E=edgeList[i];
            if (dist[E.v]> dist[E.u]+E.weigh)
                return true;
    }
    return false;
}
int main()
{
    int n,m;
    cin>>n>>m;
    int u,v,w;
    for (int i=0; i<m; i++)
    {
        cin>>u>>v>>w;
        edgeList.push_back(edge(u,v,w));
    }
    cout<<BellmanFord(n,m);
    return 0;
}
