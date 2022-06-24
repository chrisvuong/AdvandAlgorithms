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



Node* ActorBaconNum(map<string, set<string>> graph, string actor1, string actor2){
    map<string, bool> visited;
    visited[actor1] = true;
    queue<Node*> q;
    q.push(createNode(actor1, "", 0, nullptr));
    while (!q.empty())
    {
       Node* current = q.front();
       q.pop();
    //    cout<< current->actor<<endl;
       if(current->actor == actor2){
        //    cout<< current->actor<< " "<< current->movie <<" "<< current->no ;
           return current;
       }
       set<string> movies = graph[current->actor];
       for(auto movie : movies){
           set<string> actors = graph[movie];
           for(auto act : actors){
               if (!visited[act]){
                   q.push(createNode(act, movie, (current->no) +1, current));
                //    cout<< act<< " "<< movie << " "<< (current->no) +1 << endl;
                   visited[act] = true;
               }
           }
       }
    }
    return nullptr;
}

void printTrack(Node* n){
    while (n){
        cout<< n->actor<<  "| "<< n->movie <<"| "<< n->no << endl;
        n = n->parent;
    }
}

int main(){
    string filename = "bacon3.txt";
    string actor1 = "Mieczyslaw Winkler";
    string actor2 = "W.G. Fay";
    map<string, set<string>> graph = readFile(filename);
    cout<< "a graph of "<< graph.size()<< " elements created"<<endl;
    Node* found =  ActorBaconNum(graph, actor1, actor2);
    if(!found)
        found =  ActorBaconNum(graph, actor2, actor1);
    if(found){
        cout<< "The actor "<< actor1<< " has "<< found->no<< " Bacon numbers to actor "<< actor2<<endl<<endl;
        printTrack(found);
    }else
        cout<< "cannot find any relation between two actors"<<endl;

    return 0;
}