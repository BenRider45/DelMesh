//
//  Point2D.cpp
//  Delauney Mesh Generation
//  
//  Created by Ben Rider on 1/13/25.
//

#include "Point2D.hpp"
#include <iostream>

    
    
std::ostream& operator <<(std::ostream& os, const Point2D& pt){
    os << "["<<pt.V(0)<<","<<pt.V(1)<<"]";
    return os;
}




