#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
#include<stack>
using namespace std;

#define dictionaryFile "./dictionary.txt"

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

struct Node{
    string value;
    int size = 0;
    Node *parent ;
    Node(string value): value(value), parent(NULL), size(1){};
    Node(string value, Node *parent): value(value), parent(parent){
        size = parent->size +1 ;
    };
};

Node getParent(Node child){
    return *child.parent;
}

vector<string> convertNode(Node const *n){
    vector<string> rs;
    while (n->parent != nullptr )
    {   rs.push_back(n->value);
        n = n->parent;
    }
    rs.push_back(n->value);
    reverse(rs.begin(), rs.end());
    return rs;
}

void printNode(Node const *n){
    cout << n->size <<" ";
    while (n->parent != nullptr )
    {   cout << n->value <<" ";
        n = n->parent;
    }
    cout<< " " << n->value<<endl;
}

vector<string> circularSequenceBFS(string start, set<string> dict){
    int size = start.size();
    string standard = start.substr(1,2);
    

    map<string, vector<string> > graph;
    for(auto i : dict){
        string str = i.substr(1,2);
        graph[str].push_back(i);
        // if(i == "karat")
        //     cout<< str <<" "<< "baric"<<endl;
    }
    queue< Node* > qNode;
    Node *initRS = new Node(start);
    // initRS.push_back(start);
    qNode.push(initRS);
    map<string, int> visited;
    visited[start] = 1;
    vector<Node*> result;
    int maxsize = 0;
    while (!qNode.empty())
    {   
        Node *current = qNode.front();
        qNode.pop();
        string currentStr = current->value;
        // Node currentParent = *(current.parent);
        visited[currentStr] = 1;
        string substring = currentStr.substr(size-3,2);
        // cout<< "work "<< ++c;
        if(substring == standard && currentStr != start && current->size > maxsize){
            // cout<< current-> size<< endl;
            maxsize = current->size;
            printNode(current);
            result.push_back(current);
            continue;
        } 
        
        for(auto str: graph[substring]){
            if (!visited[str]){
                Node *newChild = new Node(str, current);
                qNode.push(newChild);
            }
                
        }
    }
    Node *max = new Node("") ;
    for(auto rs: result)
        max = (max->size > rs->size) ? max: rs;
    // Node maxNode = *max;
    vector<string> maxReturn;
    cout<< max->size<< endl;
    
    return maxReturn;
    
}


string getTHead (string s){
    return s.substr(1,2);
}

string getTail (string s){
    return s.substr(s.size()-3, 2);
}
map<string, vector<string> > make_subsequence_last (set<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getTail(i);
        sub[str].push_back(i);
    }
    return sub;
}

Node* circularSequence(string start, set<string> dict){
    int size = start.size();
    string standard = start.substr(1,2);
    map<string, vector<string> > graph;
    for(auto i : dict){
        string str = i.substr(1,2);
        graph[str].push_back(i);
    }
    Node *initNode = new Node(start);
    vector<Node *> results;
    map<string, bool> visited; 
    
    stack<Node *> stack; 
    stack.push(initNode);
    
    //Starting DFS 
     
    while (!stack.empty()){
        Node *node = stack.top();
        stack.pop();
        results.push_back(node);
        // cout<< stack.size() <<" " <<visited.size();
        string value = node->value; 
        visited[value] = true;
        string subtring = value.substr(value.size()-3,2);
        // if(subtring == standard){
        //         results.push_back(node);
        //     }
        for(int i = 0 ; i< graph[subtring].size(); i++){
            string str = graph[subtring][i];
            if(!(visited[str])){
                Node *newNode = new Node(str,node);
                stack.push(newNode);
            }
        }
    }
    cout<< "Result size :" << results.size()<< endl;
    Node *max = new Node("");
    for(auto i: results)
        max = (max->size > i->size)? max: i;
  

    // extend the front
    vector<string> vec = convertNode(max);
    cout<< vec.size()<<endl;
    reverse(vec.begin(), vec.end());
    graph = make_subsequence_last(dict);
    bool stop = false;
    string word = vec[vec.size()-1];
    while (!stop){
        visited[word] = true;
        stop = true;
        string subtr = getTHead(word);
        for(auto i: graph[subtr]){
            if( !visited[i] ){
                stop = false;
                vec.push_back(i);
                word = i;
                break;
            }
        }
    }
    reverse(vec.begin(), vec.end());
    cout<<vec.size()<<endl;
    for(auto v:vec)
        cout<< v<<" ";
    cout<<endl;
    return max;

}

// vector<string> front_Extended(vector rs)

int main(){
    set<string> dict = getdictionary(4);
    string word = *dict.begin();
    int size = word.size();
    vector<string> max;
    int i = 0;
    // cout<< "The number of words: "<< dict.size()<<endl;
    max = convertNode( circularSequence(word,dict) );
        

    // cout<< max.size()<<endl;
    // for(auto result: max){
        // cout<< result << " ";
    // }
    // cout<< endl;
    
    return 0;
}

