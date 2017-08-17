#include <iostream>
#include <cmath>
#include<vector>
#include <algorithm>
using namespace std;

/** MAX HEAP **/

class binary_heap
{
private:
    int maxSize;
    int siz;
    int*H;
public:
    binary_heap(int maxSize);
    binary_heap(int*Array,int siz,int maxSize);
    int getSize();
    int* getHeapArray();
    int parent (int i);
    int leftChild(int i);
    int rightChild(int i);
    void shiftUp(int i);
    void shiftDown(int i,int n);
    void Insert (int data);
    int extractMax ();
    int Remove (int i);
    void changePriority(int i,int data);
    void BuildHeap(int * Array,int n);
    void HeapSort(int * Array,int n);
    vector<int> partialSum(int*Array,int k,int n);
    void printHeap();

};
binary_heap::binary_heap(int maxSize)
{
    this -> maxSize =maxSize;
    this->siz=0;
    H = new int [maxSize];
}
binary_heap::binary_heap(int*Array,int siz,int maxSize)
{
    this->H=Array;
    this->siz=siz;
    this->maxSize=maxSize;
}
int binary_heap::getSize()
{
    return siz;
}
int* binary_heap::getHeapArray()
{
    return H;
}
int binary_heap::parent(int i)
{
    return floor(i/2);
}
int binary_heap::leftChild(int i)
{
    return 2*i;
}
int binary_heap::rightChild(int i)
{
    return 2*i+1;
}
void binary_heap:: shiftUp(int i)
{
    while (i>1 && H[parent(i)]<H[i])
    {
        swap(H[parent(i)],H[i]);
        i=parent(i);
    }
}
void binary_heap::shiftDown(int i ,int siz)
{
    int maxIdx=i;
    int leftChildIdx=leftChild(i);
    int rightChildIdx =rightChild(i);
    if (leftChildIdx<=siz && H[leftChildIdx]>H[maxIdx])
        maxIdx=leftChildIdx;
    if (rightChildIdx<=siz && H[rightChildIdx]>H[maxIdx])
        maxIdx=rightChildIdx;
    if (maxIdx!=i)
    {
        swap(H[maxIdx],H[i]);
        shiftDown(maxIdx,siz);
    }
}
void binary_heap::Insert (int data)
{
    if (siz==maxSize) throw "ERROR";
    siz+=1;
    H[siz]=data;
    shiftUp(siz);
}
int binary_heap::extractMax ()
{
    int ret=H[1];
    H[1]=H[siz];
    siz-=1;
    shiftDown(1,siz);
    return ret;
}
int binary_heap::Remove (int i)
{
    H[i]=INT_MAX;
    shiftUp(i);
    extractMax();
}
void binary_heap::changePriority(int i,int data)  //update value
{
    int oldData=H[i];
    H[i]=data;
    if (oldData > data) shiftDown(i,siz);
    else shiftUp(i);
}
void binary_heap::BuildHeap(int* Array,int n) //must create new binary heap where H is Array
{
    H=Array;
    siz=n;
    for (int i=n/2; i>=1; i--)
        shiftDown(i,n);
}
void binary_heap::HeapSort(int * Array,int n)
{
    BuildHeap(Array,n);
    for (int i=n; i>0; i--)
    {
        swap(Array[1],Array[i]);
        shiftDown(1,i-1);
    }
}
vector <int> binary_heap:: partialSum(int*Array,int n,int k)
{
    BuildHeap(Array,n);
    vector<int> v;
    for (int i=1; i<=k; i++)
        v.push_back(extractMax());
    reverse (v.begin(),v.end());
    return v;
}
void binary_heap::printHeap()
{
    for (int i=1; i<=siz; i++)
        cout <<H[i]<<" ";
    cout <<endl;
}
int main()
{
    binary_heap bh = binary_heap(10);
    bh.Insert(1);
    bh.Insert(4);
    bh.Insert(11);
    bh.Insert(7);
    bh.Insert(20);
    bh.Insert(5);
    bh.Insert(3);
    bh.printHeap();
    cout <<bh.getSize()<<endl;

    bh.extractMax();
    bh.printHeap();

    bh.Remove(1);
    bh.printHeap();
    cout <<bh.getSize()<<endl;

    bh.changePriority(5,20);
    bh.printHeap();

 //the heap is 1 indexed so the first element is A,B  is neglected
    int A[] = {0,1,3,9,100,8,12};
    bh.BuildHeap(A,6);
    bh.printHeap();

    int B[]= {0,1,3,9,6,10,5};
    bh.HeapSort(B,6);
    bh.printHeap();

    vector <int > v=bh.partialSum(A,6,3);
    for (vector<int>::iterator it=v.begin();it!=v.end();++it)
        cout <<*it<<" ";
    cout <<endl;
    return 0;
}
