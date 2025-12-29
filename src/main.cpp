//
//  main.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/13/25.
//
//

#include "DelMesh/DelMesh.hpp"
#include "DelMesh/Point2D.hpp"
#include "DelMesh/flags.hpp"
#include <gflags/gflags.h>

DECLARE_bool(help);
DECLARE_bool(helppackage);

const std::string HELP_MSG =
    "Welcome to Delmesh! A command line tool used to create Delaunay "
    "Triangulations of a given set of points.";

int main(int argc, char *argv[]) {
  std::cout << "test\n";
  gflags::SetUsageMessage(HELP_MSG);
  std::cout << "after test\n";

  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (argc <= 1) {
    std::cout << "got here\n";
    gflags::ShowUsageWithFlagsRestrict(argv[0], "0");
    return 1;
  }

  std::cout << "after parse\n";
  std::string command = argv[1];
  std::cout << "command:" << command << "\n";
  DelMesh Mesh = DelMesh();
  Point2D MAX_XY = Point2D(10, 10, -1);
  Point2D MIN_XY = Point2D(-10, -10, -1);
  Mesh.Validate(std::move(command));
  std::string pointFPath =
      Mesh.generateRandPtLst(MIN_XY.V(0), MAX_XY.V(0), MIN_XY.V(1), MAX_XY.V(1),
                             300, 10, "../PointFiles/TestPointFil4e.txt");
  std::vector<Point2D> pointList =
      Mesh.readPointListFromFile("../PointFiles/TestPointFil4e.txt");
  pointList = Mesh.radialSort(pointList);

  return 0;
}
