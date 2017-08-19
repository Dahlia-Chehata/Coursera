#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

unsigned long long PolyHash(string s,long long prime,long long x)
{
    unsigned long long Hash=0;
    for (int i=s.size()-1;i>=0;i--)
        Hash=(Hash*x + s[i]) % prime;
    return Hash;
}
vector <unsigned long long>precomputeHashes(string text,string pattern,long long x,long long prime)
{
    vector <unsigned long long> H(text.size()-pattern.size()+1);
    string substring = text.substr(text.size()-pattern.size(),pattern.size());
    H[text.size()-pattern.size()] = PolyHash(substring,prime,x);
    unsigned long long y = 1;
    for (int i= 1 ;i<=pattern.size();i++)
        y=(y*x)% prime;
    for (int i= text.size()-pattern.size()-1;i>=0;i--)
     H[i]=((x*H[i+1]+text[i]-(y*text[i+pattern.size()]%prime))+prime)%prime;
    return H;
}
vector <long long> RabinKarp(string text,string pattern)
{
  vector <long long> result;
  unsigned long long prime=1000000007;  //p >> |T||P|
  unsigned long long x=263;
  unsigned long long pHash=PolyHash(pattern,prime,x);
  vector<unsigned long long> H = precomputeHashes(text,pattern,x,prime);
  for (int i=0;i<=text.size()-pattern.size();i++)
  {
      if (pHash !=H[i]) continue;
      if ((text.substr(i,pattern.size())==pattern))
        result.push_back(i);
  }
  return result;
}
int main()
{
    string text,pattern;
    cin>>pattern>>text;
    vector <long long > v=RabinKarp(text,pattern);
    for (vector<long long>::iterator it=v.begin();it!=v.end();++it)
    cout <<*it <<" ";
    return 0;
}
