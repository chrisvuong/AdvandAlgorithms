#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
#include<climits>
using namespace std;
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

class kSmallest{
private:
    Heap *kHeap;
    Heap *nHeap;
public:
    kSmallest(vector<int> list, int k);
    ~kSmallest(){
        delete kHeap;
        delete nHeap;
    }
    void printList();
    bool deleteIndex(int i);
    int size() {return kHeap->size() + nHeap->size();}
    vector<int> ksmallest(){return kHeap->getData();}
};

kSmallest::kSmallest(vector<int> list, int k){
    // cout<< list.size() <<endl;
    this->kHeap = new Heap(k,lt);
    this->nHeap = new Heap(list.size() - k, gt);
    for(int i=0; i< k; i++){
        kHeap->insertKey(list[i]);
    }
    for(int i=k; i< list.size(); i++){
        int n = list[i];
        if(kHeap->getRoot() > n){
            int root = kHeap->extractRoot();
            kHeap->insertKey(n);
            nHeap-> insertKey(root);
        }else{
            nHeap-> insertKey(n);
        }
    }
    // kHeap->print_heap();
    // nHeap->print_heap();
    // cout<< kHeap->isFull();
}

void kSmallest::printList(){
    for(int i= 0 ; i< kHeap->size(); i++){
        cout << kHeap->getData()[i]<<" ";
    }
    for(int i= 0 ; i< nHeap->size(); i++){
        cout << nHeap->getData()[i]<<" ";
    }
    cout<< endl;
}

bool kSmallest::deleteIndex(int i){
    if(i < kHeap->size()){
        kHeap->deleteKey(i);
        kHeap->insertKey(nHeap->extractRoot());
        return true;
    } else{
        nHeap->deleteKey(i - kHeap->size());
        return true;
    }
    return false;
}

int main(){
    int n = 10;
    int k = 5;
    vector<int> v;
    for(int i = 0; i< n; i++){
        v.push_back(i);
    }
    random_shuffle(v.begin(), v.end());
    for(int i = 0; i< n; i++){
        cout<< v[i] << " ";
    }cout<< endl;
    kSmallest dataStructure(v, k);
    dataStructure.printList(); 
    cout<< dataStructure.size()<<endl;
    dataStructure.deleteIndex(12);
    dataStructure.printList();
    cout<< dataStructure.size()<<endl;
    
    auto ksmallest = dataStructure.ksmallest();
    for(auto i: ksmallest)
        cout<< i<< " ";
    cout<< endl;
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