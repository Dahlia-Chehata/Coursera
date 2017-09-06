#include <iostream>
#include <vector>
using namespace std;

vector <int> sortCharacters(string &s)
{
    vector<int> order(s.size());
    vector<int> cnt (55,0);  //90-36+1  from $ to Z
    for (int i=0;i<s.size();i++)
        cnt [s[i]-'$']+=1;
    for (int i=1;i<55;i++)
        cnt[i]+=cnt[i-1];
    for (int i=s.size()-1;i>=0;i--)
    {
        cnt[s[i]-'$']-=1;
        order[cnt[s[i]-'$']]=i;
    }
    return order;
}
vector <int> computeCharClasses(string &s ,vector<int>&order)
{
     vector<int> classes(s.size());
     classes[order[0]]=0;
     for (int i=1;i<s.size();i++)
     {
         if (s[order[i]]!=s[order[i-1]])
            classes[order[i]]= classes[order[i-1]]+1;
         else
             classes[order[i]]= classes[order[i-1]];
     }
    return classes;
}
vector <int> SortDoubleCycleShift (string &s , int length ,vector<int>&order,vector<int>&classes)
{
        vector<int> cnt (s.size(),0);
        vector<int> newOrder (s.size());
        for (int i=0;i<s.size();i++)
            cnt[classes[i]]+=1;
        for (int i=1;i<s.size();i++)
            cnt [i]+=cnt[i-1];
        for (int i=s.size()-1;i>=0;i--)
        {
            int start =(order[i]-length+s.size())% s.size();
            cnt [classes[start]]-=1;
            newOrder[cnt[classes[start]]]= start;
        }
        return newOrder;
}
vector <int> updateClasses(int length,vector<int>&classes,vector<int> &newOrder)
{
    vector<int> newClass (newOrder.size());
    newClass[newOrder[0]]=0;
    for (int i=1;i<newOrder.size();i++)
    {
        int cur= newOrder[i];
        int prev= newOrder[i-1];
        int mid= (cur+length)% newOrder.size();
        int midPrev = (prev+length)% newOrder.size();
        if (classes[cur]!=classes[prev]||classes[mid]!=classes[midPrev])
            newClass[cur]=newClass[prev]+1;
        else
            newClass[cur]=newClass[prev];
    }
    return newClass;
}
vector <int> builsSuffixArray (string &s)
{
    vector <int> order = sortCharacters(s);
    vector <int> classes = computeCharClasses(s,order);
    int length=1;
    while(length<s.size())
    {
       order = SortDoubleCycleShift(s,length,order,classes);
       classes= updateClasses(length,classes,order);
       length*=2;
    }
    return order;
}
int main()
{
   string text;
   cin>>text;
   vector <int> suffixes = builsSuffixArray(text);
   for (vector<int> ::iterator it=suffixes.begin();it!=suffixes.end();++it)
    cout <<*it<<" ";
    return 0;
}
