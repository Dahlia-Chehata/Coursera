#include <iostream>
#include <algorithm>
using namespace std;
/*
bool compare (string a,string b)
{
  if (a.size()==b.size())
    {
        for (int i=0;i<a.size();i++)
    {
        if(a[i]==b[i])continue;
        else return a>b;
    }
    }
  else
    {
        int minsiz= min(a.size(),b.size());
        int i;
           for (i=0;i<minsiz;i++)
    {
           if(a[i]==b[i])continue;
           else return a>b;
    }
        if (a.size()>b.size())
        {
            if(a[i]>b[0])return a>b;
            else return a<b;
        }
        else
        {
            if(b[i]>a[0])return a>b;
            else return a<b;
        }
    }

}*/
bool compre (string a,string b)
{
    return a+b>b+a;
}
int main()
{
 int n;
 cin >>n;
 string a[n];
 for (int i=0;i<n;i++)
 {
     cin >>a[i];
 }
sort (a,a+n,compre);
string str="";
for (int i=0;i<n;i++)
    str+=a[i];
cout <<str<<endl;
    return 0;
}
