//
//  Delmesh.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#include "DelMesh.hpp"
#include <fstream>
#include "Point2D.hpp"
#include <random>
#include <iostream>
#include <filesystem>
#include <string>
#include "Eigen/Dense"

DelMesh::DelMesh(){
    this->connecArray = std::vector<Triangle>();
    this->pointList = std::vector<Point2D>();
}

std::string DelMesh::generateRandPtLst(double minX, double maxX, double minY, double maxY, int n,int seed,std::string fileName){
    
    
    std::fstream outFile;
    outFile.open(fileName,std::ios::out);
    std::cout << "GenRandPtLst\n";
    if(outFile.is_open()){
        std::cout<<"File is Open\n";
        if (minX == minY && maxX == maxY){ //Checking if we have a symmetrical range for X and Y, this allowing us to use only one random distribution
            std::uniform_real_distribution<double> dist(minX,maxX);
            std::mt19937 rng;
            
            rng.seed(seed);
            
            for (int i=0; i<n; i++){
                double tempX = dist(rng);
                double tempY = dist(rng);
                
                outFile << tempX << "," << tempY << "\n";

            }
            
        }
        else{
            
            
            std::uniform_real_distribution<double> distX(minX, maxX);  //Random Number Dist for X
            std::uniform_real_distribution<double> distY(minY, maxY);  //Random Number Dist for Y
            
            std::mt19937 rng;
            
            rng.seed(seed);
            
            for(int i=0; i<n; i++){
                double tempX = distX(rng);
                double tempY = distY(rng);
                
                outFile << tempX << "," << tempY << "\n";
            }
        }
        outFile.close();
    }
    else{
        std::cout << "Error in opening file :(\n";
    }
    return fileName;
}

std::vector<Point2D> DelMesh::readPointListFromFile(std::string filePath){
    
    std::vector<Point2D> Output;
    std::fstream inFile(filePath);
    
    if (inFile.is_open()){
        std::string line;
        int n = 0;
        while(std::getline(inFile,line)){
            
            for (int i=0; i<line.size(); i++){
                if (line[i] == ','){
                    double tempX= stof(line.substr(0,i));
                    double tempY= stof( line.substr(i+1,line.size()-1));
                    Point2D tempPoint = Point2D(tempX,tempY);
                    //std::cout<<tempPoint;
                    Output.push_back(tempPoint);
                    
                    
                }
                
            }
            n++;
            
        }
        
        
    }
    std::cout << "Output Vector Length: " << Output.size()<< "\n";
    return Output;  
    
}

std::vector<Point2D> DelMesh::radialSort(std::vector<Point2D> pntLst){
    std::vector<Point2D> output = pntLst;
    std::sort(output.begin(),output.end());
    return output;
}


void DelMesh::findMaxMin(){
    //Use std::minmaxElement
    
    //Start Sorting radially now! 
    
    
    std::pair<std::vector<Point2D>::iterator, std::vector<Point2D>::iterator> mnmx;

    mnmx = std::minmax_element(pointList.begin(), pointList.end());

    std::cout << "\nThe minimum value position obtained is : ";
    std::cout << mnmx.first - pointList.begin() << std::endl;
    std::cout << "Min value: "<< pointList.at(mnmx.first - pointList.begin())<< "\n";

    std::cout << "\nThe maximum value position obtained is : ";
    std::cout << mnmx.second - pointList.begin() << std::endl;

    std::cout << "Max value: "<< pointList.at(mnmx.second - pointList.begin())<< "\n";
    std::cout << std::endl;



    if(this->pointList.size()==0){
        return;
    }
    double minX=0,maxX=0,minY=0,maxY = 0;
    for(int i=0; i<pointList.size(); i++){
        if(i==0){
            minX = pointList[i].V(0);
            maxX = pointList[i].V(0);
                             
            minY = pointList[i].V(1);
            maxY = pointList[i].V(1);
        }
        else{
            if(pointList[i].V(0) > maxX){
            maxX = pointList[i].V(0);
            }
            if(pointList[i].V(0) < minX){
                minX = pointList[i].V(0);
            }
            if(pointList[i].V(1) > maxY){
                maxY = pointList[i].V(1);
            }
            if(pointList[i].V(1) <minY){
                minY = pointList[i].V(1);
            }
        }
    
    }
    
    setmaxX(maxX);
    setmaxY(maxY);
    setminX(minX);
    setminY(minY);
    return;
    
}

Point2D DelMesh::getMeanPt(){
    double xMean = 0;
    double yMean = 0;
    for(int i=0;i<this->pointList.size();i++){
        xMean += pointList[i].V(0);
        yMean += pointList[i].V(1);
    }
    
    Point2D output = Point2D(xMean/this->pointList.size(), yMean/this->pointList.size());
        
        
    
    return output;
}


