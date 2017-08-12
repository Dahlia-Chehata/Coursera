#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int n;
  cin>>n;
  long a[n],b[n];
  for (int i=0;i<n;i++)
  {
      cin>>a[i];
  }
  for (int i=0;i<n;i++)
  {
      cin>>b[i];
  }
  sort (a,a+n);
  sort (b,b+n);
  long sol=0;
  for (int i=0;i<n;i++)
    sol+=a[i]*b[i];
  cout<<sol;
    return 0;
}
