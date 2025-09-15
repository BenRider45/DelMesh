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
    double radius;
    struct Box{
        Point2D XY_MAX;
        Point2D XY_MIN;

    } Box;
    Circle() { };

    Circle(Point2D init_center, double init_radius) : center(init_center), radius(init_radius) {
        Box.XY_MAX.V(0) = init_center.V(0) + init_radius;
        Box.XY_MIN.V(0) = init_center.V(0) - init_radius;

        Box.XY_MAX.V(1) = init_center.V(1) + init_radius;
        Box.XY_MIN.V(1) = init_center.V(1) - init_radius;

    //    std::cout<<"Min X:"<<Box.XY_MIN.V(0)<<"\n";
    };

    friend std::ostream& operator <<(std::ostream& os, const Circle& circ){
        os << "Circle: \n" << "Radius: " << circ.radius << " Center: " << circ.center;
        return os;
    }

};
