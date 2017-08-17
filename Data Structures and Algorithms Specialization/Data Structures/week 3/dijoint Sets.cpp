#include <iostream>
#include <map>
using namespace std;
struct Node
{
    long data;
    int rnk;
    Node*parent;
};

map <long,Node*> myMap;
map<long,Node*>::iterator it;

Node*findset(Node*node)
{
    if(node!=node->parent)
        node->parent= findset(node->parent);
    return node->parent;
}

void   makeset (long data)
{
    Node *node= new Node();
    node->data= data;
    node-> parent = node;

    ///new Node (*node->parent);
    ///node.parent=&node; this is wrong it creates the same memory address for any object created
    ///since any object of type node will have the same memory address of parent
    ///it's like copy constructor
    node->rnk = 0;
    myMap.insert(pair <long,Node*>(data,node));

    /** notice**/
    //  cout<<node.data<<endl;
    // cout<<node.parent->parent->data<<endl;
    //cout<<node.parent<<endl;


}
long findset(long data)
{
    it = myMap.find(data);
    Node*node = it->second;
    //cout<< node->data<<endl;
    return findset(node)->data;

}
bool  unionset (long data1,long data2)
{

    Node *node1;
    Node *node2;

    it = myMap.find(data1);
    node1=  it->second;

    it=myMap.find(data2);
    node2= it->second;

    Node *parent1= findset(node1);
    Node *parent2= findset(node2);

    if(parent1->data==parent2->data)
    {
        return false;
    }
    else
    {
        if(parent1->rnk>=parent2->rnk)
        {
            parent1->rnk =(parent1->rnk==parent2->rnk)? parent1->rnk+1:parent1->rnk;
            parent2-> parent = parent1;
        }
        else
        {
            parent1->parent=parent2;
        }
    }
    return true;
}
int main()
{
    makeset(1);
    makeset(2);
    makeset(3);
    makeset(4);
    makeset(5);
    makeset(6);
    makeset(7);
    unionset(1,2);
    unionset(2,3);
    unionset(4,5);
    unionset(6,7);
    unionset(5,6);
    unionset(3,7);
    cout<<findset(1)<<endl;
    cout<<findset(2)<<endl;
    cout<<findset(3)<<endl;
    cout<<findset(4)<<endl;
    cout<<findset(5)<<endl;
    cout<<findset(6)<<endl;
    cout<<findset(7)<<endl;

    return 0;
}
