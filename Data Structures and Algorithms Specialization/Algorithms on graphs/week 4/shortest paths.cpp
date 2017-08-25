#include <iostream>
#include <vector>
#include <climits>
#include <limits>
#include <queue>
#include<float.h>

#define MIN -numeric_limits<long long>::min()
#define MAX numeric_limits<long long>::max()

using namespace std;
struct edge
{
    int u,v;
    long weigh;
    edge(int u,int v,long weigh)
    {
        this->u=u;
        this->v=v;
        this->weigh=weigh;
    }
};
vector <edge> edgeList;
vector< vector <int> > adj;
queue <int> Q;

void BellmanFord(int n,int m,int s,vector<long long >&dist)
{
    dist[s]=0;
    for (int i=1;i<=n-1;i++)
    {
        for (int j=0; j<m; j++)
        {
            edge E=edgeList[j];
            if (dist[E.u]!=MAX && dist[E.v]> dist[E.u]+E.weigh)
                dist[E.v]= dist[E.u]+E.weigh;
        }
    }
    for (int i=0; i<m; i++)
    {
       edge E=edgeList[i];
       if (dist[E.u]!=MAX && dist[E.v]!=MIN && dist[E.v]> dist[E.u]+E.weigh)
       {
            dist[E.v]=MIN;
            Q.push(E.v);
       }
    }
}
void BFS (vector<long long >&dist)
{
    while (Q.size())
    {
        int u =Q.front();
        Q.pop();
        for (int i=0;i<adj[u].size();i++)
        {
            if (dist[adj[u][i]]!=MIN)
            {
                dist[adj[u][i]]=MIN;
                Q.push(adj[u][i]);
            }
        }
    }
}
int main()
{
    int n,m,s;
    cin>>n>>m;
    int u,v;
    long w;
    adj.resize(n+1);
    for (int i=0; i<m; i++)
    {
        cin>>u>>v>>w;
        edgeList.push_back(edge(u,v,w));
        adj[u].push_back(v);
    }
    cin>>s;
    vector<long long > dist (n+1,MAX);

    BellmanFord(n,m,s,dist);
     BFS(dist);
    for (int i=1;i<=n;i++)
    {
       if (dist[i]==MAX)
        cout <<"*"<<endl;
       else if (dist[i]==MIN)
        cout <<"-"<<endl;
       else
        cout <<dist[i]<<endl;
    }
    return 0;
}
