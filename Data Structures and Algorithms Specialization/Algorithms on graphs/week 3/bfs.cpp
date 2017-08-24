#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
vector < vector <int > > adjList;
queue<int> Q;
int BFS(int n,int u,int v)
{
    int dist[n+1];
    for (int i=1;i<=n;i++) dist[i]=200000;
    dist[u]=0;
    Q.push(u);
    while (Q.size())
    {
        u=Q.front();
        Q.pop();
        for (int i=0;i<adjList[u].size();i++)
        {
            if (dist[adjList[u][i]]==200000)
            {
                Q.push(adjList[u][i]);
                dist[adjList[u][i]] = dist[u]+1;
            }

        }
    }
    return dist[v];
}
int main()
{
    int n,m,f,s,u,v;
    cin>>n>>m;
    adjList.resize(n+1);
    for (int i=0; i<m; i++)
    {
        cin>>f>>s;
        adjList[f].push_back(s);
        adjList[s].push_back(f);
    }
    cin>>u>>v;
    int sol=BFS(n,u,v);
    (sol == 200000) ? cout << "-1":cout <<sol;
}
