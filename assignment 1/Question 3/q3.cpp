#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
using namespace std;
#define N 100000

void addEdge(vector<int> graph[], int u, int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool isVconnectU(vector<int> graph[], int v, const int u){
    for(auto i: graph[v])
        if (i == u)
            return true;
    return false;
}

vector<int> allVerticesConnectedV (vector<int> graph[], int v){
    return graph[v];
}

int main(){
    vector<int> graph[N];
    // make the randomness by mt13337 up to N numbers
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,N-1);
    // Adding to the graph 20 edges each nodes
    cout<< "Generating the Adjacency list :"<< endl;
    for(int i=0; i<N;i++){
        for(int j = 0; j<20; j++){ 
            addEdge(graph, dis(gen), dis(gen));
        }
    }
    // all the edges that are in the node 100
    cout<< "\tNodes that connect to node 100: "<<endl<<"\t";
    for(auto i: allVerticesConnectedV(graph, 100)){
        cout<< i<<" -> ";
    }
    cout<< endl;
    cout<< "\tIs 123 connected to 100 :"<< isVconnectU(graph, 100, 123)<< endl;
    cout<< "\tIs "<< graph[100][0] << " connected to 100: "<< isVconnectU(graph, 100, graph[100][0])<< endl;

    cout<< "Generating the Adjacency matrix : Fail from compiling "<< endl;
    // // uncomment the lines below, this will stop compiling for the message of error: size of array is too large
    // try{
    //    int *matrix = new int[N][N]; 
    // }catch (const char* e){
    //     cout<< "Error occurs for generating a matrix: "<< e<<endl;
    // }
    

    return 0;
}