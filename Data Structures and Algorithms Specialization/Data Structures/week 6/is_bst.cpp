#include <iostream>
#include<vector>
#include <cmath>
using namespace std;
 class BST {
     int nodeNum;
     vector<long long> key ;
     vector <int> left,right;
     bool isValid(int node,long long low ,long long high)
     {

         if (node==-1 ||!nodeNum) return true;
         if (key[node]<low || key[node]> high) return false;
         return (isValid(left[node],low,key[node])&&isValid(right[node],key[node],high));
     }
 public:
    void read()
    {
        cin>>nodeNum;
        key.resize(nodeNum);
        left.resize(nodeNum);
        right.resize(nodeNum);
        for (int i=0;i<nodeNum;i++)
            cin>>key[i]>>left[i]>>right[i];
    }
    bool isBST(int i)
    {
        return isValid(0,-pow(2,31),pow(2,31)-1);
    }

 };
int main()
{

    BST tree;
    tree.read();
    if (tree.isBST(0))
        cout <<"CORRECT";
        else
        cout <<"INCORRECT";
    return 0;
}
