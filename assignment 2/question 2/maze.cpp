#include<iostream>
#include<vector>
#include<stdlib.h>
#include <time.h> 
#include<string>
using namespace std;


class MazeGeneration{
    private:
        vector< vector< pair<int ,int> > > parent;
        int w;
        int h;
        vector<pair< pair<int,int>, pair<int,int> >> unblockedWall;
    public:
        MazeGeneration(int w, int h);
        void printParent();
        pair<int, int> find( int a,  int b);
        void union_pair (pair<int, int> a, pair<int, int> b);
        vector<pair<int, int>> find_neighbor(int x, int y);
        void generateMaze(pair<int, int> start, pair<int, int> goal);
        pair<int, int> randCell(){
            return make_pair(rand() % w , rand() % h);
        }
        void printMaze();
};

int main(int argc, char **argv){
    if (argc < 3){
        cout<< "please enter size of maze width and height"<<endl;
        exit(1);
    }
    srand (time(NULL));
    int h = atoi(argv[1]),
        w = atoi(argv[2]);
    MazeGeneration maze = MazeGeneration(w,h);
    maze.generateMaze(make_pair(0,0), make_pair(w-1, h-1));
    maze.printMaze();


    return 0;
}





bool pairEqual( pair<int, int> a,  pair<int, int>b){
    return a.first == b.first && a.second == b.second;
}

void MazeGeneration::printMaze(){
    vector<vector<string>> horizontalWall(w, vector<string>(h, "  |"));
    vector<vector<string>> verticalWall(w, vector<string>(h, "+++"));
    
    for (auto wall : unblockedWall){
        auto cell1 = wall.first;
        auto cell2 = wall.second;
        if(cell1.first == cell2.first){
            if(cell1.second < cell2.second)
                horizontalWall[cell1.first][cell1.second] = "   ";
            else
                horizontalWall[cell2.first][cell2.second] = "   ";
        }else{
            if(cell1.first < cell2.first)
                verticalWall[cell1.first][cell1.second] = "   ";
            else
                verticalWall[cell2.first][cell2.second] = "   ";
        }
    }

    for(int i = 0; i< h+1; i++)
        cout<<"***";
    cout<< endl;
    for(int i = 0; i< w; i++){
        cout<<"*|";
        for(int j = 0; j< h; j++)
            cout<< horizontalWall[i][j];
        cout<< "*"<<endl << "*|";
        for(int j = 0; j< h; j++)
            cout<< verticalWall[i][j];
        cout<< "*"<<endl;
    }


    for(int i = 0; i< h+1; i++)
        cout<<"***";
    cout<< endl;
}

void MazeGeneration::generateMaze(pair<int, int> start, pair<int, int> goal){

    while(!pairEqual( find(start.first, start.second), find(goal.first, goal.second) )){

        pair<int, int> randomPick = randCell();

        int x = randomPick.first, y = randomPick.second;
        vector<pair<int, int>> neighborhood = find_neighbor(x,y);
        pair<int, int> pickedNeighbor = neighborhood[rand() % neighborhood.size()];
        
        if(!pairEqual( find(x,y) , find(pickedNeighbor.first, pickedNeighbor.second))){
            unblockedWall.push_back(make_pair(randomPick, pickedNeighbor));
            union_pair(randomPick, pickedNeighbor);
        }
    }
}

vector<pair<int, int>> MazeGeneration::find_neighbor(int x, int y){
    vector<pair<int, int>> result;
    if( x > 0)
        result.push_back(make_pair(x-1, y));
    if( x < w-1)
        result.push_back(make_pair(x+1, y));
    if( y > 0)
        result.push_back(make_pair(x, y-1));
    if( y < h-1)
        result.push_back(make_pair(x, y+1));
    return result;
}

void MazeGeneration::union_pair (pair<int, int> a, pair<int, int> b){
    pair<int, int> p1 = find(a.first, a.second);
    pair<int, int> p2 = find(b.first, b.second);
    if ( pairEqual(p1, p2) )
        return;
    parent[p1.first][p1.second] = p2;
}

pair<int, int> MazeGeneration::find( int x, int y){
    if( !pairEqual(make_pair(x,y) , parent[x][y]) )
        return find( parent[x][y].first , parent[x][y].second);
    return parent[x][y];
}

MazeGeneration::MazeGeneration(int w, int h): w(w), h(h){
    vector< vector< pair<int ,int> > > p(w, vector< pair<int ,int> >(h) );
    for(int i = 0 ; i< w; i++){
        for(int j = 0 ; j< h; j++){
            p[i][j] = make_pair(i, j);
        }
    }
    parent = p;
}

void MazeGeneration::printParent(){
    for(int i = 0 ; i< w; i++){
        for(int j = 0 ; j< h; j++){
            cout<< parent[i][j].first << "," << parent[i][j].second << " ";
        }
        cout<< endl;
    }
}