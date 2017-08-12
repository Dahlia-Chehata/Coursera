#include <iostream>
#include <limits>
#include <climits>
#include <cstddef>
#include <cmath>
#include <cstddef>
#include <cfloat>
#include <sstream>
#include <iomanip>
#include <inttypes.h>

using namespace std;
//void print (int64_t M[][14],int n)
//{
//    for (int i=0;i<n;i++){
//    for (int j=0;j<n;j++)
//    {
//        cout <<M[i][j]<<",,,,";
//    }
//    cout <<endl;
//    }
//}
int64_t eval (int64_t  x,char op,int64_t  y)
{
    switch(op)
    {
        case '+' :return x+y; break;
        case '-' :return x-y;break;
        case '*' :return x*y; break;
        default  :return 0;break;
    }
}
pair <int64_t ,int64_t > MaxAndMin (string str,int64_t  M[][14],int64_t  m[][14],int i,int j)
{
    int64_t  MIN =22876792454961;   //9^14 maximum
    int64_t  MAX =-22876792454961;
    for (int k=i;k<j;k++)
         {
            char op = str[k*2+1];
           int64_t a=eval(M[i][k],op,M[k+1][j]),
                   b=eval(M[i][k],op,m[k+1][j]),
                   c=eval(m[i][k],op,M[k+1][j]),
                   d=eval(m[i][k],op,m[k+1][j]);
             MAX=  max(MAX,max(max(a,b),max(c,d)));
             MIN=  min(MIN,min(min(a,b),min(c,d)));
         }
    return make_pair(MAX,MIN);
}
int64_t  func (string str)
{
 int n=str.size()/2+1;
 int64_t  M[n][14],m[n][14];
 for (int i=0;i<n;i++)
 {
     M[i][i]=str[i*2]-'0';
     m[i][i]=str[i*2]-'0';
 }
 for (int s=1;s<n;s++)
 {
     for (int i=0;i<n-s;i++)
     {
         int j=i+s;
         pair <int64_t ,int64_t > x= MaxAndMin(str,M,m,i,j);
         M[i][j]=x.first;
         m[i][j]=x.second;
     }
 }
 return M[0][n-1]; //right top corner in the matrix
}
int main()
{
  string str;
  cin>>str;
  cout <<fixed;
  cout<<setprecision(20) <<func(str);
    return 0;
}
