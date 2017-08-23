#include <iostream>
#include <vector>
#include <string.h>
#include <string.h>
#include <stack>
using namespace std;
vector < vector <int > > adjList;
vector < vector <int > > adjListTranspose;
stack <int> stk;
void dfsUtil(int u,bool*vis,vector <vector <int>>&vec,int exp)
{
    vis[u]=true;
    for (int i=0; i<vec[u].size(); i++)
        if (!vis[vec[u][i]])
            dfsUtil(vec[u][i],vis,vec,exp);
    if (exp)stk.push(u);
}
void dfs (int n,vector <vector <int>>&vec)
{
    bool vis [n+1];
    for  (int i=1; i<=n; i++)vis[i]=0;
    for(int i=1; i<=n; i++)
        if(!vis[i])
            dfsUtil(i,vis,vec,1);
}
int SCC (int n)
{
    dfs(n,adjListTranspose);
    int scc=0;
    bool vis [n+1];
    for  (int i=1; i<=n; i++)vis[i]=0;
    while (stk.size())
    {
        int u=stk.top();
        stk.pop();
        if (!vis[u])
        {
            dfsUtil(u,vis,adjList,0);
            scc++;
        }
    }
    return scc;
}
int main()
{
    int n,m,f,s;
    cin>>n>>m;
    adjList.resize(n+1);
    adjListTranspose.resize(n+1);
    for (int i=0; i<m; i++)
    {
        cin>>f>>s;
        adjList[f].push_back(s);
        adjListTranspose[s].push_back(f);
    }
    cout <<SCC(n);
    return 0;
}
