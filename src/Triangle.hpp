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
public:
    double calcIncircleDet(Point2D d);
    double calcOrientDet();
    Point2D a;
    Point2D b;
    Point2D c;
    Edge AB;
    Edge BC;
    Edge AC;
    std::vector<Edge> Edges;
    Circle circle;
    float area;
    float perim;


    Triangle() {};
    Triangle(Point2D a, Point2D b, Point2D c) : a(a),b(b),c(c) {
        std::cout<<"Triangle Constructor"<< a;
        area = computeArea();//Computing Area via shoelace
        
        AB = Edge(a,b);
        std::cout<<AB<<"\n";
        Edges.push_back(AB);
        BC = Edge(b,c);
        Edges.push_back(BC);
        AC = Edge(a,c);
        Edges.push_back(AC);

    };
    float computeArea() { return .5 *((b.V(0) - a.V(0))*(c.V(1)-a.V(1)))- ((c.V(0) - a.V(0)) * (b.V(1)-a.V(1))); };
    
    void checkOrient(); //Returns true if orientation is CC initially, 0 if orientation required modification to be CC
    bool checkIncircle(Point2D d);//
    Circle computeCircumcircle();
    
    
    


        
    

};
