#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool operator > (pair <int,int> a,pair <int,int> b)
{
    return a.second > b.second;
}
struct edge
{
    int End;
    int weigh;
};
vector <vector<edge>> adjList;
long Dijkstra(int n,int u,int v)
{
    long dist [n+1];
    for (int i=1; i<=n; i++) dist[i]=1000000000;
    dist[u]=0;
    priority_queue <pair <int,int> , vector <pair <int,int> > , greater <pair <int,int>>> Q;
    Q.push(make_pair(u,dist[u]));
    while (Q.size())
    {
        pair <int,int> p =Q.top();
        Q.pop();
        u=p.first;
        for (int i=0; i<adjList[u].size(); i++)
        {
            edge E=adjList[u][i];
            if (dist[E.End]> dist[u]+E.weigh)
            {
                dist[E.End]= dist[u]+E.weigh;
                Q.push(make_pair(E.End,dist[E.End]));
            }
        }
    }
    return dist[v];
}
int main()
{
    int n,m,f,u,v,w;
    edge E;
    cin>>n>>m;
    adjList.resize(n+1);
    for (int i=0; i<m; i++)
    {
        cin>>f>>E.End>>E.weigh;
        adjList[f].push_back(E);
    }
    cin>>u>>v;
    long sol=Dijkstra(n,u,v);
    (sol==1000000000)? cout <<"-1" : cout <<sol;
    return 0;
}
