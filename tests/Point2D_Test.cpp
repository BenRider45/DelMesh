#include <gtest/gtest.h>
#include "DelMesh/Point2D.hpp"
#include <fstream>
#include <filesystem>
using std::cout;



TEST(Point2D, object_creation_test ){
    Point2D a = Point2D(10.0,10.0,-1);
    EXPECT_NO_FATAL_FAILURE(cout<<a);
}


TEST(Point2D, coordinate_assignment_test){
    double x = 12.0;
    double y = 15.0;

    Point2D a = Point2D(12.0,15.0,-1);


    ASSERT_EQ(x,a.V(0));
    ASSERT_EQ(y,a.V(1));
}   

TEST(Point2D, obj_equality_test){
    double x1 = 10.0;
    double y1 = 10.0;

    double x2 = 10.0;
    double y2 = 10.0;

    double x3 = 12.0;
    double y3 = 15.0;

    Point2D a(x1,y1,-1);
    Point2D b(x2,y2,-1);
    
    ASSERT_EQ(a,b);

    Point2D c(x3,y3,-1);

    ASSERT_NE(a,c);


}

