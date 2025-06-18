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
    Point2D MAX_XY = Point2D(1, 1);
    Point2D MIN_XY = Point2D(-1,-1);
   // std::string fPath =  + "/Delauney Mesh\s Generation/External";
    std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),4,100,"../PointFiles/TestPointFil3e.txt");
    
    Mesh.pointList = Mesh.readPointListFromFile(pointFPath);

    for(int i=0; i<Mesh.pointList.size(); i++){
        std::cout<<Mesh.pointList[i]<<"\n";

    }

    
    Triangle supTriang = Mesh.getSuperTriang(MAX_XY,MIN_XY);
    
    std::cout<< supTriang;


    return 0;
}                            

