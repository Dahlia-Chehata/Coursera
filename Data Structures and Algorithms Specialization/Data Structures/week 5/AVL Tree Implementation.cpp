#include <iostream>
#include <cstdlib>
using namespace std;
class Node
{
private:
    Node*RebalanceRight();
    Node* RebalanceLeft();
public:
    int key;
    int height;
    int balanceFactor;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    Node();
    Node(int key,Node*parent);
    ~Node();
    bool isLeaf();
    bool isLeftChild();
    bool isRightChild();
    Node* RotateRight();
    Node* RotateLeft();
    Node* Rebalance();
    void AdjustHeight();
};
Node::Node()
{
    this->key=-1;
    this->height=0;
    this->balanceFactor=0;
    this->parent=NULL;
    this->leftChild=NULL;
    this->rightChild=NULL;
}
Node::Node(int key,Node*parent)
{
    this->key=key;
    this->height=0;
    this->balanceFactor=0;
    this->parent=parent;
    this->leftChild=NULL;
    this->rightChild=NULL;
}
Node::~Node() {}
bool Node::isLeftChild()
{
    return (this==parent->leftChild);
}
bool Node::isRightChild()
{
    return (this==parent->rightChild);
}
bool Node::isLeaf()
{
    return ((leftChild==NULL)&&(rightChild ==NULL));
}
Node* Node:: RotateRight()
{
    Node*p= parent;
    Node*Y =leftChild;
    Node*B =leftChild->rightChild;
    if (p!=NULL)
    {
        if(isLeftChild()) p->leftChild = Y;
        else p->rightChild =Y;
    }
    Y->parent =p ;
    if (B!=NULL)
        B->parent =this;
    leftChild =B;
    Y->rightChild =this;
    this->parent =Y;
    AdjustHeight();
    Y->AdjustHeight();
    return Y;
}
Node* Node::RotateLeft()
{
    Node*p=parent;
    Node*Y= rightChild;
    Node*B= rightChild ->leftChild;
    if (p!=NULL)
    {
        if(isLeftChild()) p->leftChild = Y;
        else p->rightChild =Y;
    }
    Y->parent =p ;
    if (B!=NULL)
        B->parent=this;
    rightChild=B;
    Y->leftChild=this;
    parent =Y;
    AdjustHeight();
    Y->AdjustHeight();
    return Y;
}
Node* Node::RebalanceRight()
{
    Node* L= leftChild;
    if (L->balanceFactor>=0)
        return RotateRight();
    else
    {
        leftChild=L->RotateLeft();
        return RotateRight();
    }
}
Node* Node::RebalanceLeft()
{
    Node* R =rightChild;
    if (R->balanceFactor <= 0)
        return RotateLeft();
    else
    {
        rightChild= R->RotateRight();
        return RotateLeft();
    }
}
void Node::AdjustHeight()
{
    int leftHeight=-1,rightHeight=-1;
    if (leftChild!=NULL) leftHeight = leftChild->height;
    if (rightChild!=NULL) rightHeight = rightChild->height;
    height=1+max(leftHeight,rightHeight);
    balanceFactor=leftHeight-rightHeight;
}
Node* Node::Rebalance()
{
    AdjustHeight();
    if ( balanceFactor <-1) return RebalanceLeft();
    else if (balanceFactor>1)return RebalanceRight();
    return this;
}
class AVLTree
{
private:

    Node* leftDesendant(Node* node);
    Node* Delete(int key,Node* Root );
    Node* Insert(int key,Node* Root);
    Node* BSTMergeWithRoot(Node* R1,Node* R2,Node* T);

public:
    Node* root;
    AVLTree();
    AVLTree(Node* root);
    int getHeight();
    void InOrderTraversal(Node*root);
    void Insert(int key);
    void Delete(int key);
    pair <bool,Node*> Find (int key,Node*root);
};
AVLTree::AVLTree()
{
    root=NULL;
}
AVLTree::AVLTree(Node* root)
{
    this->root=root;
}
int AVLTree::getHeight()
{
    return root->height;
}
Node* AVLTree::leftDesendant(Node* node)
{
    if (node->leftChild ==NULL) return node;
    return leftDesendant(node->leftChild);
}
pair <bool,Node*> AVLTree::Find (int key,Node*root)
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
void InOrderTraversal(Node*root)
{
    if (root==NULL) return;
    InOrderTraversal(root->leftChild);
    cout <<root->key <<" ";
    InOrderTraversal(root->rightChild);
}
Node* AVLTree:: Insert(int key,Node*Root)
{
    if (Root == NULL)  Root = new Node(key,NULL);
    if(key > Root->key)
    {
        if (Root-> rightChild == NULL) Root->rightChild = new Node(key,Root);
        else Root->rightChild=Insert(key,Root->rightChild);
    }
    else if (Root->key>=key)
    {
        if (Root->leftChild==NULL) Root->leftChild = new Node(key,Root);
        else Root->leftChild=Insert(key,Root->leftChild);
    }
    return root=Root->Rebalance();
}
void AVLTree::Insert(int key)
{
    Insert(key,root);
}

