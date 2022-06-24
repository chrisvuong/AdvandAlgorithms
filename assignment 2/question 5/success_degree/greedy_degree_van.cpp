/*
This file is inpleament as same as the greedy_degree_set but it applies Van tree

*/


#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include<time.h>
#include "./Van-Emde-Boas-tree-master/include/vEBTree.hpp"
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
    vector<vEBTree*>graph;
    int V;
    // map<int, bool> degree;
    int E;
    bool* pass;
    public:

    Graph(string filename, bool originalGraph = false){
        ifstream file(filename);
        string line;
        vector<vEBTree*> origin;
        // Read file and generate graph
        time_t t = clock();
        while(getline(file, line)){
            char type = getType(line);
            if (type == 'p'){
                vector<string> slt = split(line);
                V = stoi(slt[2])+1;
                E = stoi(slt[3])+1;
                cout<< "a graph of "<< V << " vertexes "<<E<<" edges is created."<<endl;
                for(int i= 0; i< V; i++){
                    // cout<< i<<endl;
                    origin.push_back(new vEBTree(V));
                }
            } else if(type == 'e'){
                vector<string> slt = split(line);
                int from = stoi(slt[1]);
                int to = stoi(slt[2]);
                if(from > to)
                    swap(from,to);
                origin[from]->insert(to);
                origin[to]->insert(from);
            }
        }

        cout<< "original graph is finished loaded after "<<clock() - t<<" milisec."<<endl;
        cout<< "size of graph: "<<V<<endl;
        file.close();
        // find the compliment
        graph = origin;
        if(!originalGraph){
            t = clock();
            for(int i= 1 ; i< V; i++){
                for(int j = 1; j<V; j++){
                    if(!graph[i]->lookup(j) && i!=j)
                        graph[i]->insert(j);
                    else{
                        graph[i]->erase(j);
                    }    
                }
            }
            cout<< "complement graph is finished loaded after "<<clock() - t<<" milisec."<<endl;
            cout<< "size of graph: "<<V<<endl;
        }
    }

    int maxDegree(int *degree){
        int m = 0;
        for(int i=1; i< V; i++)
            m = (degree[i] > degree[m])? i:m;
        return m;
    }

    int size(int i){
        int s = 0;
        int cursor = graph[i]->successor(0);
        while (cursor> 0 && cursor< V){
            s++;
            cursor = graph[i]->successor(cursor);
        }
        return s;
    }

    vector<int> mvc_greedy_degree(){
        vector<int> mvc;
        int loop = 0;
        //create degree
        int degree[V] = {0};
        for(int i= 0 ; i<V; i++){
            degree[i] = size(i);//graph[i].size();
        }
        int maxI = maxDegree(degree);
        while (degree[maxI] !=0 ){
            mvc.push_back(maxI);
            degree[maxI] = 0;
            // for(auto v:graph[maxI]){
            //     degree[v]--;
            // }
            int cursor = graph[maxI]->successor(0);
            while (cursor> 0 && cursor< V){
                degree[cursor]--;
                cursor = graph[maxI]->successor(cursor);
            }
            maxI = maxDegree(degree);
            loop++;
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


    Graph graph(filename, true);
    //brock800_1.clq
    //brock800_2.clq
    //brock800_3.clq
    //brock800_4.clq
    // p_hat1500-1.clq
    // MANN_a45.clq
    // C2000.9.clq
    // C4000.5.clq

    time_t t = clock();
    vector<int> out = graph.mvc_greedy_degree();
    cout<< "found the result after "<< (clock()-t)/ CLOCKS_PER_SEC<< "secs"<<endl;
    cout<< endl << out.size()<< " vertexes found, they are : ";
    for(auto i: out)
        cout<< i << " ";
    cout<<endl;

    return 0;
}