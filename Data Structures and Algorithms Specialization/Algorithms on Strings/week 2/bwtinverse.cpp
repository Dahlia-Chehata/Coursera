#include <iostream>
#include <stack>
#include <vector>
using namespace std;
vector <int> sortCharacters(string &s)
{
    vector<int> order(s.size());
    vector<int> cnt (94,0);
    for (int i=0;i<s.size();i++)
        cnt [s[i]-'$']+=1;
    for (int i=1;i<94;i++)
        cnt[i]+=cnt[i-1];
    for (int i=s.size()-1;i>=0;i--)
    {
        cnt[s[i]-'$']-=1;
        order[cnt[s[i]-'$']]= i;
    }
    return order;
}
vector <int> position (vector <int> &order)
{
    vector <int> pos(order.size());
    for (int i=0;i<order.size();i++)
        pos[order[i]]=i;
    return pos;
}
string BWTinverse (string &s)
{
  vector <int> order = sortCharacters(s);
  vector <int> pos = position(order);
  stack <char> res;
  int cnt=0,i=0;
  while (cnt< s.size())
  {
      res.push(s[order[i]]);
      i=pos[i];
      cnt++;
  }
  string sol="";
  while (res.size())
  {
     sol+=res.top();
     res.pop();
  }
  return sol;
}
int main()
{
  string bwtTransform;
  cin>>bwtTransform;
  cout <<BWTinverse(bwtTransform);
     return 0;
}
