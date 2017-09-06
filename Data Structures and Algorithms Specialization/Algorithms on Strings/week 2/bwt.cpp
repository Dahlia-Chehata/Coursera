#include <iostream>
#include <vector>
#include <set>
using namespace std;
vector <int> SortCharacters (string &s)
{
    vector <int> order(s.size());
    vector<int>count (55,0);
    for (int i=0;i<s.size();i++)
        count [s[i]-'$']++;
    for (int i=1;i<55;i++)
        count[i]+=count[i-1];
    for (int i=s.size()-1;i>=0;i--)
    {
        count[s[i]-'$']--;
        order[count[s[i]-'$']] = i;
    }
    return order;
}
vector <int> computeClass(string &s ,vector<int> &order)
{
  vector <int> classes(s.size(),0);
  classes[order[0]]=0;
  for (int i=1;i<s.size();i++)
  {
      if (s[order[i]]==s[order[i-1]])
        classes[order[i]]=classes[order[i-1]];
      else
        classes[order[i]]=classes[order[i-1]]+1;
  }
  return classes;
}
vector<int> SortDoubleCycleShift(int length,string &s,vector<int> &order,vector<int> &classes)
{
    vector<int> newOrder(s.size());
    vector<int> count (s.size(),0);
    for (int i=0;i<s.size();i++)
        count[classes[i]]++;
    for (int i=1;i<s.size();i++)
        count [i]+=count [i-1];
    for (int i=s.size()-1;i>=0;i--)
    {
        int start = (order[i]-length+s.size()) % s.size();
        count [classes[start]]--;
        newOrder[count [classes[start]]] = start;
    }
    return newOrder;
}
vector <int> updateClass (int length,vector<int> &newOrder,vector<int> &classes)
{
   vector <int> newClass(newOrder.size());
   newClass[newOrder[0]]=0;
   for (int i=1;i<newOrder.size();i++)
   {
       int cur = newOrder[i];
       int prev= newOrder[i-1];
       int mid = (cur+length)% newOrder.size();
       int midPrev=(prev+length)% newOrder.size();
       if (classes[cur]!=classes[prev]|| classes[mid]!=classes[midPrev])
        newClass[cur]=newClass[prev]+1;
       else
        newClass[cur]=newClass[prev];
   }
   return newClass;
}
vector <int> BuildSuffixArray (string &s)
{
    vector <int> order,classes;
    order = SortCharacters(s);
    classes = computeClass(s,order);
    int length=1;
    while (length< s.size())
    {
        order = SortDoubleCycleShift(length,s,order,classes);
        classes = updateClass(length,order,classes);
        length*=2;
    }
    return order;
}
 vector <char> BWT (string &s)
 {
     vector <char> res;
     vector <int> suffixArray = BuildSuffixArray(s);
     for (vector <int> ::iterator it = suffixArray.begin();it!=suffixArray.end();++it)
     {
         int startIdx = *it;
         int suffixlength = s.size() - startIdx;
         res.push_back(s[((s.size()-1-suffixlength)+s.size())%s.size()]);
     }
     return res;
 }
int main()
{

   string text;
   cin>>text;
   vector <char> res = BWT(text);
   for (vector <char> ::iterator it = res.begin();it!=res.end();++it)
      cout <<*it;
    return 0;
}
