//
//  BWMesh.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#include "BWMesh.hpp"
#include <fstream>
#include "Point2D.hpp"
#include <random>
#include <iostream>
#include <filesystem>
#include <string>
BWMesh::BWMesh(){
    this->connecArray = std::vector<Triangle>();
    this->pointList = std::vector<Point2D>();
    
}

std::string BWMesh::generateRandPtLst(double minX, double maxX, double minY, double maxY, int n,int seed,std::string fileName){
    
    
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

std::vector<Point2D> BWMesh::readPointListFromFile(std::string filePath){
    
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

void BWMesh::findMaxMin(){
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

Point2D BWMesh::getMeanPt(){
    double xMean = 0;
    double yMean = 0;
    for(int i=0;i<this->pointList.size();i++){
        xMean += pointList[i].V(0);
        yMean += pointList[i].V(1);
    }
    
    Point2D output = Point2D(xMean/this->pointList.size(), yMean/this->pointList.size());
        
        
    
    return output;
}


Triangle BWMesh::getSuperTriang(Point2D MAX_XY, Point2D MIN_XY){
    if(this->pointList.size()==0){
        return Triangle(Point2D(0, 0),Point2D(0, 0),Point2D(0, 0));
    }
    Point2D meanPoint= this->getMeanPt();
    
    float DeltaX = MAX_XY.V(0)-MIN_XY.V(0);
    float DeltaY = MAX_XY.V(1)-MIN_XY.V(1);
    float maxCircX  = maxX;
    float minCircX = minX;
    float maxCircY = maxY;
    float minCircY = minY;
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
    float C_supX = (maxCircX + minCircX) /2;
    float C_supY = (maxCircY + minCircY) /2;

    Point2D C_supPoint = Point2D(C_supX,C_supY);
    Point2D maxCIRCXY = Point2D(maxCircX,maxCircY);

    float r_cc = C_supPoint.dist(maxCIRCXY);
    float r_scc = 2*r_cc;


    float A_y = C_supY + r_scc;
    
    float BC_y = C_supY - r_scc/2;

    float B_x = C_supX + (3.0/2.0)*r_scc*tan(M_PI/6);
    float C_x = C_supX - (3.0/2.0)*r_scc*tan(M_PI/6);

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




