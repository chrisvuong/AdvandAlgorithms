#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

#define dictionaryFile "./dictionary.txt"

set<string> getdictionary(int n = 0){
    ifstream file;
    set<string> rs;
    file.open(dictionaryFile);
    if(file.is_open()){
        string line;
        while ( getline (file,line) ){
            if(!n  || (n and line.size() == n))
                rs.insert(line);
        }
    } else 
        throw "Unable to open dictionary.txt" ;
    file.close();
    return rs;
}

vector<string> shortestChainLen( string source, string target, set<string> &dict){
    map<string, vector<string>> graph; // assump this is a graph, key is the node and vector is the edges 
    for(int i=0 ; i< source.size(); i++){ // generate the node (a node can have many substring) of the source word
        string str = source.substr(0,i)+ " " +source.substr(i+1);
        graph[str].push_back(source);
    }
    // checking for all the word in the dictionary
    for(auto word: dict){
        for(int i=0 ; i< word.size(); i++){
            string str = word.substr(0,i)+ " " +word.substr(i+1);
            graph[str].push_back(word);
        }
    }

    //Because every edge has the same cost, let use BFS 
    queue<pair<string, vector<string> >> q; // string is the value of node and int is the cost of that not from the source
    map<string, int> visited; // for bfs we eliminate the visited node, so we won't loop again to the edge we found
    vector<string> sourceV;
    sourceV.push_back(source);
    q.push(make_pair(source, sourceV)); // the first node is the source node
    visited[source] = 1;

    // let travel
    while (!q.empty()){
        pair<string,vector<string>> current = q.front();
        q.pop();
        string word = current.first;
        vector<string> distance = current.second;
        if (word == target)
            return distance; // return when meet the distance
        for(int i=0 ; i< word.size(); i++){
            string str = word.substr(0,i)+ " " + word.substr(i+1);
            vector<string> edgesOfStr = graph[str];
            for(auto edge: edgesOfStr){
                if( !visited[edge] ){
                    visited[edge] = 1;
                    vector<string> newDistance = distance;
                    newDistance.push_back(edge);
                    q.push(make_pair(edge, newDistance ));
                }
            }
        }
    }
    return sourceV; // return the source path only without the target 
}

int main(int argc, char *argv[]){
    if (argc < 3){
        cout<< "please giving the source and target"<<endl;
        exit(1);
    }
    string source = argv[1];
    string target = argv[2];

    transform(source.begin(), source.end(), source.begin(), [](unsigned char c) {
        return tolower(c);
    });
    transform(target.begin(), target.end(), target.begin(), [](unsigned char c) {
        return tolower(c);
    });
    
    if(target.size() != source.size()){
        cout<< "target and source must have the same size";
        exit(1);
    }
    int size = source.size();
    set<string> dict = getdictionary(size);
    vector<string> shortestPath = shortestChainLen(source, target, dict);
    for(auto p: shortestPath){
        cout<< p << " ";
    }
    cout<<endl;
    cout<< "Total of "<< shortestPath.size() -1<< " steps"<<endl;
    // cout<<dict.size();
    return 0;
}

