// given a set of N lines, how many intersect
// Design an O(N*logN) algorithm and implement 
// it in C++ for the case where there are only vertical or horizontal lines
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;

struct point{int x,y;};
struct line
{
    point a,b;
    line(point a, point b) : a(a), b(b){};
};

int ccw(point a, point b, point c){
    //  area is positive then counter clockwise, if negative then clockwise.
    return (b.x - a.x)*(c.y-a.y) - (c.x - a.x)*(b.y - a.y);
}

int intersect(line a, line b){
    if (ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) > 0) return false;
    if (ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) > 0) return false;
    return true;
}
struct event{
    line l;
    int type; // 0 is horizontal startpoint , 1 is horizontal endpoint, 2 is vertical
    event(line line, int t): l(line), type(t){};
} ;

vector<event> generating_event();

bool compare(event a, event b) {return a.l.a.x< b.l.a.x;};

bool isSameLine(line a, line b){return  a.a.x == b.b.x && 
                                        a.a.y == b.b.y &&
                                        a.b.x == b.a.x &&
                                        a.b.y == b.a.y;}

void deleteLine (vector<line> sl, line l){
    for(auto it = sl.begin(); it != sl.end(); it++){ // the worst case can be O(n)
        if(isSameLine(*it, l)){
            // cout<< "a line is erated";
            sl.erase(it);
            return;
        }
    }
}

int count_intersect(vector<event> events){
    sort(events.rbegin(), events.rend(), compare); // sort them to a decreasing order, assumming it used the best efficient sort has O(nlog(n))
    int intersections = 0; // counting the intersection
    vector<line> sweepline; // initialize the sweepline set
    while (!events.empty()) 
    {
        event E = events[events.size() -1];
        // the sweepline will loop through from the smallest x so it pop the last event
        switch (E.type) 
        {
        // Check if the case is horizontal, then there is horizontal, the sl 
        case 0: // case that the line is horizontal and it is the start of the horizontal
            sweepline.push_back(E.l);
            break;
        case 1: // case that the line is horizontal and it is the end of the horizontal
            deleteLine(sweepline, E.l);// delete the E.l in the sweepline 
            break;
        default: // this is the case of 2 which is the vertical line, it may intersect to all the parallel line in the sweepline
            for(auto l : sweepline){
                if (intersect(l,E.l)) {
                    intersections++;
                    cout<< "line {(" <<l.a.x << ','
                                    <<l.a.y << "),("
                                    <<l.b.x << ","
                                    <<l.b.y << ')'<< "} intersects with line {("
                                    <<E.l.a.x << ','
                                    <<E.l.a.y << "),("
                                    <<E.l.b.x << ','
                                    <<E.l.b.y << ")}."<<endl; 

                }
            }
            break;
        }
        events.pop_back();
    }
    
    return intersections;
}

int main (){
    // create some event line:
    vector<event> events = generating_event();
    
    // for(auto e : events){
    //     cout<< e.l.a.x << " "<< e.l.a.y << " "<< e.l.b.x << " "<< e.l.b.y << endl;
    // }
    cout<< "Total intersections: "<< count_intersect(events)<<endl;
    return 0;
}





vector<event> generating_event(){ // adding all the line accouding to the graph in the report.
    vector<event> events;
    //adding all horizontal line
    events.push_back( event( line ({2,3} , {4,3}), 0));
    // events.push_back( event( line ({2,3} , {4,3}), 1));
    events.push_back( event( line ({4,3} , {2,3}), 1));

    events.push_back( event( line ({3,9} , {10,9}), 0));
    // events.push_back( event( line ({3,9} , {10,9}), 1));
    events.push_back( event( line ({10,9} , {3,9}), 1));

    events.push_back( event( line ({6,13} , {10,13}), 0));
    // events.push_back( event( line ({6,13} , {10,13}), 1));
    events.push_back( event( line ({10,13} , {6,13}), 1));

    events.push_back( event( line ({9,11} , {16,11}), 0));
    // events.push_back( event( line ({9,11} , {16,11}), 1));
    events.push_back( event( line ({16,11} , {9,11}), 1));

    events.push_back( event( line ({6,16} , {13,16}), 0));
    // events.push_back( event( line ({6,16} , {13,16}), 1));
    events.push_back( event( line ({13,16} , {6,16}), 1));

    events.push_back( event( line ({6,6} , {12,6}), 0));
    // events.push_back( event( line ({6,6} , {12,6}), 1));
    events.push_back( event( line ({12,6} , {6,6}), 1));

    events.push_back( event( line ({14,6} , {17,6}), 0));
    // events.push_back( event( line ({14,6} , {17,6}), 1));
    events.push_back( event( line ({17,6} , {14,6}), 1));

    events.push_back( event( line ({16,7} , {20,7}), 0));
    // events.push_back( event( line ({16,7} , {20,7}), 1));
    events.push_back( event( line ({20,7} , {16,7}), 1));

    events.push_back( event( line ({17,9} , {27,9}), 0));
    // events.push_back( event( line ({17,9} , {27,9}), 1));
    events.push_back( event( line ({27,9} , {17,9}), 1));

    events.push_back( event( line ({15,14} , {17,14}), 0));
    // events.push_back( event( line ({15,14} , {17,14}), 1));
    events.push_back( event( line ({17,14} , {15,14}), 1));

    events.push_back( event( line ({18,14} , {23,14}), 0));
    // events.push_back( event( line ({18,14} , {23,14}), 1));
    events.push_back( event( line ({23,14} , {18,14}), 1));

    // adding all vertical line
    events.push_back( event( line ({4,12} , {4,5}), 2));
    events.push_back( event( line ({7,17} , {7,5}), 2));
    events.push_back( event( line ({11,17} , {11,12}), 2));
    events.push_back( event( line ({10,12} , {10,7}), 2));
    events.push_back( event( line ({12,13} , {13,2}), 2));
    events.push_back( event( line ({15,5} , {15,12}), 2));
    events.push_back( event( line ({16,15} , {16,12}), 2));
    events.push_back( event( line ({22,10} , {22,6}), 2));
    events.push_back( event( line ({21,18} , {21,12}), 2));
    events.push_back( event( line ({18,6} , {18,12}), 2));
    return events;
}