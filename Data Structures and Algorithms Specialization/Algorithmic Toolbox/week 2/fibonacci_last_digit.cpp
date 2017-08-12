#include <iostream>

using namespace std;
 int  fList[10000001];
int main()
{
  int n;

  cin>>n;
  fList[0]=0;
  fList[1]=1;
  for (int i=2;i<=n;i++)
    fList[i]=(fList[i-1]+fList[i-2])%10;
      cout <<fList[n];
    return 0;
}
