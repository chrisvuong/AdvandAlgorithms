#include<iostream>
#define MAX 9999
using namespace std;

struct edge{
    int src, des, weight;
};

struct graph{
    int V, E;
    edge* Edge; 
};

graph* createGraph(int V, int E){
    graph* G = new graph;
    G->E = E;
    G->V = V;
    G->Edge = new edge[E];
    return G;
}
graph* graphGeneration(int V,int E);

char translate(int i){
    switch (i)
    {
    case 0:
        return 'A';
        break;
    case 1:
        return 'B';
        break;
    case 2:
        return 'C';
        break;
    case 3:
        return 'D';
        break;
    default:
        return 'E';
        break;
    }
}

void Bell_ford (graph* Graph, int src){
    int V = Graph->V;
    int E = Graph -> E;
    int dist[V];
    int node[V][V] ;
    for(int i= 0; i< V; i++)
        for(int j = 0 ; j<V; j++)
            node[i][j] = -1;
    int deep[V] = {0};
    for(int i=0; i<V; i++){
        dist[i] = MAX;
        
    }
    node[src][0] = src;
    deep[src]++;
    dist[src] = 0;
    bool finish = true;
    for(int i= 1; i< V;i++){
        for(int j= 0; j<E; j++){
            int src = Graph->Edge[j].src;
            int des = Graph-> Edge[j].des;
            int weight = Graph->Edge[j].weight;
            if (dist[src] + weight< dist[des]){
                dist[des] = dist[src] + weight;
                int n = 0;
                for(; n< deep[src]; n++){
                    node[des][n] = node[src][n];
                }
                node[des][n] = des;
                deep[des] = n+1;
                finish = false;
            }
        } 
        if (finish) break;
        finish = true;
    }

    for(int i = 0; i< V;i++){
        for(int j = 0 ; j < deep[i];j++){
            cout<< translate(node[i][j])<< " ";
        }
        cout<<", total weight is "<<dist[i]<<endl;
    }
    cout<<endl;
}   

int main(){
    int V = 5;
    int E = 10;
    graph* Graph = graphGeneration(V,E);
    Bell_ford(Graph, 0);
   
    return 0;
}

graph* graphGeneration(int V,int E){
    graph* Graph = createGraph(V,E);
    // Let A,B,C,D,E be 0,1,2,3,4
    // Let edge 0 is A->B or 0-1
    Graph->Edge[0].src = 0;
    Graph->Edge[0].des = 1;
    Graph->Edge[0].weight = 6 ;
    // Let edge 1 is B->C or 1-2
    Graph->Edge[1].src = 1;
    Graph->Edge[1].des = 2;
    Graph->Edge[1].weight = 5 ;
    // Let edge 2 is C->B or 2-1
    Graph->Edge[2].src = 2;
    Graph->Edge[2].des = 1;
    Graph->Edge[2].weight = -2 ;
    // Let edge 3 is A->E or 0-4 
    Graph->Edge[3].src = 0;
    Graph->Edge[3].des = 4;
    Graph->Edge[3].weight = 7 ;
    // Let edge 4 is B->D or 1-3
    Graph->Edge[4].src = 1;
    Graph->Edge[4].des = 3;
    Graph->Edge[4].weight = -4 ;
    // Let edge 5 is D->A or 3-0
    Graph->Edge[5].src = 3;
    Graph->Edge[5].des = 0;
    Graph->Edge[5].weight = 2 ;
    // Let edge 6 is E->C or 4-2
    Graph->Edge[6].src = 4;
    Graph->Edge[6].des = 2;
    Graph->Edge[6].weight = -3 ;
    // Let edge 7 is E->D or 4-3
    Graph->Edge[7].src = 4;
    Graph->Edge[7].des = 3;
    Graph->Edge[7].weight = 9 ;
    // Let edge 8 is B->E or 1-4
    Graph->Edge[8].src = 1;
    Graph->Edge[8].des = 4;
    Graph->Edge[8].weight = 8 ;
    // Let edge 9 is D->C or 3-2
    Graph->Edge[9].src = 3;
    Graph->Edge[9].des = 2;
    Graph->Edge[9].weight = 7 ;

    return Graph;
}
