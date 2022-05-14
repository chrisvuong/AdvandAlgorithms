#include<iostream>
#include <set>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#define dictionaryFile "./dictionary.txt"
using namespace std;

struct Node{
    string value;
    int size = 0;
    // set<string> visited;
    Node *parent ;
    Node(string value): value(value), parent(NULL), size(1){
        // visited.insert(value);
    };
    Node(string value, Node *parent): value(value), parent(parent){
        size = parent->size +1 ;
        // visited.insert(value);
    };
};

set<string> getdictionary(int n = 0){
    ifstream file;
    set<string> rs;
    file.open(dictionaryFile);
    if(file.is_open()){
        string line;
        while ( getline (file,line) ){
            // line.erase(remove(line.begin(), line.end(), ' '), line.end());
            if(!n  || (n and line.size() == n))
                rs.insert(line);
        }
    } else 
        throw "Unable to open dictionary.txt" ;
    file.close();
    return rs;
}

string getTHead (string s){
    return s.substr(1,2);
}

string getTail (string s){
    return s.substr(s.size()-3, 2);
}

map<string, vector<string> > make_subsequence_first (set<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getTHead(i);
        sub[str].push_back(i);
    }
    return sub;
}

map<string, vector<string> > make_subsequence_last (set<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getTail(i);
        sub[str].push_back(i);
    }
    return sub;
}

Node *tracking (map<string, vector<string> > &first, set<string> visited ,Node * node ){
    string word = node ->value; 
    visited.insert(word);
    string sub = getTail(word);//cout<< word<<endl;
    Node *max = new Node("");
    for(string i : first[sub]){
        if(visited.find(i) ==  visited.end() ){ 
            Node *newNode = new Node ( i , node);
            Node *current = tracking(first, visited,newNode);
            max = max->size > current->size ? max: current; //cout<<endl;
            delete current;
        }
    }
    cout<< max->size<< endl;
    return max;    
}



void printNode(Node const *n);
int main(){
    set<string> dictionary = getdictionary(5);
    // cout<< dictionary.size();
    string word = *dictionary.begin() ;
    map<string, vector<string> > first = make_subsequence_first (dictionary);
    map<string, vector<string> > last = make_subsequence_last(dictionary);
    set< string > visited;
    vector<Node *> sequence;
    Node *node = new Node(word);
    Node *rs = tracking(first,visited, node);
    printNode(rs);
    // for(auto w: sequence){
    //     cout<< w<<" ";
    // }cout<<endl<<endl;
    return 0;
}

void printNode(Node const *n){
    cout << n->size <<" ";
    while (n->parent != nullptr )
    {   cout << n->value <<" ";
        n = n->parent;
    }
    cout<< " " << n->value<<endl;
}