#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include<time.h>
using namespace std;

char getType(string l){
    return l[0];
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

vector<string> split(string str){
    vector<string> result;
    stringstream ss(str);
    while (ss.good())    {
        string substr;
        getline(ss, substr, ' ');
        if (substr.size())
            result.push_back(substr);
    }
    return result;
}


class Graph{
    private:
    set<int> *graph;
    int V;
    set<pair<int,int>> edges;
    int E;
    bool* pass;
    public:
    Graph(string filename){
        ifstream file(filename);
        string line;
        // Read file and generate graph
        time_t t = clock();
        while(getline(file, line)){
            char type = getType(line);
            if (type == 'p'){
                vector<string> slt = split(line);
                V = stoi(slt[2])+1;
                E = stoi(slt[3])+1;
                cout<< "a graph of "<< V << " vertexes "<<E<<" edges is created."<<endl;
                graph = new set<int>[V];
                for(int i= 1; i< V; i++){
                    for(int j= 1; j< V; j++){
                        if (i!=j){
                            graph[i].insert(j);
                            if(i<j)
                                edges.insert(make_pair(i,j));
                            else
                                edges.insert(make_pair(j,i));
                        }
                    }
                }
                // edges = new pair<int,int>[E];
            } else if(type == 'e'){
                vector<string> slt = split(line);
                int from = stoi(slt[1]);
                int to = stoi(slt[2]);
                if(from > to)
                    swap(from,to);
                graph[from].erase(to);
                graph[to].erase(from);
                edges.erase(make_pair(from, to));
            }
        }
        cout<< "graph is finished loaded after "<<clock() - t<<" milisec."<<endl;
        cout<< "size of edges: "<<edges.size()<<endl;
        file.close();
    }

    int countIntersection(int i){
        int rs = 0;
        for(auto v: graph[i]){
            if(i<v && edges.find(make_pair(i,v)) != edges.end())
                rs++;
            if(i>v && edges.find(make_pair(v,i)) != edges.end())
                rs++;
        }       
        return rs;
    }
    int edgeSize(){
        return edges.size();
    }

    int getMaxDegree(){
        int maxIndex = 1;
        // set_intersection(graph[maxIndex].begin(), graph[maxIndex].end(), edges.begin(), edges.end(), inserter(maxSet, maxSet.begin()));
        int maxSet = countIntersection(maxIndex);
        for(int i= 2; i< V; i++){
            int current= countIntersection(i);
            // set_intersection(graph[i].begin(), graph[i].end(), edges.begin(), edges.end(), inserter(current, current.begin()));
            if(maxSet < current){
                maxIndex = i;
                maxSet = current;
            }
        }
        for(auto m:graph[maxIndex]){
            edges.erase(make_pair(m,maxIndex));
            edges.erase(make_pair(maxIndex,m));
        }

        // cout<<"erase: "<< maxSet<<endl;
        // cout<<"Edges size: "<< edgeSize()<<endl;
        return maxIndex;
    }

    vector<int> mvc_greedy(){
        vector<int> mvc;
        int i = 0;
        while (edgeSize() >0 ){
            // cout<< i << " loop "<< endl;
            int currentIndex = getMaxDegree(); // find the vertex with the highest unvisited edges
            // cout<< currentIndex<<" is in mvc"<< endl;
            mvc.push_back(currentIndex);
            i++;
        }
        return mvc;
    }
};


int main(int argc, char **argv){
    if(argc < 2){
        cout<< "please give the input file name"<<endl;
        exit(1);
    }
    char *filename = argv[1];
    Graph graph(filename);


    time_t t = clock();
    vector<int> out = graph.mvc_greedy();
    cout<< "found the result after "<< (clock()-t)/ CLOCKS_PER_SEC<< "secs"<<endl;
    cout<< endl << out.size()<< " vertexes found, they are : ";
    for(auto i: out)
        cout<< i << endl;
    cout<<endl;

    return 0;
}