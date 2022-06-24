#include "heap.hpp"
#include <stdexcept>

void swap(int *x, int *y){
    int t = *x;
    *x = *y;
    *y = t;
}

bool gt(int a, int b){
    return a>b;
}
bool lt(int a, int b){
    return a<b;
}
bool Heap::deleteKey(int key){
    if(key > heap_size)
        return false;
    // convert key to (comp(INT_MAX, INT_MIN))? INT_MIN:INT_MAX;
    int i = key;
    data[i] = (comp(INT_MAX, INT_MIN))? INT_MIN:INT_MAX;
    while (i!= 0 && comp (data[parent(i)] , data[i] ))
    {
        swap(& data[i], &data[parent(i)]);
        i = parent(i);
    }
    extractRoot();
    return true;
}

int Heap::searchKey(int value, int startAt){
    if(startAt > heap_size)
        return -1;
    if(data[startAt] == value)
        return startAt;
    if (comp(value, data[startAt])){
        int key =  searchKey(value, left(startAt));
        if(key >= 0)
            return key;
        key = searchKey(value, right(startAt));
        if(key >= 0)
            return key;
    }
    return -1;
}

void Heap::Heapify(int i){
    int l = left(i);
    int r = right(i);
    int current = i;

    int dl = data[l];
    int di = data[i];

    if (l < heap_size && comp(data[i] ,data[l]) )
        current = l;
    if (r < heap_size && comp(data[current] ,data[r]) )
        current = r;
    if (current != i)
    {
        swap(&data[i], &data[current]);
        Heapify(current);
    }
}

int Heap::extractRoot(){
    int root = data[0];
    data[0] = data[heap_size-1];
    data[heap_size-1] = (comp(INT_MAX, INT_MIN))? INT_MIN:INT_MAX;
    heap_size--;
    Heapify(0);
    return root;
}

void Heap::print_heap(){
    for(int i=0; i< heap_size; i++)
        cout<< data[i]<< " ";
    cout<< endl;
}

bool Heap::insertKey(int k){
    if(isFull())
        return false;
    heap_size++;
    int i = heap_size-1;
    data[i] = k;
    while(i!= 0 && (data[parent(i)] <0 || comp(data[parent(i)], data[i]))){
        swap(&data[i], &data[parent(i)]);
        i = parent(i);
    }
    return true;
}

Heap::Heap(int n, function<bool(int, int)> comparison) :comp(comparison){
    vector<int> d(n, (comp(INT_MAX, INT_MIN))? INT_MIN:INT_MAX);
    data = d;
}

Heap::Heap(int n): comp(gt){
    vector<int> d(n, (comp(INT_MAX, INT_MIN))? INT_MIN:INT_MAX);
    data = d;
}