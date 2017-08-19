#include <iostream>
#include <vector>
#include <algorithm>
#include<cstdlib>
#include <fstream>

using namespace std;
class HashList
{
public:
    string key;
    HashList* nxt;
    HashList(string key);
};
HashList::HashList(string key)
{
    this->key=key;
    this->nxt=NULL;
}
class hashTable
{
private:
    int bucketNum;
    HashList**LIST;
public :
    hashTable(int bucketNum);
    void add(string str);
    void Delete (string str);
    string Find(string str);
    string check (int index);
    size_t hashFunc(const string& s) const;
};
hashTable::hashTable(int bucketNum)
{
    this->bucketNum=bucketNum;
    LIST = new HashList*[bucketNum];
    for (int i=0; i<bucketNum; i++)
        LIST[i] = NULL;
}
size_t hashTable::hashFunc(const string& s) const
{
    static const size_t multiplier = 263;
    static const size_t prime = 1000000007;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash % bucketNum;
}

void hashTable::add(string str)
{
    int index=hashFunc(str);
    if (LIST[index]==NULL)
    {
        HashList*entry=new HashList(str);
        LIST[index]=entry;
    }
    else
    {
        int flag=0;
        HashList*entry=LIST[index];
        if (entry->key==str) flag=1;
        while (entry->nxt!= NULL)
        {
            if (entry->key ==str) flag=1;
            entry=entry->nxt;
        }
        if (!flag) entry->nxt=new HashList(str);
    }

}
string hashTable::Find(string str)
{
    int index=hashFunc(str);
    if (LIST[index]==NULL)
        return "no";
    else
    {
        HashList*entry=LIST[index];
        while (entry!= NULL && entry->key!=str)
            entry=entry->nxt;
        if (entry == NULL)
            return"no";
        else
            return "yes";
    }
}
void hashTable::Delete (string str)
{
    int index=hashFunc(str);
    if (LIST[index]==NULL) return;
        HashList*entry=LIST[index];
        HashList*prev=NULL;
        while (entry->nxt!= NULL&&entry->key!=str)
        {
            prev=entry;
            entry=entry->nxt;
        }
        if (entry->key==str)
        {
            if (prev==NULL)
            {
                LIST[index]= entry->nxt;
                delete entry;
            }
            else
            {
                prev->nxt=entry->nxt;
               delete entry;
            }
        }
    }
string hashTable::check (int index)
{
    if (LIST[index]==NULL) return "";
    string str="";
    HashList*entry = LIST[index];
    vector <string>v;
    while (entry->nxt!=NULL)
    {
        v.push_back(entry->key);
        entry=entry->nxt;
    }
    v.push_back(entry->key);
    reverse(v.begin(),v.end());
    for (vector<string>::iterator it=v.begin(); it!=v.end(); it++)
        str=str+*it+" ";
    return str;
}

int main()
{
    int m,N;
    cin>>m>>N;
    hashTable table=hashTable(m);
    string type,str;
    int idx;
    vector <string> v;
    for (int i=0; i<N; i++)
    {
        cin>>type;
        if (type=="add")
        {
            cin>>str;
            table.add(str);
        }
        else if (type=="del")
        {
            cin>>str;
            table.Delete(str);
        }
        else if (type=="find")
        {
            cin>>str;
            v.push_back(table.Find(str));
        }
        else
        {
            cin>>idx;
            v.push_back(table.check(idx));
        }
    }
    for (vector<string>::iterator it=v.begin(); it!=v.end(); it++)
        cout<<*it<<endl;
    return 0;
}
