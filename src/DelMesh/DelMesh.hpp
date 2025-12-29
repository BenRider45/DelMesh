//
//  DelMesh.hpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//
#pragma once

#ifndef DelMesh_hpp
#define DelMesh_hpp

#include "Point2D.hpp"
#include "Triangle.hpp"
#include <stdio.h>
#include <vector>
class DelMesh {
  // TODO refactor and make private things pricate
  // TODO define operations enum class and validator to be used in
  // initialization
  // TODO look into std::move for transferring vectors
public:
  DelMesh();
  DelMesh(const DelMesh &) = default;
  DelMesh(DelMesh &&) = default;
  DelMesh &operator=(const DelMesh &) = default;
  DelMesh &operator=(DelMesh &&) = default;

  bool Validate(std::string command);
  std::vector<Triangle> connecArray; // connectivity array
  std::vector<Point2D> pointList;    // Point list

  enum class OPERATIONS { TRIANGULATE };
  std::vector<Triangle>
  BowyerWatson(std::vector<Point2D> pointList,
               Triangle SuperTriang); // calculation of triangluation mesh
  void ExportConnecArray(
      std::string fileName,
      std::vector<Triangle>
          Triangulation); // writing connectivity array into textfile

  std::vector<Point2D>
  readPointListFromFile(std::string filePath); // Reading points from text file

  std::string generateRandPtLst(
      double minX, double maxX, double minY, double maxY, int n, int seed,
      std::string
          fileName); // Generate a n-length list of random 2D points under the
                     // given bounds for x and y, stores in textfile. Option to
                     // inclufe seed for reproducibility

  Point2D getMeanPt();

  std::vector<Point2D> radialSort(std::vector<Point2D> pntLst);

  // Return vector containing 2 points s.t output= {(Minx,Miny),(Maxx,Maxy)}
  std::vector<Point2D> findMaxMin(std::vector<Point2D> pointLst);

  bool Initialize(OPERATIONS op);

private:
  Triangle getSuperTriang(Point2D MAX_XY, Point2D MIN_XY);
  void BW_Insert_Pt(Point2D &point, std::vector<Triangle> &Triangulation);
};

#endif /* DelMesh_hpp */
