#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <string.h>
using namespace std;
vector < unordered_map <char,int>* > buildTrie (string patterns[],int n)
{
    vector < unordered_map <char,int>* > Trie ;
    unordered_map <char,int>* root = new  unordered_map <char,int>() ;
    Trie.push_back(root);
    for (int i=0;i<n;i++)
    {
        unordered_map <char,int>* curNode = root;

        for (int j=0; j<(patterns[i]).size();j++)
        {
            char curSymbol = patterns [i][j];
            if( curNode->size() && curNode->find(curSymbol)!=curNode->end())
                   curNode = Trie[curNode->find(curSymbol)->second];
            else
            {
                unordered_map <char,int>* newNode=new unordered_map <char,int>() ;
                 Trie.push_back(newNode);
                 curNode->insert(make_pair(curSymbol,Trie.size()-1));
                 curNode=newNode;
            }
        }

    }

    return Trie;
}
void printTrie (vector < unordered_map <char,int>* > Trie)
{
    for (int i=0;i<Trie.size();i++)
    {
        unordered_map <char,int>* node = Trie[i];
        for (auto it = node->begin(); it != node->end(); ++it )
            cout <<i<<"->"<<it->second<<":"<<it->first<<endl;
    }
}
int main()
{
 int n;
 cin >> n;
 string patterns[n];
 for (int i=0;i<n;i++)
    cin>>patterns[i];
vector < unordered_map <char,int>* >Trie = buildTrie(patterns,n);
printTrie(Trie);
    return 0;
}
