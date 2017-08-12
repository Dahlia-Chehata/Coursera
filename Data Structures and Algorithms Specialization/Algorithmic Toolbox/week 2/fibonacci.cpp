#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    long long fList[46];
    fList[0]=0;
    fList[1]=1;
    for (int i=2;i<=45;i++)
        fList[i]=fList[i-1]+fList[i-2];
    cout <<fList[n];
    return 0;
}
