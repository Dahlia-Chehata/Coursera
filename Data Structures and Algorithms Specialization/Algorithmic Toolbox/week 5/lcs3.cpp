#include <iostream>

using namespace std;
 long LCS_3 ( long s1[] ,long s2[], long s3[],int n,int m,int l)
{
  long dist[n+1][m+1][l+1];

  for (int i=0;i<=n;i++)
  {
      for (int j=0;j<=m;j++)
      {
          for (int k=0;k<=l;k++)

          {
              if (!i ||!j ||!k)
              {
                  dist[i][j][k]=0;
                  continue;
              }
              if (s1[i-1]==s2[j-1]&&s2[j-1]==s3[k-1])
              {
                  dist[i][j][k]=1+ dist[i-1][j-1][k-1];
                  continue;
              }
              dist[i][j][k]=max(max(dist[i][j][k-1],dist[i-1][j][k]),dist[i][j-1][k]);
          }
     }
  }
  return dist[n][m][l];
}
int main()
{
  int n,m,l;
  cin >> n;
  long s1[n];
  for (int i=0;i<n;i++) cin >> s1[i];
  cin >>m;
  long s2[m];
  for (int i=0;i<m;i++) cin >> s2[i];
  cin >>l;
  long s3[l];
  for (int i=0;i<l;i++) cin >> s3[i];
  cout <<LCS_3(s1,s2,s3,n,m,l);


    return 0;
}