Triangle DelMesh::getSuperTriang(Point2D MAX_XY, Point2D MIN_XY){
    if(this->pointList.size()==0){
        return Triangle(Point2D(0, 0),Point2D(0, 0),Point2D(0, 0));
    }
    Point2D meanPoint= this->getMeanPt();
    
    double DeltaX = MAX_XY.V(0)-MIN_XY.V(0);
    double DeltaY = MAX_XY.V(1)-MIN_XY.V(1);
    double maxCircX  = maxX;
    double minCircX = minX;
    double maxCircY = maxY;
    double minCircY = minY;
    for(int i=0; i<this->pointList.size()-2; i++){
        for(int j=i+1; j< this->pointList.size()-1; j++){
            for(int k = j+1; k < this->pointList.size(); k++){
                //std::cout<<"Point Combination: I: " << i << ": "<< pointList[i]<<"J: "<<j<<": "<<pointList[j]<< "K: "<<k<<": "<<pointList[k]<<"\n";
                Triangle tri = Triangle(pointList[i],pointList[j],pointList[k]);
                //std::cout<<"["<<i<<","<<j<<","<<k<<"]\n";
                if (tri.circle.Box.XY_MAX.V(0) > maxCircX){maxCircX = tri.circle.Box.XY_MAX.V(0); }
                if (tri.circle.Box.XY_MAX.V(1) > maxCircY){maxCircY = tri.circle.Box.XY_MAX.V(1); }
                
                if (tri.circle.Box.XY_MIN.V(0) < minCircX){minCircX = tri.circle.Box.XY_MIN.V(0); }
                if (tri.circle.Box.XY_MIN.V(1) < minCircY){minCircY = tri.circle.Box.XY_MIN.V(1); }

            }

        }


    }
    std::cout<<maxCircX<<","<<maxCircY<<"||"<<minCircX<<","<<minCircY<<"\n";

    // std::cout<<"maxCircX: "<<maxCircX<<"\n";
    // std::cout<<"maxCircY: "<<maxCircY<<"\n";
    // std::cout<<"minCircX: "<<minCircX<<"\n";
    // std::cout<<"minCircY: "<<minCircY<<"\n";
    double C_supX = (maxCircX + minCircX) /2;
    double C_supY = (maxCircY + minCircY) /2;

    Point2D C_supPoint = Point2D(C_supX,C_supY);
    Point2D maxCIRCXY = Point2D(maxCircX,maxCircY);

    double r_cc = C_supPoint.dist(maxCIRCXY);
    double r_scc = 2*r_cc;


    double A_y = C_supY + r_scc;
    
    double BC_y = C_supY - r_scc/2;

    double B_x = C_supX + (3.0/2.0)*r_scc*tan(M_PI/6);
    double C_x = C_supX - (3.0/2.0)*r_scc*tan(M_PI/6);

    // std::cout<<"B_X: "<<B_x<<"\n";
    // std::cout<<"C_X: "<<C_x<<"\n";
    // std::cout<<"Tan: "<<tan(M_PI/6);
    Point2D A = Point2D(C_supX, A_y);

    Point2D B = Point2D(B_x, BC_y);
    Point2D C = Point2D(C_x, BC_y);

    Triangle output = Triangle(A, B, C);
    std::cout<<"========At SuperTriangReturn========\n";
    return output;
    
}

//Maybe adding an Insert Point function to use as a helper later on/make algorithm more modular?

std::vector<Triangle> DelMesh::BW_Insert_Pt(Point2D &point, std::vector<Triangle> &Triangulation){


    std::vector<Triangle> badTriangleList = {};
            std::vector<Edge> polygonEdgeList = {};
            for(int j=0;j<Triangulation.size();j++){
                if(Triangulation.at(j).checkIncircle(point)){
                    std::cout<<"Bad Triangle\n";
                //Remove from triangulationd
                //Store edges of triangle
                    badTriangleList.push_back(Triangulation.at(j));
                //Remove Bad Triangle From List
                }

                std::cout<<"Got to Triangulation loop\n";
            }  
        
        
            std::cout<<"got out of Triangulation loop\n";
            //Getting Convex hull of new hole in mesh
            for(Triangle badTriangle : badTriangleList){
                std::cout<<"Got to badTriangleList loop\n";
                
                for(int k=0; k<3; k++){
                    
                    std::cout<<"Got to Triangle Edge Loop\n";

                    int times_seen = 0;
                    if(polygonEdgeList.size()==0){
                        polygonEdgeList.push_back(badTriangle.Edges[k]);                


                    }else{
                        for(Edge polyEdge : polygonEdgeList){
                            
                            if(badTriangle.Edges[k]== polyEdge){
                                times_seen ++;
                                std::cout<<"Seen!";
                            }
                            std::cout<<"Polygon edge List loop\n";
                            if(times_seen ==1){
                                polygonEdgeList.push_back(badTriangle.Edges[k]);                
                            }
                            
                        }
                    }   
                    
                    
                }
                
            }

            for(int j=0; j<polygonEdgeList.size();j++){
                Triangle T = Triangle(point,polygonEdgeList[j].a,polygonEdgeList[j].b);
                Triangulation.emplace_back(T);
            }


}


std::vector<Triangle> DelMesh::BowyerWatson(std::vector<Point2D> pointList, Triangle SuperTriag){  
    std::vector<Triangle> Triangulation = {SuperTriag}; 
    for(int i=0; i<pointList.size(); i++){
        DelMesh::BW_Insert_Pt(pointList.at(i),Triangulation);
    }

}