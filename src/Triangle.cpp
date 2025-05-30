//
//  Triangle.cpp
//  Delauney Mesh Generation
//
//  Created by Ben Rider on 1/15/25.
//

#include "Triangle.hpp"
#include <cmath>


Circle Triangle::computeCircumcircle(){
    int A_idx, B_idx; 
    for(int i=0; i>3; i++){
        if(this->Edges[i].slope==0){
            int A_idx = i-1;
            int B_idx = i+1;
            if(A_idx == -1){A_idx = 2; }
            if(B_idx == 3) { B_idx = 0;}
            //There can only be at most one edge with a slope of 0
        }
        
    }
    Edge A = this->Edges[A_idx];
    float A_perpM;
    if(A.SLOPE_INF){
        A_perpM = 0;
    }else{
        A_perpM = -1/A.slope;
    }

    
    Edge B = this->Edges[B_idx];
    float B_perpM;
    if(B.SLOPE_INF){
        B_perpM = 0;
    }else{
        B_perpM = -1/B.slope;
    }
    
    float denom = B_perpM - A_perpM;
    float X_Num = (B_perpM*B.mdpt.V(0)) - (A_perpM*A.mdpt.V(0)) + (A.mdpt.V(1) - B.mdpt.V(1));
    float Y_Num = (pow(B_perpM,2)*B.mdpt.V(0)) - (A_perpM*B_perpM*A.mdpt.V(0)) + B_perpM*(A.mdpt.V(1) - B.mdpt.V(1));
    float Y_Res = -B_perpM*B.mdpt.V(0) + B.mdpt.V(1);
    
     
    //Compute Inverse of slopes (check for inf slope case)
    //use ComputeMdpt function to get midpoints
    //compute circle X and Y
    //compute radius (distance between center and any vertex)
`   //Create Circle Object
    return Circle();
    
}


bool Triangle::isPointInCircumcircle(){
     
    // Compute determinate here, build matrix with eigen like github example


}
