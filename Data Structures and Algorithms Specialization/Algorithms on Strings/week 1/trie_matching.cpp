#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
    int next [Letters];

    Node ()
    {
        fill (next, next + Letters, NA);
    }

    bool isLeaf () const
    {
        return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA );
    }
};

int letterToIndex (char letter)
{
    switch (letter)
    {
    case 'A':
        return 0;
        break;
    case 'C':
        return 1;
        break;
    case 'G':
        return 2;
        break;
    case 'T':
        return 3;
        break;
    default:
        assert (false);
        return -1;
    }
}
void printTrie (vector < Node* > Trie)
{

    for (int i=0; i<Trie.size(); i++)
    {
        Node* node = Trie[i];
        cout <<i<<"  ::next [A]:"<<node->next[letterToIndex('A')]<<" next [C]:"<<node->next[letterToIndex('C')]
             <<" next [G]:"<<node->next[letterToIndex('G')]<<" next [T]:"<<node->next[letterToIndex('T')]
            <<endl;
    }
}
vector <Node*> buildTrie (const vector <string>& patterns)
{
    vector <Node*> trie ;
    trie.push_back(new Node());
    for (string p : patterns)
    {
        Node* curNode = trie[0];
        for (int i=0; i<p.size(); i++)
        {
            char curSymbol = p[i];
            if (curNode->next[letterToIndex(curSymbol)]!=NA)
                curNode=trie[letterToIndex(curSymbol)];
            else
            {
                Node* newNode = new Node();
                trie.push_back(newNode);
                curNode->next[letterToIndex(curSymbol)] = trie.size()-1;
                curNode = newNode;
            }
        }
    }
    return trie;
}
int prefixTrieMatching (int idx,vector <Node*> trie,string text)
{
    char Symbol= text[0];
    Node* curNode = trie[0];
    int k=0;
    while (true)
    {
        if (curNode->isLeaf()) return idx;
        else if (curNode->next[letterToIndex(Symbol)]!=NA)
        {
            curNode=trie[curNode->next[letterToIndex(Symbol)]];
            if (k+1<text.size())Symbol= text[++k];
            else
            {
                if (curNode->isLeaf())return idx;
               break;
            }
        }
        else break;
    }
    return NA;
}
vector <int> solve ( string& text, const vector <string>& patterns)
{
    vector <int> result;
    vector <Node*> trie = buildTrie(patterns);
    int cnt=0;
    while (text.size())
    {
        int sol = prefixTrieMatching(cnt++,trie,text);
        if (sol!=-1)result.push_back(sol);
        text =text.substr(1);
    }
    return result;
}
/**********************************************************************************************************************************/
vector <int> res;
void Search(string &pat, const string& text)
{
    int M = pat.size();
    int N = text.size();
    for (int i = 0; i <= N - M; i++)
    {
        int j;
        for (j = 0; j < M; j++)
            if (text[i+j] != pat[j])
                break;

        if (j == M)
        {
            if (find(res.begin(), res.end(), i) == res.end())
                res.push_back(i);
        }
    }
}
void naiveAlg (const string& text,vector <string>& patterns)
{
    for (int i=0; i<patterns.size(); i++)
        Search(patterns[i],text);
}
int stressTesting(const string& text,int n, vector <string>& patterns)
{
    string x =text;
    vector <int> v1=solve(x,patterns);
    naiveAlg(text,patterns);
    if (equal(v1.begin(), v1.end(), res.begin()))
        cout << "success" << endl;
    else
    {
        cout <<"oops"<<endl;
        for (auto it=v1.begin();it!=v1.end();it++)
            cout <<*it<<" ";
        cout <<endl;
        for (auto it=res.begin();it!=res.end();it++)
            cout <<*it<<" ";
        cout <<endl;
        return -1;
    }
}
int main (void)
{

       /** stress testing **/
//       int n;
//       string txt,tmp;
//       vector <string> pattrns;
//       static const char alphanum[] ="ACGTAAA" ;
//       int stringLength = sizeof(alphanum) - 1;
//       while (true)
//       {
//           res.clear();
//           txt="";
//            for (int i=0;i<10;i++)
//                txt+=alphanum[rand() % stringLength];
//            cout <<txt<<endl;
//             n = rand()%5+1;
//             pattrns.resize(n);
//             for (int i=0;i<n;i++){
//                 tmp="";
//                 for (int j=0;j<5;j++)
//                 tmp+=alphanum[rand() % stringLength];
//             cout<<tmp<<endl;
//             pattrns.push_back(tmp);
//             }
//             if(stressTesting(txt,n,pattrns)==-1) break;
//       }
    string text;
    cin >> text;
    int n;
    cin >> n;
    vector <string> patterns (n);
    for (int i = 0; i < n; i++)
        cin >> patterns[i];
	vector <int> ans=solve (text,patterns);
	for (int i = 0; i < (int) ans.size (); i++)
		cout << ans[i]<<" ";

    return 0;
}
