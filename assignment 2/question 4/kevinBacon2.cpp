#include<iostream>
#include<map>
#include<string>
#include<set>
#include<fstream>
#include<queue>
using namespace std;

string getAuthor(string line){
    int i = line.find('|');
    return line.substr(0, i);
}
string getMovie(string line){
    int i = line.find('|');
    return line.substr(i+1);
}

map<string, set<string>> readFile(string filename){
    map<string, set<string>> result;
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        result[getAuthor(line)].insert(getMovie(line));
        result[getMovie(line)].insert(getAuthor(line));
    }
    file.close();
    return result;
}

struct Node
{
    string actor;
    string movie;
    int no;
    Node* parent;
    Node(string actor, string movie, int no, Node* parent): actor(actor), movie(movie), no(no), parent(parent) {  
    }
};

Node* createNode(string actor, string movie, int no, Node* p){
    return new Node( actor,  movie,  no, p);
}



Node* ActorBaconNum(map<string, set<string>> graph){
    map<string, bool> visited;
    string from = "Kevin Bacon (I)";
    visited[from] = true;
    queue<Node*> q;
    vector<Node*> all;
    q.push(createNode(from, "", 0, nullptr));
    while (!q.empty())
    {
       Node* current = q.front();
       q.pop();
       set<string> movies = graph[current->actor];
       for(auto movie : movies){
           set<string> actors = graph[movie];
           for(auto act : actors){
               if (!visited[act]){
                   Node* newNode = createNode(act, movie, (current->no) +1, current);
                   q.push(newNode);       
                   all.push_back(newNode);
                //    cout<< newNode->actor<< " "<< newNode->movie << " "<< newNode->no << endl;
                   visited[act] = true;
               }
           }
       }
    }
    Node* max = createNode("", "", 0, nullptr);
    for (Node* n: all){
        // cout<< n->no << n->actor<<endl;
        max = ((max->no) > (n->no))? max:n;
    }
    return max;
}

void printTrack(Node* n){
    while (n){
        cout<< n->actor<<  "| "<< n->movie <<"| "<< n->no << endl;
        n = n->parent;
    }
}

int main(){
    string filename = "bacon2.txt";
    string actor = "George DiCenzo";
    map<string, set<string>> graph = readFile(filename);
    Node* found =  ActorBaconNum(graph);
    cout<< "The actor "<< found->actor<< " has "<< found->no<< " Bacon numbers, and this is the largest bacon number"<<endl<<endl;
    // printTrack(found);

    return 0;
}