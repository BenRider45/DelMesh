
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
        if(this->Edges.at(i).slope==0.0){
            A_idx = i-1;
            B_idx = i+1;
            if(A_idx == -1){A_idx = 2; }
            if(B_idx == 3) { B_idx = 0;}
            break;
            //There can only be at most one edge with a slope of 0
        }
        
    }



    Edge A = this->Edges.at(A_idx);
    float A_perpM;
    if(A.SLOPE_INF){
        A_perpM = 0;
    }else{
        A_perpM = -1/A.slope;
    }

    
    Edge B = this->Edges.at(B_idx);
    float B_perpM;
    if(B.SLOPE_INF){
        B_perpM = 0;
    }else{
        B_perpM = -1/B.slope;
    }
    
    float denom = B_perpM - A_perpM;
    float X_Num = (B_perpM*B.midPt.V(0)) - (A_perpM*A.midPt.V(0)) + (A.midPt.V(1) - B.midPt.V(1));
    float Y_Num = (pow(B_perpM,2)*B.midPt.V(0)) - (A_perpM*B_perpM*A.midPt.V(0)) + B_perpM*(A.midPt.V(1) - B.midPt.V(1));
    float Y_Res = -B_perpM*B.midPt.V(0) + B.midPt.V(1);
        
    float CircCenter_X = X_Num / denom;
    float CircCenter_Y = (Y_Num /denom) + Y_Res;
    Point2D CirclePoint = Point2D(CircCenter_X,CircCenter_Y);
    float CircleRadius = sqrt(pow((CircCenter_X - A.a.V(0)),2)+ pow((CircCenter_Y - A.a.V(1)),2));
    Circle output = Circle(CirclePoint,CircleRadius);

    if(CircleRadius == NULL){
        std::cout<<"Circle Radius Null: " << CircleRadius<<"\n"; 
    }

    return output;
    
}


bool Triangle::checkIncircle(Point2D d){
     
    // Compute determinate here, build matrix with eigen like github example


    return true;

}
