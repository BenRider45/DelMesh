//
//  Delmesh.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#include "DelMesh.hpp"
#include "../Eigen/Dense"
#include "Point2D.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <string>

DelMesh::DelMesh() {
  this->connecArray = std::vector<Triangle>();
  this->pointList = std::vector<Point2D>();
}

namespace {

std::string str_toupper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); } // correct
  );
  return s;
}

std::vector<Triangle> removeBadTriang(std::vector<Triangle> &BadTraings,
                                      std::vector<Triangle> &Triangulation) {
  std::vector<Triangle> output;
  for (Triangle t : Triangulation) {
    bool tInBt = false;
    for (Triangle bt : BadTraings) {
      if (bt == t) {
        std::cout << "Found Bad Triangle: " << bt;
        tInBt = true;
      }
    }
    if (!tInBt) {
      output.push_back(t);
    }
  }
  return output;
}

std::vector<Triangle> cleanTriangulation(std::vector<Triangle> &Triangulation) {
  std::vector<Triangle> output;

  // std::ranges::copy_if(Triangulation, std::back_inserter(output),
  // ([](Triangle& T) { return !(T.HAS_SUPERTRIANGLE_POINT); }));

  for (Triangle T : Triangulation) {
    std::cout << "\n Triangle: " << T << "\n";
    if (!T.has_supertriangle_point) {
      output.push_back(T);
    }
  }
  std::cout << "Length: " << output.size();
  return output;
}

} // namespace

std::string DelMesh::generateRandPtLst(double minX, double maxX, double minY,
                                       double maxY, int n, int seed,
                                       std::string fileName) {

  std::fstream outFile;
  outFile.open(fileName, std::ios::out);
  std::cout << "GenRandPtLst\n";
  if (outFile.is_open()) {
    std::cout << "File is Open\n";
    if (minX == minY &&
        maxX ==
            maxY) { // Checking if we have a symmetrical range for X and Y,make
                    // this allowing us to use only one random distribution
      std::uniform_real_distribution<double> dist(minX, maxX);
      std::mt19937 rng;

      rng.seed(seed);

      for (int i = 0; i < n; i++) {
        double tempX = dist(rng);
        double tempY = dist(rng);

        outFile << tempX << "," << tempY << "\n";
      }

    } else {

      std::uniform_real_distribution<double> distX(
          minX, maxX); // Random Number Dist for X
      std::uniform_real_distribution<double> distY(
          minY, maxY); // Random Number Dist for Y

      std::mt19937 rng;

      rng.seed(seed);

      for (int i = 0; i < n; i++) {
        double tempX = distX(rng);
        double tempY = distY(rng);

        outFile << tempX << "," << tempY << "\n";
      }
    }
    outFile.close();
  } else {
    std::cout << "Error in opening file :(\n";
  }
  return fileName;
}

std::vector<Point2D> DelMesh::readPointListFromFile(std::string filePath) {

  std::vector<Point2D> Output;
  std::fstream inFile(filePath);

  if (inFile.is_open()) {
    std::string line;
    int n = 0;
    while (std::getline(inFile, line)) {

      for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
          double tempX = stof(line.substr(0, i));
          double tempY = stof(line.substr(i + 1, line.size() - 1));
          Point2D tempPoint = Point2D(tempX, tempY, n);
          // std::cout<<tempPoint;
          Output.push_back(tempPoint);
        }
      }
      n++;
    }
  }
  return Output;
}

std::vector<Point2D> DelMesh::radialSort(std::vector<Point2D> pntLst) {
  std::vector<Point2D> output = pntLst;
  std::sort(output.begin(), output.end());
  return output;
}

std::vector<Point2D> DelMesh::findMaxMin(std::vector<Point2D> pointList) {
  Point2D minPt = pointList.at(0);
  Point2D maxPt = pointList.at(1);
  for (auto pt : pointList) {
    minPt.V(0) = minPt.V(0) > pt.V(0) ? pt.V(0) : minPt.V(0);
    minPt.V(1) = minPt.V(1) > pt.V(1) ? pt.V(1) : minPt.V(1);

    maxPt.V(0) = maxPt.V(0) < pt.V(0) ? pt.V(0) : maxPt.V(0);
    maxPt.V(1) = maxPt.V(1) < pt.V(1) ? pt.V(1) : maxPt.V(1);
  }
  std::vector<Point2D> output = {minPt, maxPt};
  return output;
}

