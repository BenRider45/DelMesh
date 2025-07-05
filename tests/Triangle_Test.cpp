#include <gtest/gtest.h>
#include "DelMesh/Triangle.hpp"
#include "DelMesh/Point2D.hpp"

using std::cout;
TEST(Triangle, object_creation_test){
    Point2D a = Point2D(-10,0);
    Point2D b = Point2D(0,10);
    Point2D c = Point2D(0, (sqrt(3)/2)*10);

    Triangle t = Triangle(a,b,c);
    EXPECT_NO_FATAL_FAILURE(cout<<t);
    
}