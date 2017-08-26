#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

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
    int idxA,idxB;
    point a;
    point b;
    double d;
    edge(int idxA,int idxB,point a,point b)
    {
        this->idxA=idxA;
        this->idxB=idxB;
        this->a=a;
        this->b=b;
        this->d =dist(a,b);
    }
};
vector <edge> edges;
class dijointSet
{
public:
    int n;
    int*parent;
    int*rnk;
    dijointSet(int n);
    void makeSet();
    int Find (int i);
    void Union (int i,int j);

};
dijointSet::dijointSet(int n)
{
    this->n =n;
    parent=new int [n];
    rnk = new int [n];
}
void dijointSet::makeSet()
{
    for (int i=0; i<n; i++)
    {
        parent[i]=i;
        rnk[0]=0;
    }
}
int dijointSet:: Find (int i)
{
    if (i!=parent[i])
        parent[i]=Find(parent[i]);
    return parent[i];
}
void dijointSet::Union (int i,int j)
{
    int parent1=Find(i);
    int parent2=Find(j);
    if (parent1==parent2)
        throw exception();
    if (rnk[parent1]>rnk[parent2])
        parent[parent2]=parent1;
    else
    {
        parent[parent1]=parent2;
        if (rnk[parent1]==rnk[parent2])
            rnk[parent2]++;
    }
}
bool compare (edge a,edge b)
{
    return a.d <b.d;
}
double kruskal(int n,int k)
{
    dijointSet ds =dijointSet(n);
    sort(edges.begin(),edges.end(),compare);
    ds.makeSet();
    int cnt=n;
    for (vector <edge>::iterator it=edges.begin(); it!=edges.end(); ++it)
    {
        edge E = *it;
        if (ds.Find(E.idxA)!=ds.Find(E.idxB))
        {
            ds.Union(E.idxA,E.idxB);
            cnt --;
            if (cnt==k-1) return E.d;
        }
    }
}
int main()
{
    int n,k;
    cin>>n;
    vector <point> pts (n);
    for (int i=0; i<n; i++)
        cin>>pts[i].x>>pts[i].y;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            edges.push_back(edge(i,j,pts[i],pts[j]));
        }
    }
    cin>>k;


//        sort(edges.begin(),edges.end(),compare);
//        for (vector <edge>::iterator it=edges.begin(); it!=edges.end(); ++it)
//          cout <<"point"<<(*it).idxA<<" point"<<(*it).idxB<<" distance "<<(*it).d<<endl;

    cout <<fixed;
    cout <<setprecision(9)<<kruskal(n,k);
    return 0;
}
