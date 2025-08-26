//
//  main.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/13/25.
//
//TODO:
// Make Triangle data structure
// Write SuperTriangle calculation algo
// Write orientation check
// Write incircle
#include <iostream>
#include "DelMesh/Point2D.hpp"
#include "DelMesh/DelMesh.hpp"
#include "DelMesh/UTIL.hpp"
#include <iomanip>
#include <limits>
int main(int argc, const char * argv[]) {


    Point2D testPoint = Point2D(3.4214,2.6667543);
    
    DelMesh Mesh = DelMesh();
    Point2D MAX_XY = Point2D(10, 10);
    Point2D MIN_XY = Point2D(-10,-10);
   // std::string fPath =  + "/Delauney Mesh\s Generation/External";

   //TESTING SEED
   //std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),4,100,"../PointFiles/TestPointFil3e.txt");

    std::string pointFPath = Mesh.generateRandPtLst(MIN_XY.V(0),MAX_XY.V(0),MIN_XY.V(1),MAX_XY.V(1),10,10,"../PointFiles/TestPointFil4e.txt");
    
    Mesh.pointList = Mesh.readPointListFromFile(pointFPath);
    Mesh.pointList = Mesh.radialSort(Mesh.pointList);

    for(int i=0; i<Mesh.pointList.size(); i++){
        std::cout<<Mesh.pointList[i]<<"\n";

    }
    // Point2D a = Point2D(-10,0);
    // Point2D b = Point2D(10,0);
    // Point2D c = Point2D(0,20);

    // Triangle t = Triangle(a,b,c);

    // Point2D inTriangle = Point2D(0,5);

    // std::cout<<"inTriangle checkIncircle:"<<t.checkIncircle(inTriangle)<<"\n";

    // Point2D outTriangle = Point2D(0,30);

    // double test = 1.22222511642;
    // double test2= 1.1521251253;

    


    // double test = 1.44444444448;
    


    double roundedTest = 1.444444445;
    // std::cout<<"Tetst";
    // std::cout<<"round(test): "<<std::setprecision(std::numeric_limits<long double>::digits10) << UTIL::round(test,4)<< "\n";

    // std::cout<<"\n";
    // std::cout << "Rounded test 2 decimals: "<< UTIL::round(test,4)<< "\n";
    // std::cout << std::setprecision(std::numeric_limits<long double>::digits10)
    // << "Test: " << test<< '\n' << "Rounded Test: "<< UTIL::round(test) 
    // << "\nRounded Test Check: "<<roundedTest<<"\n";

    

    //std::cout<<"outTriangle checkIncircle:"<<t.checkIncircle(outTriangle)<<"\n";

    Triangle supTriang = Mesh.getSuperTriang(MAX_XY,MIN_XY);
    std::cout<< supTriang;

    Mesh.findMaxMin();
    std::sort(Mesh.pointList.begin(), Mesh.pointList.end());
    std::cout<< "sorted Pointlist: \n";
    for(Point2D pnt : Mesh.pointList){
        std::cout <<pnt<<"\n";
    }    






    std::system("python3 ../src/computations.py");
    //std::vector<Triangle> m = Mesh.BowyerWatson(Mesh.pointList,supTriang);





    return 0;
}                            

