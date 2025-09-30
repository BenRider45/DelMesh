//
//  Edge.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 5/9/25.
//

#include "Edge.hpp"

//Computes the midpoint of edge
Point2D Edge::computeMidpoint(){
    double midX = (this->a.V(0) + this->b.V(0))/2;
    double midY = (this->a.V(1) + this->b.V(1))/2;
    
    return Point2D(midX,midY,-1);
    
    
}

//Returns 'a' is point is == Edge->a, 'b' is point is == Edge->b, "N" if not either point
char Edge::pointInEdge(Point2D p){
    
    if(a == p) return 'a';
    
    else if(b==p) return 'b';
    
    else return 'N';
        
}
