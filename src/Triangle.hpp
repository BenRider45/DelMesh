//
//  Triangle.hpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <stdio.h>
#include <vector>
#include "Point2D.hpp"
#include "Edge.hpp"
#include "Circle.hpp"

#endif /* Triangle_hpp */


class Triangle{
private:
    double calcIncircleDet(Point2D d);
    double calcOrientDet();
    Point2D a;
    Point2D b;
    Point2D c;
    std::array<Edge,3> Edges; //Edge Order: AB, BC, AC
    Circle circle;
    float area;
    float perim;
public:

    Triangle() {};
    Triangle(Point2D a, Point2D b, Point2D c) : a(a),b(b),c(c) {
        area = computeArea();//Computing Area via shoelace
        Edges[0] = Edge(a,b);
        Edges[1] = Edge(b,c);
        Edges[2] = Edge(a,c);
    };
    float computeArea() { return .5 *((b.V(0) - a.V(0))*(c.V(1)-a.V(1)))- ((c.V(0) - a.V(0)) * (b.V(1)-a.V(1))); };
    
    std::vector<Point2D> verticies; //Will almost always have len of 3
    void checkOrient(); //Returns true if orientation is CC initially, 0 if orientation required modification to be CC
    bool checkIncircle(Point2D d);//
    Circle computeCircumcircle();
    
    
    


        
    

};
