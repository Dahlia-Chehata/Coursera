#include <iostream>

using namespace std;
int edit (string str1,string str2)
{
    int dist [str1.size()+1][str2.size()+1];
     dist[0][0]=0;
    for (int i=1;i<=str1.size();i++) dist[i][0]=i;
    for (int i=1;i<=str2.size();i++) dist[0][i]=i;

    for (int i=1;i<=str1.size();i++)
    {
        for (int j=1;j<=str2.size();j++)
        {
            if (str1[i-1]==str2[j-1]) dist[i][j]=dist[i-1][j-1];
           else dist[i][j]=min (min(dist[i][j-1]+1,dist[i-1][j]+1),dist[i-1][j-1]+1);
        }
    }

    return dist[str1.size()][str2.size()];
}
int main()
{
  string str1,str2;
  cin >>str1>>str2;
  cout<<edit(str1,str2);
    return 0;
}
