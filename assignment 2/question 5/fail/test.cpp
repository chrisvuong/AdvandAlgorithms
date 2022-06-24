#include<iostream>
#include<set>
using namespace std;

int main(){
    set<pair<int, int>> s;
    s.insert(make_pair(1,2));
    s.insert(make_pair(1,2));
    s.insert(make_pair(3,4));
    cout<< s.erase(make_pair(1,2))<<endl;
    cout<< s.size();

}