Point2D DelMesh::getMeanPt() {
  double xMean = 0;
  double yMean = 0;
  for (int i = 0; i < this->pointList.size(); i++) {
    xMean += pointList[i].V(0);
    yMean += pointList[i].V(1);
  }

  Point2D output = Point2D(xMean / this->pointList.size(),
                           yMean / this->pointList.size(), -1);

  return output;
}

Triangle DelMesh::getSuperTriang(Point2D MAX_XY, Point2D MIN_XY) {

  double DeltaX = MAX_XY.V(0) - MIN_XY.V(0);
  double DeltaY = MAX_XY.V(1) - MIN_XY.V(1);
  double maxCircX = MAX_XY.V(0);
  double minCircX = MIN_XY.V(0);
  double maxCircY = MAX_XY.V(1);
  double minCircY = MIN_XY.V(1);

  double C_supX = (maxCircX + minCircX) / 2;
  double C_supY = (maxCircY + minCircY) / 2;

  Point2D C_supPoint = Point2D(C_supX, C_supY, -1);
  Point2D maxCIRCXY = Point2D(maxCircX, maxCircY, -1);

  double r_cc = C_supPoint.dist(maxCIRCXY);
  double r_scc = 2e10 * r_cc;

  double A_y = C_supY + r_scc;

  double BC_y = C_supY - r_scc / 2;

  double B_x = C_supX + (3.0 / 2.0) * r_scc * tan(M_PI / 6);
  double C_x = C_supX - (3.0 / 2.0) * r_scc * tan(M_PI / 6);

  Point2D A = Point2D(C_supX, A_y, -1);

  Point2D B = Point2D(B_x, BC_y, -2);
  Point2D C = Point2D(C_x, BC_y, -3);

  Triangle output = Triangle(A, B, C);
  return output;
}

void DelMesh::ExportConnecArray(std::string fileName,
                                std::vector<Triangle> triangulation) {
  std::fstream outFile;
  outFile.open(fileName, std::ios::out);

  if (outFile.is_open()) {
    for (auto triangle : triangulation) {
      std::cout << "Looking at triangle: " << triangle
                << "With bool val: " << triangle.has_supertriangle_point
                << "\n";
      outFile << triangle.a.idx + 1 << "," << triangle.b.idx + 1 << ","
              << triangle.c.idx + 1 << ";\n";
    }

    outFile.close();
  }
}
// Maybe adding an Insert Point function to use as a helper later on/make
// algorithm more modular?

void DelMesh::BW_Insert_Pt(Point2D &point,
                           std::vector<Triangle> &Triangulation) {

  std::vector<Triangle> badTriangleList = {};
  std::vector<Edge> polygonEdgeList = {};

  for (int j = 0; j < Triangulation.size(); j++) {
    if (Triangulation.at(j).checkIncircle(point)) {
      std::cout << "Bad Triangle\n";
      // Remove from triangulationd
      // Store edges of triangle
      badTriangleList.push_back(Triangulation.at(j));
      // Remove Bad Triangle From List
    }
  }

  for (Triangle badTriang : badTriangleList) {
    for (Edge e : badTriang.Edges) {
      bool isUnique = true;
      for (Triangle badTriangInner : badTriangleList) {
        if (!(badTriang == badTriangInner)) {
          for (Edge e2 : badTriangInner.Edges) {
            if (e == e2) {
              isUnique = false;
            }
          }
        }
      }
      if (isUnique) {
        polygonEdgeList.push_back(e);
      }
    }
  }
  // Remove bad Triangles from triangulation
  Triangulation = removeBadTriang(badTriangleList, Triangulation);

  for (int j = 0; j < polygonEdgeList.size(); j++) {
    //    std::cout<<"Building new Triangles\n";
    Triangle T = Triangle(point, polygonEdgeList[j].a, polygonEdgeList[j].b);
    Triangulation.push_back(T);
  }
}

std::vector<Triangle> DelMesh::BowyerWatson(std::vector<Point2D> pointList,
                                            Triangle SuperTriag) {
  std::vector<Triangle> Triangulation = {SuperTriag};
  for (int i = 0; i < pointList.size(); i++) {
    DelMesh::BW_Insert_Pt(pointList.at(i), Triangulation);
    //        std::cout<<"Triangulation.len: "<<Triangulation.size()<<"\n";
  }

  return cleanTriangulation(Triangulation);
}
