#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
vector < vector <int > > adjList;
int ret=0;
bool hasCycle(int u,bool*recStack,bool*vis)
{
    if (!vis[u])
    {
        vis[u]=true;
        recStack[u]=true;
        for (int i=0; i<adjList[u].size(); i++)
        {
            if (!vis[adjList[u][i]]&& hasCycle(adjList[u][i],recStack,vis))
                return  true;
            else if (recStack[adjList[u][i]])
                return true;
        }
    }
    recStack[u]=false;
    return false;
}
int func (int n)
{
    bool vis [n+1];
    bool recStack [n+1];
    for  (int i=1; i<=n; i++)
    {
        vis[i]=0;
        recStack[i]=0;
    }
    for(int i=1; i<=n; i++)
        if(hasCycle(i,vis,recStack))
            return true;
    return false;
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
    cout <<func(n);
}
