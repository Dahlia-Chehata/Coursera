#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
vector < vector <int > > adjList;
queue<int> Q;
bool BFS(int u,int*color)
{
    color[u]=0;
    Q.push(u);
    while (Q.size())
    {
        u=Q.front();
        Q.pop();
        for (int i=0;i<adjList[u].size();i++)
        {
            if (color[adjList[u][i]]== -1)
            {
                Q.push(adjList[u][i]);
                color[adjList[u][i]] = ! color[u];
            }
            else
            {
                if ( color[adjList[u][i]]==color[u])
                    return false;
            }

        }
    }
    return true;
}
bool isBipartite(int n)
{
    int color [n+1];
    for (int i=1;i<=n;i++) color[i]=-1;
    for (int i=1;i<=n;i++)
    {
        if (color[i]==-1)
            if (!BFS(i,color))return false;
    }
    return true;
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
    cout << isBipartite(n);
}
