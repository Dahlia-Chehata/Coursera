#include <iostream>
#include <vector>
using namespace std;
vector <int>computePrefixFunction(string pattern)
{
    vector <int> s (pattern.size());
    s[0]=0;
    int border = 0;
    for (int i=1; i<pattern.size(); i++)
    {
        while (border>0&&pattern[i]!=pattern [border])
            border = s[border-1];
        if (pattern[i]==pattern[border])
            border++;
//        else
//            border=0;
        s[i]=border;
    }
    return s;
}
vector <int> findAllOccurences (string text,string pattern)
{
    string str = pattern+"$"+text;
    vector <int> prefixes = computePrefixFunction(str);
    vector <int> result;
    for (int i=pattern.size()+1; i<str.size(); i++)
        if (prefixes[i]== pattern.size())
            result.push_back(i-2*pattern.size());
    return result;
}
int main()
{
    string pattern,text;
    cin>>pattern>>text;
    vector<int> result = findAllOccurences(text,pattern);
    for (vector<int>::iterator it = result.begin(); it!=result.end(); ++it)
        cout<<*it<<" ";
    return 0;
}