Node* AVLTree::Delete(int key,Node* Root)
{
    if (Root==NULL) return Root;
    if (key <Root->key) Root->leftChild =Delete(key,Root->leftChild);
    else if (key> Root->key) Root->rightChild =Delete(key,Root->rightChild);
    else
    {
        Node*ret;
        if (Root->leftChild==NULL)
        {
            ret=Root->rightChild;
            free(Root);
            return ret;
        }
        else if (Root->rightChild==NULL)
        {
            ret=Root->leftChild;
            free(Root);
            return ret;
        }
        else
        {
            Node* tmp= leftDesendant(Root->rightChild); //find next element according to in-order traversal
            Root->key =tmp->key;
            Root->rightChild=Delete(tmp->key,Root->rightChild);
        }
    }
    return Root->Rebalance();
}
void AVLTree::Delete(int key)
{
    root=Delete(key,root);
}
Node* BSTMergeWithRoot(Node* R1,Node* R2,Node* T)
{
    T->leftChild =R1;
    T->rightChild=R2;
    R1->parent= T;
    R2->parent= T;
    return T;
}
Node* AVLMergeWithRoot(Node* R1,Node* R2,Node* T)
{
    if (R1 == NULL )
    {
     if (R2==NULL)return NULL;
     else return R2;
    }
    else if (R2 == NULL)
    {
        if (R1==NULL)return NULL;
        else return R1;
    }
    if (abs(R1->height-R2->height)<=1)
    {
        T = BSTMergeWithRoot(R1,R2,T);//T->key
        T->AdjustHeight();
        return T;
    }
    else if (R1->height>R2->height)
    {
        Node* newR1 = AVLMergeWithRoot(R1->rightChild,R2,T);
        R1->rightChild=newR1;
        newR1->parent=R1;
        return R1->Rebalance();
    }
    else
    {
        Node* newR2=AVLMergeWithRoot(R1,R2->leftChild,T);
        R2->leftChild=newR2;
        newR2->parent=R2;
        return R2->Rebalance();
    }
}
/**merge 2 AVL trees where all keys in R1 smaller than those of R2**/
Node* AVLMerge(AVLTree R1,AVLTree R2)
{
    Node* T = R1.Find(INT_MAX,R1.root).second;
    Node* T1 = new Node(T->key,NULL);
    R1.Delete(T->key);
    return AVLMergeWithRoot(R1.root,R2.root,T1);
}
pair <Node*,Node*>Split(Node* root,int key)
{
    if (root==NULL)
    {
        Node* x =NULL;
        Node* y =NULL;
        return make_pair(x,y);
    }
    if (key <=root->key)
    {
       pair <Node*,Node*> R =Split(root->leftChild,key);
       Node* R3= AVLMergeWithRoot(R.second,root->rightChild,root);
       return make_pair(R.first,R3);
    }
    else
    {
         pair <Node*,Node*> R =Split(root->rightChild,key);
         Node* R3= AVLMergeWithRoot(root->leftChild,R.first,root);
         return make_pair(R3,R.second);
    }
}
int main()
{
    Node root1 = Node(100,NULL);
    AVLTree tree1 = AVLTree(&root1);
    tree1.Insert(50);
    tree1.Insert(300);
    tree1.Insert(70);
    tree1.Insert(20);
    InOrderTraversal(tree1.root);
    cout <<endl;

     Node root2 = Node(80,NULL);
     AVLTree tree2 = AVLTree(&root2);
     tree2.Insert(40);
     tree2.Insert(120);
     InOrderTraversal(tree2.root); //combinedRoot->key
      cout<<endl;

     Node* combinedRoot= AVLMerge(tree1.root,tree2.root);
     InOrderTraversal(combinedRoot);
     cout<<endl;
     
    return 0;
}
