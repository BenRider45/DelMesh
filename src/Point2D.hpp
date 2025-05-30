//
//  Point2D.hpp
//  Delauney Mesh Generation
//  Helper class which represents a 2D point on in cartesian coordinates
//  Created by Ben Rider on 1/13/25.
//

#ifndef Point2D_hpp
#define Point2D_hpp

#include <stdio.h>
#include <iostream>
#include "Eigen/Dense"


class Point2D {
     
    
public:

    Eigen::Vector2f V;//Point Vector
    
    bool inTriangle;
   
    
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
    
    Point2D(Eigen::Vector2f init_coordinates): V(init_coordinates), inTriangle(false) {};
    Point2D() {};
    Point2D(float x, float y) : V(Eigen::Vector2f(x,y)), inTriangle(false) {};
    Point2D(Eigen::Vector2f coords,bool newInTriangle) {V = coords; inTriangle = newInTriangle; }
    
    friend std::ostream& operator <<(std::ostream& os, const Point2D& pt);
    
    bool operator==(const Point2D& other) const {return this->V == other.V;}
    
    
};

#endif /* Point2D_hpp */
