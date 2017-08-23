#include <iostream>
#include <vector>
#include <string.h>
#include <string.h>
#include <stack>
using namespace std;
vector < vector <int > > adjList;
stack <int> stk;
void dfsUtil(int u,bool*vis)
{
     vis[u]=true;
        for (int i=0; i<adjList[u].size(); i++)
            if (!vis[adjList[u][i]])
               dfsUtil(adjList[u][i],vis);
   stk.push(u);
}
void dfs (int n)
{
    bool vis [n+1];
    for  (int i=1; i<=n; i++)
    {
        vis[i]=0;
    }
    for(int i=1; i<=n; i++)
        if(!vis[i])
            dfsUtil(i,vis);
}
int main()
{
    int n,m,f,s;
    cin>>n>>m;
    adjList.resize(n+1);
    for (int i=0; i<m; i++)
    {
        cin>>f>>s;
        adjList[f].push_back(s);
    }
   dfs(n);
while(stk.size())
{
    cout <<stk.top()<<" ";
    stk.pop();
}
return 0;
}
