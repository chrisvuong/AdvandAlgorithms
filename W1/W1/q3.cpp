
// Implement in C++ a quick algorithm for deciding if two line segments are parallel 
// (without using any divisions).

#include<iostream>
using namespace std;

struct point{int x,y;};
struct line
{
    point a,b;
};

int isParallel(line j, line k ){
    return (j.a.y - j.b.y)*(k.a.x - k.b.x) == (k.a.y - k.b.y) * (j.a.x - j.b.x);
}

int main(){
    line lineset[] = {
        {{1,2},{0,1}},
        {{1,1},{2,2}},
        {{1,4},{2,2}},
        {{1,4},{2,2}}
    };
 



    return 0;
}

