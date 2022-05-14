#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<random>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<time.h>
using namespace std;

#define dictionaryFile "./dictionary.txt"

int s;
time_t CPU;

vector<string> getdictionary(int n = 0){
    ifstream file;
    vector<string> rs;
    file.open(dictionaryFile);
    if(file.is_open()){
        string line;
        while ( getline (file,line) ){
            // line.erase(remove(line.begin(), line.end(), ' '), line.end());
            if(!n  || (n and line.size() == n))
                rs.push_back(line);
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
string getHead (string s){
    return s.substr(1,2);
}

string getTail (string s){
    return s.substr(s.size()-3, 2);
}

map<string, vector<string> > make_subsequence_first (vector<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getHead(i);
        sub[str].push_back(i);
    }
    return sub;
}

map<string , int> subHEAD_INDEX(vector<string> max){
    map<string, int > sub;
    for(int i = 0; i < max.size(); i++){
        string str = getHead( max[i] );
        // cout<<i << " ";
        if(sub.count(str) == 0)
            sub[str]= i;
    }
    // cout<< endl;
    return sub;
}
map<string , int> subTAIL_INDEX(vector<string> max){
    map<string, int > sub;
    for(int i =  max.size()-1; i >= 0; i--){
        string str = getTail( max[i] );
        if(!sub[str])
            sub[str]=i;
    }
    return sub;
}
Node* circularSequence(string start,map<string, vector<string> > graph , int sizeExpected){

    Node *initNode = new Node(start);
    string headStart = getHead(start);
    vector<Node *> results;
    map<string, bool> visited; 
    
    stack<Node *> stack; 
    stack.push(initNode);
    
    //Starting DFS 
     
    while (!stack.empty()){
        Node *node = stack.top();
        if(node->size> s){
            s = node->size;
            cout<< s <<" words @ "<< double(clock() - CPU )/CLOCKS_PER_SEC<<"s"<< endl ;
        }
        stack.pop();
        string value = node->value;
        // Find the longest circular
        results.push_back(node);

         
        visited[value] = true;
        string subtring = value.substr(value.size()-3,2);

        if(node->size >= sizeExpected){
                return node;
            }
        for(int i = 0 ; i< graph[subtring].size(); i++){
            string str = graph[subtring][i];
            if(!(visited[str])){
                Node *newNode = new Node(str,node);
                stack.push(newNode);
            }
        }
    }
    Node *max = new Node("");
    for(auto i: results)
        max = (max->size > i->size)? max: i;

    return max;

}

int main(int argc, char *argv[]){
    if(argc < 3){
        cout<< "please give the valid atgument."<<endl
            << "./<exe filename> <word length> <expected maximum> | <word alphabet>"<<endl;
        exit(1);
    }
    s= 0;
    CPU = clock();
    int expectedSize = atoi(argv[2]);
    int wordLength = atoi(argv[1]);
    vector<string> dict = getdictionary(wordLength);
    cout<< "d size = "<< dict.size()<<endl;
    // string word = "blare";
    // int size = word.size();
    vector<string> max;
    int i = 0;
    // cout<< string(argv[3]).size() <<endl;
    // searching for maximum length 
    map<string, vector<string> > graph =  make_subsequence_first(dict);
    vector<string> random = vector<string>(dict.begin(), dict.end());
    random_shuffle(begin(random), end(random));// command this line if not random check
    for(auto w : random){
        if(argc == 4 && w.substr(0, string(argv[3]).size()) != string(argv[3]))
            continue;
        cout<< "Word started in '"<<w<<"'"<<endl;
        Node *temp = circularSequence(w,graph, expectedSize) ;
        if(temp->size > max.size()){
            max = convertNode(temp);
        }
        if(s >= expectedSize){
            cout<< "found "<<s<<" words in "<<double(clock() - CPU )/CLOCKS_PER_SEC << " seconds"<<endl;
            break;
        }
        cout<< "'"<<w<<"' has "<< temp->size << " words"<<endl;
        delete (temp);
    }
     
    cout<< "the max size sequence can be found "<<max.size()<<endl;
    // finding circular
    string longestSub;
    int longestSubsize = 0;
    map<string, int > subListHEAD =  subHEAD_INDEX(max);
    map<string, int > subListTAIL =  subTAIL_INDEX(max);
    if(wordLength != 4){
        for(auto i : subListTAIL){
            string key = i.first;
            if(!subListHEAD[key])
                continue;
            if(subListTAIL[key] - subListHEAD[key] > longestSubsize){
                longestSub = key;
                longestSubsize = subListTAIL[key] - subListHEAD[key];
            }
        }
    }else {
       longestSub = getHead(max[0]); 
       longestSubsize = max.size();
    }
    //output as a list
    cout<< "The best circular from this sequence has "<<longestSubsize<<" words. "<<endl;
    string filename = "circular_"+string(argv[1])+".txt";
    ofstream outfile(filename);
    if(outfile.is_open()){
        for(int i = subListHEAD[longestSub]; i <= subListTAIL[longestSub]; i++)
            outfile<<max[i]<< "\n";
    }else cout<< "CANNOT OUTPUT THE CIRCULAR SEQUENCE TO FILENAME "<< filename<<endl;
    outfile.close();
    cout<< "file finish @ "<<double(clock() - CPU )/CLOCKS_PER_SEC << " seconds"<<endl;
    return 0;
}

