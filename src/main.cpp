//
//  main.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/13/25.
//
//TODO:
// Make Triangle data structure
// Write SuperTriangle calculation algo
// Write orientation check
// Write incircle
#include <iostream>
#include "Point2D.hpp"
#include "BWMesh.hpp"

int main(int argc, const char * argv[]) {


    Point2D testPoint = Point2D(3.4214,2.6667543);
    
    BWMesh Mesh = BWMesh();
    std::cout << "Hello World\n";    
    Point2D MAX_XY = Point2D(10.0, 10.0);
    Point2D MIN_XY = Point2D(-10.0,-10.0);
   // std::string fPath =  + "/Delauney Mesh\s Generation/External";
    std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),10,100,"../PointFiles/TestPointFil2e.txt");
    
        
    Point2D A = Point2D(5.0,5.0);
    Point2D B = Point2D(2.5,20.5);
    Point2D C = Point2D(6.4, 6.3);
    
    Triangle tri = Triangle(A,B,C);
    std::cout<< tri.Edges[0]; 
    std::cout<< tri.Edges[1];
    std::cout<< tri.Edges[2];
   
    std::cout<<"Do I get to 34?\n";
    Circle circ = tri.computeCircumcircle();
    std::cout<<"Circle Center: "<<circ.radius<<"\n";
    std::cout<< pointFPath<<"\n";
    Mesh.pointList = Mesh.readPointListFromFile("../PointFiles/TestPointFile.txt");
    
    
    for (Point2D p : Mesh.pointList){
        std::cout << p <<"\n" ;
        
    }
//    std::cout<<"Hello World!";
    return 0;
}                            

