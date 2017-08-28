#include <iostream>
#include <map>
using namespace std;

class TrieNode
{
public:
    map <char,TrieNode*>children;
    bool endOfPattern;
    TrieNode();
};
TrieNode::TrieNode()
{
    endOfPattern = false;
}
class Trie
{

private:
    TrieNode*root;
    void InsertRecursive(TrieNode* current,string pattern,int index);
    bool SearchRecursive(TrieNode* current,string pattern,int index);
    bool Delete(TrieNode* current,string pattern,int index);
public:
    Trie();
    void Insert(string pattern);
    void InsertRecursive(string pattern);
    bool Search (string pattern);
    bool SearchRecursive(string pattern);
    void Delete(string pattern);
};
Trie::Trie()
{
    root= new TrieNode();
}
void Trie::Insert(string pattern)
{
     TrieNode* currentNode = root;
     for (int i=0;i<pattern.size();i++)
     {
         char currentSymbol=pattern[i];
         if (currentNode->children.find(currentSymbol)!= currentNode->children.end())
            currentNode = currentNode->children.find(currentSymbol)->second;
         else
         {
             TrieNode* newNode = new TrieNode();
             currentNode->children.insert(make_pair(currentSymbol,newNode));
             currentNode=newNode;
         }
     }
     currentNode->endOfPattern=true;
}
void Trie::InsertRecursive(TrieNode* current,string pattern,int index)
{
    if (index==pattern.size())
    {
        current->endOfPattern=true;
        return;
    }
    char currentSymbol = pattern[index];
    if (current->children.find(currentSymbol) == current->children.end())
    {
        TrieNode* newNode = new TrieNode();
        current->children.insert(make_pair(currentSymbol,newNode));
    }
 InsertRecursive(current->children.find(currentSymbol)->second,pattern,index+1);
}
void Trie::InsertRecursive(string pattern)
{
 InsertRecursive(root,pattern,0);
}
bool Trie::Search (string pattern)
{
  TrieNode* currentNode = root;
  for (int i=0;i<pattern.size();i++)
  {
      char currentSymbol = pattern[i];
      if (currentNode-> children.find(currentSymbol)== currentNode->children.end())
        return false;
      currentNode=currentNode->children.find(currentSymbol)->second;
  }
  return currentNode->endOfPattern;
}
bool Trie::SearchRecursive(TrieNode* current,string pattern,int index)
{
   if (index==pattern.size()) return current->endOfPattern;
   char currentSymbol = pattern[index];
   if (current->children.find(currentSymbol)== current->children.end()) return false;
   return SearchRecursive(current->children.find(currentSymbol)->second,pattern,index+1);
}
bool Trie::SearchRecursive(string pattern)
{
    return SearchRecursive(root,pattern,0);
}
bool Trie:: Delete(TrieNode* current,string pattern,int index)
{
   if(index==pattern.size())
   {
       if (!current->endOfPattern) return false;
       current->endOfPattern = false;
       return current->children.empty();
   }
   char currentSymbol=pattern[index];
   if (current->children.find(currentSymbol)== current ->children.end())
    return false;

   bool flag=Delete(current->children.find(currentSymbol)->second,pattern,index+1);
   if (flag)
   {
       current->children.erase(current->children.find(currentSymbol));
       return current->children.empty();
   }
   return false;
}
void Trie:: Delete(string pattern)
{
   Delete(root,pattern,0);
}
int main()
{
    Trie tree = Trie();
    tree.Insert("banana");
    tree.Insert("ban");
    tree.Insert("b");
    tree.Insert("apple");
    cout <<tree.Search("apple")<<endl;
    cout <<tree.SearchRecursive("ban")<<endl;
    tree.Delete("b");
    tree.Delete("boolean");
    cout <<tree.Search("ban")<<endl;
    tree.Delete("ban");
    cout <<tree.Search("ban")<<endl;
    tree.Delete("ban");
    cout <<tree.Search("ban")<<endl;

    return 0;
}
