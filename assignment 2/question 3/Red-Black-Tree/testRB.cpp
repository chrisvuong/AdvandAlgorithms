#include<iostream>
#include "RBTree.h"
#include <time.h>
#include<random>
using namespace std;
int main(){
    // insertion test
    RBTree tree;
    time_t t = clock();
    int n = 1000000;
    for(int i=0; i< n; i++){
        tree.insertValue(i);
    }
    cout<< "insert "<< n << " number in the tree, after "<< clock()-t<< " milisec" <<endl;
    // deletion test 
    RBTree tree1;
    // n = 100000;
    for(int i=0; i< n; i++){
        tree1.insertValue(i);
    }
    t = clock();
    for(int i=0; i< n; i++){
        tree1.deleteValue(i);
    }
    cout<< "delete "<< n << " number in the tree, after "<< clock()-t<< " milisec" <<endl;
    RBTree tree2;
    n = 10000;
    for(int i=0; i< n; i++){
        tree2.insertValue(i);
    }
    t = clock();
    tree2.inorder();
    cout<< "access "<< n << " number in the tree, after "<< clock()-t<< " milisec" <<endl;
    return 0;
}