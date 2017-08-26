#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;

double weight[200][200];

struct point
{
    int x,y;
};
double dist (point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct edge
{
    point a;
    point b;
    double d;
    edge(point a,point b)
    {
        this->a=a;
        this->b=b;
        this->d =dist(a,b);
    }
};

double prim (int n)
{
    double cost [n];
    bool mst[n];
    for (int i=0; i<n; i++)
    {
        cost[i]= numeric_limits<double>::max();
        mst[i] = false;
    }
    cost[0]=0;
    priority_queue <pair <double,int>, vector<pair <double,int>>,greater<pair <double,int>>> Q;
    Q.push(make_pair(0,cost[0]));
    while (Q.size())
    {
        pair <double,int> p= Q.top();
        Q.pop();
        int i=p.second;
        mst[i]=true;
        for (int j=0 ; j<n ; j++)
        {
            if (i!=j)
            {
                double d =weight[i][j];
                if( mst[j]==false && cost[j] > d)
                {
                    cost[j]=d;
                    Q.push(make_pair(cost[j],j));
                }
            }
        }
    }
    double sol=0.0;
    for (int j=0; j<n; j++)
        sol+=cost[j];
    return sol;
}
int main()
{
    int n;
    cin>>n;
    vector <point> pts (n);
    for (int i=0; i<n; i++)
        cin>>pts[i].x>>pts[i].y;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            weight[i][j]=dist(pts[i],pts[j]);
            weight[j][i]=dist(pts[i],pts[j]);
        }
    }
    cout <<fixed;
    cout <<setprecision(9)<<prim(n);
    return 0;
}
