#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
vector <vector <int> > adjList ;
void dfsUtil (int u,bool* vis)
{
    vis[u]=true;
    for (int i=0; i<adjList[u].size(); i++)
        if (!vis[adjList[u][i]])
          dfsUtil(adjList[u][i],vis);

    }
int DFS(int n,bool*vis)
{
    int CC =0;
    for (int i=1; i<=n; i++)
    {
        if (!vis[i]) {
            dfsUtil(i,vis);
            CC++;
        }
    }
    return CC;
}
int main()
{
    int n,m,f,s;
    cin>>n>>m;
    adjList.resize(n+1);
    for (int i=0;i<m;i++)
    {
        cin>>f>>s;
        adjList[f].push_back(s);
        adjList[s].push_back(f);
    }
    bool vis [n+1];
    memset(vis,0,sizeof vis);
    cout <<DFS(n,vis);
    return 0;
}
