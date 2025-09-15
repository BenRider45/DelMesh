#include <gtest/gtest.h>
#include "DelMesh/Triangle.hpp"
#include "DelMesh/Point2D.hpp"

using std::cout;


TEST(Triangle, object_creation_test){
    Point2D a = Point2D(-10,0);
    Point2D b = Point2D(0,10);
    Point2D c = Point2D(0, (sqrt(3)/2.0)*10);

    Triangle t = Triangle(a,b,c);
    EXPECT_NO_FATAL_FAILURE(cout<<t);
}

TEST (Triangle, equality_test){
    
    Point2D a = Point2D(-15.0,5.0);
    Point2D b = Point2D(15.0,0.0);
    Point2D c = Point2D(0.0, 10.0);

    Point2D a2 = Point2D(-15.0,5.0);
    Point2D b2 = Point2D(15.0,0.0);
    Point2D c2 = Point2D(0.0, 10.0);

    Triangle t(a,b,c);
    Triangle t2(a,b,c);

    ASSERT_EQ(t,t2);

}
TEST(Triangle, circumcircle_calculation_test){

    Point2D a = Point2D(-15.0,5.0);
    Point2D b = Point2D(15.0,0.0);
    Point2D c = Point2D(0.0, 10.0);

    Triangle t = Triangle(a,b,c);

    Point2D CALCULATED_CC_CENTER = Point2D(-1.9444444444444444, -9.166666666666666);

    double CALCULATED_CC_RADIUS = 19.265045427110778;


    ASSERT_EQ(CALCULATED_CC_CENTER.V(0),t.circle.center.V(0));
    ASSERT_DOUBLE_EQ(CALCULATED_CC_CENTER.V(1),t.circle.center.V(1));

    ASSERT_EQ(CALCULATED_CC_CENTER,t.circle.center);
    ASSERT_EQ(CALCULATED_CC_RADIUS,t.circle.radius);


}

TEST(Triangle, in_circle_test){
    Point2D a = Point2D(-10,0);
    Point2D b = Point2D(10,0);
    Point2D c = Point2D(0, sqrt(3)*10);

    Point2D d = Point2D(0,5); //Point that is inside this triangles circumcircle
    Triangle t = Triangle(a,b,c);
    ASSERT_TRUE(t.checkIncircle(d));

    Point2D e = Point2D(123456,12345678); //Point that is definitely outside this triangles circumcircle
    ASSERT_FALSE(t.checkIncircle(e));

}

TEST(Triangle, correct_wrong_orientation_test){
    Point2D a = Point2D(-10,0);
    Point2D c = Point2D(10,0);
    Point2D b = Point2D(0, (sqrt(3)/2.0)*10);
 
    Triangle t = Triangle(a,b,c); //These Points are in an incorrect orientation (c is to the left of directed line ab)

    ASSERT_NE(b,t.b);
    ASSERT_NE(c,t.c); //Points B and C should be swapped Now

    ASSERT_EQ(b,t.c);   
    ASSERT_EQ(c,t.b);

}

TEST(Triangle, dont_correct_right_orientation_test){
    Point2D a = Point2D(-10,0);
    Point2D b = Point2D(10,0);
    Point2D c = Point2D(0, (sqrt(3)/2.0)*10);

    Triangle t = Triangle(a,b,c); //These Points are in an incorrect orientation (c is to the left of directed line ab)

    ASSERT_NE(b,t.c);
    ASSERT_NE(c,t.b); //Points B and C should be swapped Now

    ASSERT_EQ(b,t.b);
    ASSERT_EQ(c,t.c);


}

TEST(Triangle, area_calc_test){
    Point2D a = Point2D(-10,0);
    Point2D b = Point2D(10,0);
    Point2D c = Point2D(0, (sqrt(3))*10);
    Triangle t = Triangle(a,b,c);

    double TEST_TRIANGLE_AREA = .5 * ((a.V(0)*b.V(1) + b.V(0)*c.V(1)+ c.V(0)*a.V(1)) - (a.V(1)*b.V(0)+b.V(1)*c.V(0)+c.V(1)*a.V(0)));
    
    ASSERT_DOUBLE_EQ(t.area,TEST_TRIANGLE_AREA);
}


