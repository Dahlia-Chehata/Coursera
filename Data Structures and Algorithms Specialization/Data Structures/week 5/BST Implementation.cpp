#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
using namespace std;
class Node
{
public:
    int key;
    Node*parent;
    Node*leftChild;
    Node*rightChild;
    Node();
    Node(int key,Node*parent);
    ~Node ();
    bool isLeftChild(Node* left);
    bool isRightChild(Node* right);
    bool isLeaf();
};
Node::Node()
{
    this ->key = -1;
    this ->parent=NULL;
    this-> leftChild =NULL;
    this->rightChild = NULL;
}
Node::Node(int key,Node*parent)
{
    this ->key=key;
    this ->parent=parent;
    this-> leftChild =NULL;
    this->rightChild = NULL;
}
Node::~Node() {}
bool Node::isLeftChild(Node*parent)
{
    return (this==parent ->leftChild);
}
bool Node::isRightChild(Node* right)
{
    return (this==parent->rightChild);
}
bool Node::isLeaf ()
{
    return (this->leftChild == NULL && this->rightChild ==NULL);
}
/******************************************************************************************************************/
class BST
{
    Node* root;

public:
    BST();
    BST(Node* root);
    pair <bool, Node*>Find (int key,Node*root);
    Node*next (Node*node);
    Node*leftDesendant(Node*node);
    Node*RightAncestor(Node*node);
    vector <Node*> RangeSearch(int x,int y,Node* root);
    void Insert (int key, Node* root);
    Node* Delete (Node* node,int key);
    void InOrderTraversal(Node* root);
    void PostOrderTraversal(Node* root);
    void PreOrderTraversal(Node* root);
    void BFS (Node* root);
};
BST::BST()
{
    root = new Node;
}
BST::BST(Node* root)
{
    this->root=root;
}
//  return the required value if found or the parent root if not
pair <bool,Node* > BST::Find (int key,Node*root)
{
    if(root->key==key) return make_pair(1,root);
    else if (root->key > key)
    {
        if (root->leftChild !=NULL)
            return Find(key,root->leftChild);
        return make_pair(0,root);
    }
    else
    {
        if (root->rightChild!=NULL)
            return Find(key,root->rightChild);
        return make_pair(0,root);
    }
}
Node* BST::leftDesendant(Node* node)
{
    if (node->leftChild ==NULL) return node;
    return leftDesendant(node->leftChild);
}
Node* BST::RightAncestor(Node* node)
{
    if (node == NULL) return NULL; // if the node has the largest value in the tree
    if (node->key < node->parent->key) return node->parent;
    return RightAncestor(node->parent);
}

Node* BST::next(Node* node)
{
    if (node-> rightChild!=NULL)
        return leftDesendant(node->rightChild);
    else return RightAncestor(node);
}
vector <Node*> BST::RangeSearch(int x,int y,Node* root)
{
    vector <Node*> v ;
    pair < bool,Node*>p = Find(x,root);
    if (!p.first) throw "x not found !!!";
    Node* node = p.second;
    while (node ->key <= y)
    {
        if(node->key >= x) v.push_back(node);
        node =next(node);
    }
    return v;
}
void BST::Insert (int key, Node* root)
{
    pair < bool,Node*> p = Find(key,root);
    Node*node = p.second;
    Node* child = new Node(key,node);
    if (!p.first) //not found a similar key
    {
        if (node->key > key)node ->leftChild = child;
        else node ->rightChild = child;
    }
    else //found a similar key : insert the node with same key as a left child
    {
        Node* leftSubtree = node->leftChild;
        child ->leftChild =leftSubtree;
        node->leftChild =child;
        leftSubtree ->parent =child;
    }
}
Node* BST::Delete (Node* root,int key)
{
   if (root==NULL) return root;
   if (key < root->key) root->leftChild = Delete(root->leftChild,key);
   else if (key > root->key)root->rightChild=Delete(root->rightChild,key);
   else  // found the node to be deleted
   {
       //node with one child or none
        Node*ret;
       if (root->leftChild==NULL)
       {
           ret=root->rightChild;
           free(root);
           return ret;
       }
       else if (root->rightChild==NULL)
       {
           ret=root->leftChild;
           free(root);
           return ret;
       }
       Node* tmp= leftDesendant(root->rightChild); //find next element according to in-order traversal
       root->key =tmp->key;
       root->rightChild=Delete(root->rightChild,tmp->key);
   }
   return root;
}
/** DFS **/
void BST::InOrderTraversal(Node*root)
{
    if (root==NULL) return;
    InOrderTraversal(root->leftChild);
    cout <<root->key <<" ";
    InOrderTraversal(root->rightChild);
}
void BST::PostOrderTraversal(Node* root)
{
    if (root==NULL) return;
    PostOrderTraversal(root->leftChild);
    PostOrderTraversal(root->rightChild);
    cout <<root->key <<" ";
}
void BST::PreOrderTraversal(Node* root)
{
    if (root==NULL) return;
    cout <<root->key <<" ";
    PreOrderTraversal(root->leftChild);
    PreOrderTraversal(root->rightChild);
}
//level traversal
void BST::BFS (Node* node)
{
    if (node==NULL) return;
    queue <Node*> Q;
    Q.push(node);
    while (Q.size())
    {
        Node*x =Q.front();
        Q.pop();
        cout <<x->key <<" ";
        if (x->leftChild !=NULL) Q.push(x->leftChild);
        if (x->rightChild!=NULL) Q.push(x->rightChild);
    }
}
int main()
{
    Node root = Node(3,NULL);
    BST tree  = BST(&root);
    tree.Insert(10,&root);
    tree.Insert(1,&root);
    tree.Insert(6,&root);
    tree.Insert(14,&root);
    tree.Insert(4,&root);
    tree.Insert(7,&root);
    tree.Insert(13,&root);

    //test tree walking
    tree.InOrderTraversal(&root);
    cout<<endl;
    tree.PreOrderTraversal(&root);
    cout<<endl;
    tree.PostOrderTraversal(&root);
    cout<<endl;
    tree.BFS(&root);
    cout<<endl;

    tree.Insert(2,&root);
    tree.InOrderTraversal(&root);
    cout<<endl;

    //test find() , next()
    pair <bool,Node*> x =tree.Find(6,&root);
    if (x.first) cout <<"found 6"<<endl;
    else  cout <<"not found"<<endl;
    cout <<tree.next(x.second)->key <<endl;

    //test range()
    vector <Node*> lista = tree.RangeSearch(2,10,&root);
    for (vector <Node*>::iterator it=lista.begin();it!=lista.end();++it)
     cout <<(*it)-> key <<" ";
    cout<<endl;

    tree.Delete(&root,6);
    tree.InOrderTraversal(&root);
    cout<<endl;

    return 0;
}
