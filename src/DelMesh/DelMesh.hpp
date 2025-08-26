//
//  DelMesh.hpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#ifndef DelMesh_hpp
#define DelMesh_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Point2D.hpp"
#include "Triangle.hpp"
#include "UTIL.hpp"
class DelMesh {
    
public:
    DelMesh();
    std::vector<Triangle> connecArray;//connectivity array
    std::vector<Point2D> pointList; //Point list
    double maxX,maxY,minX,minY;
    
    std::vector<Triangle> BowyerWatson(std::vector<Point2D> pointList,Triangle SuperTriang);//calculation of triangluation mesh
    std::vector<Triangle> BW_Insert_Pt(Point2D &point, std::vector<Triangle> &Triangulation);
    std::string ExportConnecArray(std::string fileName,std::vector<Triangle> Triangulation); //writing connectivity array into textfile
    std::vector<Point2D> readPointListFromFile(std::string filePath);//Reading points from text file
    std::string generateRandPtLst(double minX, double maxX, double minY, double maxY, int n,int seed,std::string fileName);//Generate a n-length list of random 2D points under the given bounds for x and y, stores in textfile. Option to inclufe seed for reproducibility
    void setmaxX(double maxX){this->maxX=maxX;}
    void setminX(double minX){this->minX=minX;}
    void setmaxY(double maxY){this->maxY=maxY;}
    void setminY(double minY){this->minY=minY;}

    double getmaxX(){return this->maxX;}
    double getmaxY(){return this->maxY;}
    double getminX(){return this->minX;}
    double getminY(){return this->minY;}
    
    Point2D getMeanPt();

    std::vector<Point2D> radialSort(std::vector<Point2D> pntLst);

    void findMaxMin();
    //Finding the Min and Max X Y values for the given pointList
    
    Triangle getSuperTriang(Point2D MAX_XY, Point2D MIN_XY);

    
};



#endif /* DelMesh_hpp */
