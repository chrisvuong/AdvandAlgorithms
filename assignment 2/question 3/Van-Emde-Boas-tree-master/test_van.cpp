#include "vEBTree.hpp"
#include<iostream>
#include<random>
#include<time.h>
using namespace std;
int main(){
    srand(time(NULL));
    time_t t;
    int n = 1000000;
    // int testList[n] = {-1};
    vEBTree veb(n);
    t = clock();
    for(int i = 0; i< n; i++){
        veb.insert(i);
    }
    cout<< "Time to insert "<<n << " numbers to Van Tree is "<< (clock() - t)<< " milisecs " <<endl;
    t = clock();
    for(int i = 0; i< n; i++){
        veb.erase(i);
    }
    cout<< "Time to delete "<<n << " numbers to Van Tree is "<< (clock() - t)<< " milisecs " <<endl;   
    for(int i = 0; i< n; i++){
        veb.insert(i);
    }
    t = clock();
    for(int i = 0; i< n; i++){
        veb.lookup(i);
    }
    cout<< "Time to look up "<<n << " numbers to Van Tree is "<< (clock() - t)<< " milisecs " <<endl;
    n = 10000;
    vEBTree veb1(n);
    for(int i = 0; i< n; i++){
        veb1.insert(i);
    }
    t = clock();
    int cursor = veb1.min_element();
    while (true)
    {
        cout<< cursor << " ";
        if(cursor == veb1.max_element()) break;
        cursor = veb1.successor(cursor);
    }
    cout<< endl;
    cout<< "Time to access "<<n << " numbers to Van Tree is "<< (clock() - t)<< " milisecs " <<endl;
    return 0;
}
