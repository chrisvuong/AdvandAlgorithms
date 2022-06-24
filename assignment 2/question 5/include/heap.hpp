#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
#include<climits>
// #include<set>

using namespace std;
void swap(int *x, int *y);
bool gt(int a, int b);
bool lt(int a, int b);
class Heap{
    vector<int> data; 
    function<bool(int, int)> comp;
    int heap_size =0;
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }
    public:
    int size(){return heap_size;}
    bool isFull(){return heap_size == data.size();}
    bool insertKey(int k);
    Heap(int n);
    Heap(int n, function<bool(int, int)> f);
    int extractRoot();
    void print_heap();
    void Heapify(int i);
    int searchKey(int value,int startAt = 0);
    int getRoot(){return data[0];}
    int getValue(int key){ return data[key];}
    bool deleteKey(int key);
    vector<int> getData(){return data;}
};