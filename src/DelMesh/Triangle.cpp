
//  Triangle.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#include "Triangle.hpp"
#include <cmath>


Circle Triangle::computeCircumcircle(){
    int A_idx, B_idx=0; 
    //In the case that one of the edges, of our triangle has a slope of 0, 
    //its perpendicular bisector will have an infinite slope, making is
    //incompatible with our current method of calculating the center of our circle
    //This loop ensures we will never choose a side with a slope of 0.
    
    for(int i=0; i<3; i++){
        std::cout << "this->Edges.at(i).slope:" << this->Edges.at(i).slope << "\n";
        std::cout << "this->Edges.at(i).SLOPE_ZERO: " << this->Edges.at(i).SLOPE_ZERO << "\n"; 
        if(this->Edges.at(i).SLOPE_ZERO){
            
            std::cout <<"index i: "<< i << "\n";
            A_idx = i-1;
            B_idx = i+1;
            if(A_idx == -1){A_idx = 2; }
            if(B_idx == 3) { B_idx = 0;}
            break;
            //There can only be at most one edge with a slope of 0
        }
        
    }
    std::cout << "A_idx: "<< A_idx << "\n";
    std::cout << "B_idx: "<< B_idx << "\n";

    std::cout << "============\n";



    Edge A = this->Edges.at(A_idx);
    std::cout << "Edge at A_idx: " << A << '\n'; 

    double A_perpM;
    if(A.SLOPE_INF){
        A_perpM = 0;
    }else{
        A_perpM = -1/A.slope;
    }

    
    Edge B = this->Edges.at(B_idx);
    std::cout << "Edge at B_idx: " << B << '\n'; 

    double B_perpM;
    if(B.SLOPE_INF){
        B_perpM = 0;
    }else{
        B_perpM = -1/B.slope;
    }
    
    
    double denom = B_perpM - A_perpM;
    double X_Num = (B_perpM*B.midPt.V(0)) - (A_perpM*A.midPt.V(0)) + (A.midPt.V(1) - B.midPt.V(1));
    double Y_Num = (pow(B_perpM,2)*B.midPt.V(0)) - (A_perpM*B_perpM*A.midPt.V(0)) + B_perpM*(A.midPt.V(1) - B.midPt.V(1));
    double Y_Res = -B_perpM*B.midPt.V(0) + B.midPt.V(1);
        
    double CircCenter_X =  X_Num / denom;
    double CircCenter_Y = (Y_Num /denom) + Y_Res;
    Point2D CirclePoint = Point2D(CircCenter_X,CircCenter_Y);
    double CircleRadius = sqrt(pow((CircCenter_X - A.a.V(0)),2)+ pow((CircCenter_Y - A.a.V(1)),2));
    Circle output = Circle(CirclePoint,CircleRadius);

    if(!CircleRadius ){
        std::cout<<"Circle Radius Null: " << CircleRadius<<"\n"; 
    }

    return output;
    
}


bool Triangle::checkIncircle(Point2D d){
     
    // Compute determinate here, build matrix with eigen like github example
    Eigen::Matrix4f mat;
    mat << a.V(0), a.V(1), a.mag, 1,
           b.V(0), b.V(1), b.mag, 1,
           c.V(0), c.V(1), c.mag, 1,
           d.V(0), d.V(1), d.mag, 1;
    

    return mat.determinant()>0; 

}

int Triangle::checkOrient(){
    //Computing the determinate of 3x3 matrix:
    // |a_x b_x c_x|
    // |a_y b_y c_y|
    // |1   1   1  |

    double det = b.V(0)*(c.V(1)-a.V(1)) + a.V(0)*(b.V(1)-c.V(1)) + c.V(0)*(a.V(1)- b.V(1));
        
    return det==0 ? 0 : (det>0 ? 1 : -1);
}

int Triangle::correctOrient(){
    if(checkOrient() <0){
        Point2D temp = b;
        b = c;
        c = temp;
        return -1;
    }
    return 1;

}
