//
//  Point2D.hpp
//  Delauney Mesh Generation
//  Helper class which represents a 2D point in cartesian coordinates
//  Created by Ben Rider on 1/13/25.
//

#ifndef Point2D_hpp
#define Point2D_hpp

#include <stdio.h>
#include <iostream>
#include "Eigen/Dense"
#include <cmath>
#include "UTIL.hpp"
class Point2D {
     
    
public:

    Eigen::Vector2d V;//Point Vector
    
    bool inTriangle;
   
    double mag;

    int idx; //Index of point in respective pointList
    //1
    
//    If the slope is zero, you know the 𝑦
//     coordinate of the center because two of your points have the same 𝑥
//     coordinate and the bisector is the line halfway between them.
//     Similarly if the slope is infinite, you know the 𝑥
//     coordinate of the center. You can use this 𝑥
//     or 𝑦 in the line bisecting the segment between the third point
//     and one of the two you have used.
//     in the line bisecting the segment between the third point
//     and one of the two you have used.
    
    Point2D(Eigen::Vector2d init_coordinates,int idx) : idx(idx)  {


        init_coordinates(0) = init_coordinates(0);
        init_coordinates(1) = init_coordinates(1);

        mag = pow(V(0),2) + pow(V(1),2);
        inTriangle = false;
    };

    Point2D()= default;
    Point2D(double x, double y, int idx) : inTriangle(false), idx(idx){
        //Processing coords
        V = Eigen::Vector2d(x,y);

        mag = pow(V(0),2) + pow(V(1),2);
        inTriangle = false;
    };

    Point2D(Eigen::Vector2d coords,bool newInTriangle,int idx): idx(idx) {
        
        V = coords; 
        V(0) = V(0);
        V(1) = V(1);

        inTriangle = newInTriangle; 
        mag = pow(V(0),2) + pow(V(1),2);
    }

   bool operator<(const Point2D& other) const {
            return V.norm() < other.V.norm();
        }

    friend std::ostream& operator<<(std::ostream& os, const Point2D& pt);

    
    bool operator==(const Point2D& other) const {return UTIL::compDouble(this->V(0), other.V(0)) && UTIL::compDouble(this->V(1), other.V(1));}
    
    double dist(Point2D other);

};

#endif /* Point2D_hpp */
