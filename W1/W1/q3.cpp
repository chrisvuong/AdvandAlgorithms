
// Implement in C++ a quick algorithm for deciding if two line segments are parallel 
// (without using any divisions).
//not yet
#include<iostream>
using namespace std;

struct point{int x,y;};
struct line
{
    point a,b;
};

int ccw(point a, point b, point c){
    //  area is positive then counter clockwise, if negative then clockwise.
    return (b.x - a.x)*(c.y-a.y) - (c.x - a.x)*(b.y - a.y);
}

int isParallel(line j, line k ){
    return (j.a.y - j.b.y)*(k.a.x - k.b.x) == (k.a.y - k.b.y) * (j.a.x - j.b.x);
}



int main(){
    line lineset[] = {
        {{3,5},{5,3}},
        {{5,3},{3,1}},
        {{1,3},{3,5}},
        {{3,1},{1,3}},
    };
 
    cout<<


    return 0;
}

