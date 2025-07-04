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
    Edge CA;
    std::vector<Edge> Edges;
    Circle circle;
    float area;
    float perim;


    Triangle() {};
    Triangle(Point2D a, Point2D b, Point2D c) {

        this->a = a;
        this->b = b;
        this->c = c;
        this->AB = Edge(a,b);
        this->BC = Edge(b,c);
        this->CA = Edge(c,a);
        //std::cout<<"Triangle Constructor"<< a;
        area = computeArea();//Computing Area via shoelace
        Edges = {AB,BC,CA};
        // AB = Edge(a,b);
        // //std::cout<<AB<<"\n";
        // Edges.push_back(AB);
        // BC = Edge(b,c);
        // Edges.push_back(BC);
        // CA = Edge(c,a);
        // Edges.push_back(CA);
        if(correctOrient() == -1){
            std::cout<<"Points given in clockwise order\n";
        }
        
        this->circle = computeCircumcircle();

       // std::cout<<"Triangle Constructor circle: "<<this->circle<<'\n';
    };
    float computeArea() { return .5 *((b.V(0) - a.V(0))*(c.V(1)-a.V(1)))- ((c.V(0) - a.V(0)) * (b.V(1)-a.V(1))); };
    
    int checkOrient(); //returns 1 if oriented correctly, returns -1 if not oriented correctly, and 0 if points are colinear
    int correctOrient(); // returns 1 if points did not need correction, -1 if points were corrected
    bool checkIncircle(Point2D d);//
    Circle computeCircumcircle();
    
    friend std::ostream& operator <<(std::ostream& os, const Triangle& triag){
        os << "Triangle: \n" << "AB: " << triag.AB << "-> BC : " << triag.BC << "-> CA: " << triag.CA
        << "\n CircumCircle: \n"<<triag.circle;
        return os;
    } 
    


        
    

};
