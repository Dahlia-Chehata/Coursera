#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
vector <vector <int> > adjList ;
vector <int> previ,post;
int clock=1;
void previsit(int u)
{
   previ[u]=clock;
   clock++;
}
void postvisit(int u)
{
   post[u]=clock;
   clock++;
}
void dfsUtil (int u,bool* vis)
{
    vis[u]=true;
    previsit(u);
    for (int i=0; i<adjList[u].size(); i++)
        if (!vis[adjList[u][i]])
          dfsUtil(adjList[u][i],vis);
   postvisit(u);
    }
void DFS(int n,bool*vis)
{
    for (int i=1; i<=n; i++)
        if (!vis[i])
            dfsUtil(i,vis);
}
int main()
{
    int n,m,f,s;
    cin>>n>>m;
    adjList.resize(n+1);
    post.resize(n+1);
    previ.resize(n+1);
    for (int i=0;i<m;i++)
    {
        cin>>f>>s;
        adjList[f].push_back(s);
        adjList[s].push_back(f);
    }
    bool vis [n+1];
    memset(vis,0,sizeof vis);
    DFS(n,vis);
    for (int i=1;i<=n;i++)
        cout <<previ[i]<<"/"<<post[i]<<endl;
    return 0;
}
