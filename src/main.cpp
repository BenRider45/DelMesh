//
//  main.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/13/25.
//
//

#include <iostream>
#include "DelMesh/Point2D.hpp"
#include "DelMesh/DelMesh.hpp"
#include "DelMesh/UTIL.hpp"
#include <iomanip>
#include <limits>
int main(int argc, const char * argv[]) {

    Point2D testPoint = Point2D(3.4214,2.6667543,-1);
    
    DelMesh Mesh = DelMesh();
    Point2D MAX_XY = Point2D(10, 10,-1);
    Point2D MIN_XY = Point2D(-10,-10,-1);
   // std::string fPath =  + "/Delauney Mesh\s Generation/External";

   //TESTING SEED
   //std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),4,100,"../PointFiles/TestPointFil3e.txt");

    std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),300,10,"../PointFiles/TestPointFil4e.txt");
    std::vector<Point2D> pointList = Mesh.readPointListFromFile("../PointFiles/TestPointFil4e.txt");
    pointList = Mesh.radialSort(pointList);
    Triangle supTriang = Mesh.getSuperTriang(MAX_XY,MIN_XY);
    std::vector<Triangle> triang;
    std::cout<<supTriang<<"\n";

    std::vector<Point2D> MaxMin = Mesh.findMaxMin(pointList);
    std::cout<< "MaxMin length:" << MaxMin.size() << "\n";
    for( auto pt : MaxMin){
      std::cout<< "Point: " << pt << "\n";

    }     
//    triang = Mesh.BowyerWatson(pointList,supTriang);
//    Mesh.ExportConnecArray("../PointFiles/TestArray.txt",triang);
    
  
    return 0;
}                            

