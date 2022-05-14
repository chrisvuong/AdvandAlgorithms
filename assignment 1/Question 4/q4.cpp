#include<iostream>
#include<vector>
using namespace std;


struct unorderList
{
    int *data;
    vector<int *> k;
    int n;
};

unorderList generate(int n){
    unorderList rs;
    rs.data = new int[n+1];
    for(int i=0 ; i<=n; i++){
        rs.data[i] = -1;
    }
    rs.n = n;
    return rs;
}

void add(unorderList &list, int n){
    if (n > list.n){
        throw "Can only store integers in the range 0 .. n";
    }
    if(list.data[n] > -1) {
        throw "Duplicate integers are not allowed in the list.";
    }
    
    list.data[n] = list.k.size(); 
    list.k.push_back(&(list.data[n])); // just save the pointer of the location
}

void deleteItem(unorderList &list, int n){
    list.data[n] = -1;
}

bool test(unorderList &list, int n){
    return list.data[n] > -1;
}

void clear(unorderList &list){
    for(int i=0; i< list.k.size(); i++){
        int n = list.k[i] - list.data;
        deleteItem(list, n);
    }
    list.k.erase(list.k.begin(), list.k.end());
}

vector<int> iteration(unorderList &list){
    vector<int> rs;
    for(int i=0; i< list.k.size(); i++){ // O(k)
        if(*(list.k[i])<0 || *(list.k[i]) != i) continue;
        rs.push_back(list.k[i] - list.data);
    }
    return rs;
}

void printList(unorderList const &list);
int main(){
    int n;
    cout<< "Please enter the size n = ";
    cin>> n;
    unorderList list = generate(n);
    printList(list); // print an empty list;
    cout<< "adding 5."<<endl;
    add(list, 5);
    cout<< "adding 3."<<endl;
    add(list, 3);
    printList(list); //[5, 3]
    try{
        cout<< "adding 3."<<endl;
        add(list, 3); //  an error message out 
    } catch (const char* msg) {
        cout<< "Error :"<< msg << endl;
    }
    try{
        cout<< "adding 100."<<endl;
        add(list, 100); //  an error message out if n < 100
    } catch (const char* msg) {
        cout<< "Error :"<< msg << endl;
    }
    cout<< "adding 6."<<endl;
    add(list, 6);
    printList(list);
    cout<< "testing 3 in the list."<<endl;
    cout<< test(list, 3)<<endl;
    cout<< "deleting 3."<<endl;
    deleteItem(list, 3);
    printList(list);
    cout<< "adding 3:"<<endl;
    add(list, 3);
    printList(list);
    cout<< "testing 4 in the list."<<endl;
    cout<< test(list, 4)<<endl;
    cout<< "clearing the list."<<endl;
    clear(list);
    printList(list);
    
    return 0;
}

// Tool function
void printList(unorderList const &list){ 
    cout<< "[";
    for(int i=0; i< list.k.size(); i++){ // O(k)
        if(*(list.k[i])<0 || *(list.k[i]) != i) continue;
        cout<< list.k[i] - list.data;
        if(i != list.k.size() -1) cout  <<", ";      
    }
    cout<< "]"<< endl;
}