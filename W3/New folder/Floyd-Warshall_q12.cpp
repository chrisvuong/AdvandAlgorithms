#include<iostream>
#include<cmath>
using namespace std;
#define N 6
#define INF 9999
void print(int graph [][N]){
    for(int i=0; i<N; i++){
        for(int j = 0; j<N;j++){
            if(graph[i][j] == INF) cout<< "INF\t";
            else cout<< graph[i][j]<< "\t";
        }
        cout<<endl;
    }
}
void fw(int graph[][N]){
    int dist[N][N];
    for(int i = 0; i<N;i++)
        for(int j = 0; j<N ; j++)
            dist[i][j] = graph[i][j];
    for(int k=0; k<N;k++){
        for(int i = 0; i<N; i++)
            for(int j=0; j<N; j++)
                if(dist[i][k] + dist[k][j] < dist [i][j])
                    dist[i][j] =dist[i][k] + dist[k][j];
    }

    print(dist);
}



int main(){
    int graph[N][N] = {
        {0,INF, INF,INF, -1,INF }, // 1
        {1, 0, INF,2, INF, INF},  // 2
        {INF,2,0, INF, INF,-8}, // 3
        {-4, INF, INF,0,3, INF},// 4
        {INF,7, INF, INF,0, INF},// 5
        {INF,5,10, INF, INF,0}// 6
    };

    fw(graph);
    return 0;
}