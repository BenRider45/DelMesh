//
//  Circle.hpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 5/9/25.
//

#include "Point2D.hpp"


class Circle {
    
public:
    
    Point2D center;
    float radius;
    
    Circle() { };

    Circle(Point2D init_center, float init_radius) : center(init_center), radius(init_radius) {};


};
