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
        result.push_back(substr);
    }
    return result;
}


class Graph{
    private:
    set<int> *data;
    int size;
    set<int> visited;
    int *priorityList; // Create a small version of heap tree 
    int priorityIndex;
    public:
    // bool priority(int a, int b){
    //     return data[a].size()> data[b].size();
    // }
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
        //make a priority list sorted in the length of graph
        priorityIndex = size -1;
        priorityList = new int[priorityIndex];
        for(int i=0; i< priorityIndex; i++){
            priorityList[i] = i+1;
            // cout<< priorityList[i]<< " ";
        }cout<<endl; 
        quickSort(priorityList,0, priorityIndex-1); // sort as the size of edge
    }
    bool priority(int index1, int index2){
        set<int> intersect1;
        set_intersection(data[index1].begin(), data[index1].end(), visited.begin(), visited.end(), inserter(intersect1, intersect1.begin()));
        set<int> intersect2;
        set_intersection(data[index2].begin(), data[index2].end(), visited.begin(), visited.end(), inserter(intersect2, intersect2.begin()));
        // return index1> index2;
        return data[index1].size() - intersect1.size() < data[index2].size() - intersect2.size();
    }
    int partition (int arr[], int low, int high){
        int pivot = arr[high]; // pivot
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++){
            if (priority(arr[j] , pivot)){//data[arr[j]].size() > data[pivot].size()){
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        return (i + 1);
    }
 
    void quickSort(int arr[], int low, int high){
        if (low < high){
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    void printGraph(){
        for(int i=0 ; i<size; i++){
            cout<< i << " :"<<endl;
            for(auto j : data[i])
                cout<<j<< " ";
            cout<<endl;
        }
    }
    void printHeap(){
        for(int i =0 ; i<priorityIndex;i++)
            // cout<< data[priorityList[i]].size()<< " ";
            cout<< priorityList[i]<< " ";
        cout<<endl;
    }
    vector<int> mvc_greedy(){
        vector<int> mvc;
        int i = 0;
        while (visited.size() != size-1 ){
            cout<< i << " loop "<< endl;
            int currentIndex = priorityList[priorityIndex-1]; 
            visited.insert(currentIndex);
            mvc.push_back(currentIndex);
            for(auto v: data[currentIndex]){
                // cout<< v;
                visited.insert(v);
            }
            quickSort(priorityList, 0, priorityIndex-1);
            cout <<"visited :" <<visited.size()<< endl;
            priorityIndex--;
            i++;
        }
        // cout<< visited.size()<< endl;
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
    Graph graph("C2000.9.clq");
    // graph.printGraph();
    // graph.printHeap();
    time_t t = clock();
    vector<int> out = graph.mvc_greedy();
    cout<< "found the result after "<< (clock()-t)/ CLOCKS_PER_SEC<< "secs"<<endl;
    cout<< endl << out.size()<< " vertexed found, they are : ";
    for(auto i: out)
        cout<< i << " ";
    cout<<endl;
    // graph.test();
    return 0;
}