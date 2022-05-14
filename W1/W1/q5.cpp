
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

int intersect(line a, line b){
    cout<< ccw(a.a, a.b, b.a)<<endl;
    cout<< ccw(a.a, a.b, b.b)<<endl;
    cout<< ccw(b.a, b.b, a.a)<<endl;
    cout<< ccw(b.a, b.b, a.b)<<endl;
    if (ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) > 0) return false;
    if (ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) > 0) return false;
    return true;
}


int main(){
    line lineset[] = {
        {{3,5},{5,3}},
        {{5,3},{3,1}},
        {{1,3},{3,5}},
        {{3,1},{1,3}},
    };
    point   a = {1,1},
            b = {2,2},
            c = {1,2},
            d = {2,1}
            ;

    line    l1 = {a,b},
            l2 = {d,c};
    cout<< intersect(l1,l1);// ==> 1


    return 0;
}

