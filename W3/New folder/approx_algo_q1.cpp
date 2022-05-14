#include<iostream>
#include<set>
#include<vector>
using namespace std;
vector<int> degrees(20,0);

void find_max(set<pair<int,int>> E_p){
    auto max = begin(E_p);
    int maxd = (degrees[max->first] + degrees[max->second]) /2;
    for (auto e : E_p)
        if(((degrees[e.first]+ degrees[e.second]) /2) > maxd) {
            max = &e;
            maxd = degrees[e.first]+ degrees[e.second] /2;
        }
    iter_swap (E_p.begin() , max );
}

int main(){
    set<int> C;
    set<pair<int,int>> E_p;
    E_p.insert({1,5});
    degrees[1]++;
    degrees[5]++;
    E_p.insert({2,5});
    E_p.insert({3,5});
    E_p.insert({4,5});
    E_p.insert({5,6});
    E_p.insert({6,7});
    E_p.insert({6,8});
    E_p.insert({6,9});
    E_p.insert({6,10});
    for(auto e:E_p){
        degrees[e.first]++;
        degrees[e.second]++;
    }
    while(!E_p.empty()){
        find_max(E_p);
        auto uv = begin(E_p);
        int u = uv->first, v = uv->second;
        C.insert(u);
        C.insert(v);
        while (uv != end(E_p)){
            if(uv->first == u || uv->first == v || uv->second == u || uv->second == v)
                uv = E_p.erase(uv);
            else   uv++;
        }
        
    }
    for(auto u : C) cout<<u<< " ";
    cout<<endl;
    return 0;
}