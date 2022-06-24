#include<iostream>
#include<fstream>
#include<vector>
#include<set>
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
    set<int> *data;
    int size;
    set<int> visited;
    bool* pass;
    public:
    Graph(string filename){
        ifstream file(filename);
        string line;
        // Read file and generate graph
        while(getline(file, line)){
            char type = getType(line);
            if (type == 'p'){
                vector<string> slt = split(line);
                size = stoi(slt[2])+1;
                cout<< "a graph of "<< size << " edges is created."<<endl;
                data = new set<int>[size];
            } else if(type == 'e'){
                vector<string> slt = split(line);
                int from = stoi(slt[1]);
                int to = stoi(slt[2]);
                data[from].insert(to);
                data[to].insert(from);
            }
        }
        file.close();
        pass = new bool[size];
    }
    
    void printGraph(){
        for(int i=0 ; i<size; i++){
            cout<< i << " :"<<endl;
            for(auto j : data[i])
                cout<<j<< " ";
            cout<<endl;
        }
    }
    int getMaxDegree(){
        set<int> maxIntersect;
        int maxIndex = 1;
        set_intersection(data[maxIndex].begin(), data[maxIndex].end(), visited.begin(), visited.end(), inserter(maxIntersect, maxIntersect.begin()));
        for(int i= 2; i< size; i++){
            set<int> current;
            set_intersection(data[i].begin(), data[i].end(), visited.begin(), visited.end(), inserter(current, current.begin()));
            if(data[maxIndex].size() - maxIntersect.size() < data[i].size() - current.size()){
                maxIndex = i;
                maxIntersect = current;
            }
        }
        return maxIndex;
    }
    vector<int> mvc_greedy(){
        vector<int> mvc;
        int i = 0;
        while (visited.size() != size-1 ){
            cout<< i << " loop "<< endl;
            int currentIndex = getMaxDegree(); 
            visited.insert(currentIndex);
            mvc.push_back(currentIndex);
            for(auto v: data[currentIndex]){
                // cout<< v;
                visited.insert(v);
            }
            cout <<"visited :" <<visited.size()<< endl;
            i++;
        }
        cout<< visited.size()<< endl;
        return mvc;
    }
    void test(){
        vector<int> index = {496, 462, 700, 621};
        set<int> visited;
        for(auto i:index){
            for(auto j: data[i])
                visited.insert(j);
        }
        for(auto i : visited)
            cout<< i << " ";
        cout<< endl;
        cout<< visited.size()<< endl;
    }
};

int main(){
    // Graph graph("C2000.9.clq");
    Graph graph("C4000.5.clq");
    // Graph graph("p_hat1500-1.clq");
    // Graph graph("MANN_a45.clq");
    // Graph graph("MANN_a45.clq");

    time_t t = clock();
    vector<int> out = graph.mvc_greedy();
    cout<< "found the result after "<< (clock()-t)/ CLOCKS_PER_SEC<< "secs"<<endl;
    cout<< endl << out.size()<< " vertexes found, they are : ";
    for(auto i: out)
        cout<< i << " ";
    cout<<endl;

    return 0;
}