#include <gtest/gtest.h>
#include "DelMesh/Point2D.hpp"
#include <fstream>
#include <filesystem>
using std::cout;



TEST(Point2D, object_creation_test ){
    Point2D a = Point2D(10.0,10.0);
    EXPECT_NO_FATAL_FAILURE(cout<<a);
}


TEST(Point2D, coordinate_assignment_test){
    double x = 12.0;
    double y = 15.0;

    Point2D a = Point2D(12.0,15.0);


    ASSERT_EQ(x,a.V(0));
    ASSERT_EQ(y,a.V(1));
}   



