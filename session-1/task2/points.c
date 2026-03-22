
#include <stdio.h>
#include "points.h"
#include <math.h>

int main( void ){

    // complete the structure definition in the header file first
    // implement code for the following
    // include necessary libraries
    
    Point p = { .x=1, .y=2 };
    Point q = { .x=-2, .y=4 };
    
    printf(" Distance between (%.1f,%.1f) and (%.1f,%.1f) is %f\n", 
             p.x,p.y,q.x,q.y,distance(p,q));
    
    return 0;
}

float distance( Point p, Point q ){
    // implement distance here
    float dx = p.x - q.x;
    float dy = p.y - q.y;
    return sqrtf(dx * dx + dy * dy);

}

Point reflect(Point q){ // returns a point 
    Point p;
    p.x =  q.x;
    p.y = -q.y;
    return p;
}

Point shift(Point q, Point dq){
    Point p;
    p.x = q.x + dq.x;
    p.y = q.y + dq.y;
    return p;
}