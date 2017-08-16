#include <iostream>
#include <string.h>
using namespace std;
int computeHeight (int n,int parent[])
{
    int height[n];
    int maxHeight=0;
    memset(height,0,sizeof height);
    for (int i=0; i<n; i++)
    {
        if (height[i]!=0) continue;
        int h=0;
        for (int j=i; j!=-1; j=parent[j]) //child-parent path
        {
            if ( height[j]!=0)
            {
                h+=height[j];
                break;
            }
            h++;
        }
        maxHeight=max(maxHeight,h);
        for (int j=i; j!=-1; j=parent[j]) //child-parent path
        {
            if (height[j]!=0)break;
             height[j]=h--;
        }
    }
    return maxHeight;
}
    int main()
    {
        int n;
        cin>>n;
        int parent[n];
        for (int i=0; i<n; i++) cin >>parent[i];
        cout<<computeHeight(n,parent);
        return 0;
    }
