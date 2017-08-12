#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <cstddef>
#include <cfloat>
#include <sstream>
#include <iomanip>
using namespace std;

long compareX(pair <long,long> p1,pair <long,long> p2)
{
    if (p1.first==p2.first) return p1.second<p2.second;
    return p1.first <p2.first;
}
long compareY(pair <long,long> p1,pair <long,long> p2)
{
    if (p1.second==p2.second) return p1.first<p2.first;
    return p1.second <p2.second;
}
double dist (pair <long,long> p1,pair <long,long> p2)
{
    return sqrt(((p2.first-p1.first)*(p2.first-p1.first))+((p2.second-p1.second)*(p2.second-p1.second)));
}
double smallestDist (pair <long,long> points[],int n)
{
   double minn= DBL_MAX;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
        minn=min(minn,dist(points[i],points[j]));
    return minn;
}
 double stripClosest (pair <long,long> strip[],int siz, double d)
{
    double minimum =d;
    sort(strip,strip+siz,compareY); //el str da ytshal f 7alt est3ml el 2 functions el commented
    for (int i=0;i<siz;i++)
    {
        for (int j=i+1;j<siz&&(strip[j].second -strip[i].second)<minimum;j++)
        {
            if (dist(strip[i],strip[j])<minimum)
                minimum=dist(strip[i],strip[j]);
        }
    }
    return minimum;
}
double closeUtils(pair <long,long> P[],int n)
{
   if (n <=3) return smallestDist(P,n);
   int mid=n/2;
   pair<long,long> midpoint = P[mid];
   double d1= closeUtils(P,mid);
   double d2= closeUtils(P+mid,n-mid);
   double d = min(d1,d2);
   pair<long,long> strip[n];
   int j=0;
   for (int i=0;i<n;i++)
       if (abs(P[i].first-midpoint.first)<d)
        strip[j++]=P[i];
   return min (d ,stripClosest (strip,j,d));
}
double closePts (pair <long,long> points[],int n)
{
    sort(points,points+n,compareX);
    return closeUtils(points,n);
}
/***************************************************** O(n log n) solution ****************************************************/

double closeUtils2(pair <long,long> Px[],pair <long,long> Py[],long n)
{
   if (n <=3) return smallestDist(Px,n);
   int mid=n/2;
   pair<long,long> midpoint = Px[mid];

   pair<long,long> Py1[mid+1];
   pair<long,long> Py2[n-mid-1];
   int idx1=0,idx2=0;
   for (int i=0;i<n;i++)
   {
       if (Py[i].first<=midpoint.first)
        Py1[idx1++]=Py[i];
        else
        Py2[idx2++]=Py[i];
   }
   double d1= closeUtils2(Px,Py1,mid);
   double d2= closeUtils2(Px+mid,Py2,n-mid);
   double d = min(d1,d2);

   pair<long,long> strip[n];
   int j=0;
   for (int i=0;i<n;i++)
       if (abs(Py[i].first-midpoint.first)<d)
        strip[j++]=Py[i];
   return min (d ,stripClosest (strip,j,d));
}
double closePts2 (pair <long,long> points[],int n)
{
    pair <long,long> Px[n];
    pair <long,long> Py[n];
    for (int i=0;i<n;i++)
    {
        Px[i]=points[i];
        Py[i]=points[i];
    }
    sort(Px,Px+n,compareX);
    sort(Py,Py+n,compareY);
    return closeUtils2(Px,Py,n);
}
/***********************************************************************************************************************************/
double longSolution (pair <long,long> points[],int n)
{
double minn= DBL_MAX;
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)
        minn=min(minn,dist(points[i],points[j]));
    return minn;
}
int main()
{
   int n;
   cin>>n;
   pair <long,long> points [n];
   for (int i=0;i<n;i++)
    cin>>points[i].first>>points[i].second;
    cout <<fixed;
    cout << setprecision(9)<<closePts(points,n)<<endl;

    /** stress testing **/
// while (true)
// {
//     n=rand()%100000+10000;
//     pair <long,long> points [n];
//     for (int i=0;i<n;i++)
//     {
//         points[i].first=/*rand()%2000000001+(-1000000000)*/5;
//         points[i].second=rand()%2000000001+(-1000000000);
//     }
//     if (closePts(points,n)==longSolution(points,n))
//        cout <<"ok"<<endl;
//     else
//     {
//         cout <<"error"<<endl;
//         break;
//     }
// }
    return 0;
}
