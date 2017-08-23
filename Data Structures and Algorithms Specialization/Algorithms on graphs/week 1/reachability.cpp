#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
vector < vector<int> > adjList;
int ret=0;
int dfs(int u,bool*vis,int v)
{
    if (u == v) return 1;
        vis[u]=true;
    for (int i=0;i<adjList[u].size();i++)
        if (!vis[adjList[u][i]])
       ret|= dfs(adjList[u][i],vis,v);
    return ret;
}
int main()
{
int n,m,u,v,f,s;
cin>>n>>m;
adjList.resize(n+1);
for (int i=0;i<m;i++)
{
    cin>>f>>s;
    adjList[f].push_back(s);
    adjList[s].push_back(f);
}
cin>>u>>v;
bool vis[n+1];
memset (vis,0,sizeof vis);
cout<<dfs(u,vis,v)<<endl;
    return 0;
}
