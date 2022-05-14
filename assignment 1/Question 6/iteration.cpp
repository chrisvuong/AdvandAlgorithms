#include<iostream>
#include <set>
#include<fstream>
#include<string>
#include<map>
#include<stack>
#include<vector>
#include<algorithm>
#include<time.h>
#define dictionaryFile "./dictionary.txt"
using namespace std;


set<string> getdictionary(int n = 0){
    ifstream file;
    set<string> rs;
    file.open(dictionaryFile);
    if(file.is_open()){
        string line;
        while ( getline (file,line) ){
            // line.erase(remove(line.begin(), line.end(), ' '), line.end());
            if(!n  || (n and line.size() == n))
                rs.insert(line);
        }
    } else 
        throw "Unable to open dictionary.txt" ;
    file.close();
    return rs;
}

string getHead (string s){
    return s.substr(1,2);
}

string getTail (string s){
    return s.substr(s.size()-3, 2);
}

map<string, vector<string> > make_subsequence_head (set<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getTHead(i);
        sub[str].push_back(i);
    }
    return sub;
}

map<string, vector<string> > make_subsequence_tail (set<string> dict){
    map<string, vector<string> > sub;
    for(auto i : dict){
        string str = getTail(i);
        sub[str].push_back(i);
    }
    return sub;
}

int main(){
    int size = 5;
    int max = 10;
    vector<string> result ;
    set<string> dictionary = getdictionary(size);
    map<string, vector<string> > head = make_subsequence_head(dictionary);
    clock_t t;
    t = clock();
    int found = 0;
    for(string word: dictionary){
        vector<string> sequence ;
        map<string, bool> visited;
        map<int, vector<string>> location;
        map<string, vector<string> > finish = make_subsequence_head(dictionary);
        visited[word] =true; 
        sequence.push_back(word);
        string current = word;
        while(true){
            string sub = getHead(current);
            while (finish)
        }
    }
    







    return 0;
}
