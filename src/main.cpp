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
#include <gflags/gflags.h>
#include "DelMesh/flags.hpp"
#include <iomanip>
#include <limits>

DECLARE_bool(test);

const std::string HELP_MSG = "Welcome to Delmesh! A command line tool used to create Delaunay Triangulations of a given set of points.";

int main(int argc, char * argv[]) {

  for(int i=0; i < argc; i++){
    std::cout<<"Value: " << argv[i] << "\n";
    
  }

  gflags::ParseCommandLineFlags(&argc, &argv, true);

  for(int i=0; i < argc; i++){
    std::cout<<"Value: " << argv[i] << "\n";
    
  }
  
  std::string test = FLAGS_test ? "true!" : "false";
  std::cout << "This flag is " << test << "\n";
  Point2D testPoint = Point2D(3.4214,2.6667543,-1);
    
  DelMesh Mesh = DelMesh();
  Point2D MAX_XY = Point2D(10, 10,-1);
  Point2D MIN_XY = Point2D(-10,-10,-1);

  std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),300,10,"../PointFiles/TestPointFil4e.txt");
  std::vector<Point2D> pointList = Mesh.readPointListFromFile("../PointFiles/TestPointFil4e.txt");
  pointList = Mesh.radialSort(pointList);
  Triangle supTriang = Mesh.getSuperTriang(MAX_XY,MIN_XY);
  std::vector<Triangle> triang;
  std::cout<<supTriang<<"\n";

  std::vector<Point2D> MaxMin = Mesh.findMaxMin(pointList);
    
  
  return 0;
}                            

