//
//  Edge.hpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 5/9/25.
//

#include "Point2D.hpp"
#include <cmath>


class Edge{

public:
    
    //Change to
    Point2D a;
    Point2D b;
    Point2D midPt;
    float slope;
    float magnitude;
    bool usedInMesh;
    Edge() : a(), b(), midPt(), slope(0), magnitude(0), usedInMesh(0) {};
    Point2D computeMidpoint();
    char pointInEdge(Point2D p);
    bool SLOPE_INF;
    Edge(Point2D a, Point2D b): a(a),b(b) {
        
        this->midPt = computeMidpoint();
        this->SLOPE_INF = b.V(0) == a.V(0) ?  true : false;
        //std::cout<<"This->SLOPE_INF: "<< this->SLOPE_INF<<"\n"; 
        if (!SLOPE_INF){
            this->slope = (a.V(1)-b.V(1))/(a.V(0)-b.V(0));
        }
        this->magnitude = sqrt(pow((a.V(1)-b.V(1)),2)+ pow((a.V(0)-b.V(0)),2));
        
    };

    bool operator==(const Edge& other) const{
        return a.V == other.a.V && b.V == other.b.V;
        
    };
    
    friend std::ostream& operator <<(std::ostream& os, const Edge& edg){
        os << "Edge: " << edg.a << "->" << edg.b <<"\n";
        return os;
    }    
};
