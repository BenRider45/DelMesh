#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include "UTIL.hpp"
#include <iomanip>
#include <cmath>
#include <limits>



    

bool UTIL::compDouble(double x, double y){
    return (abs(x-y) <= UTIL::EPSILON * std::max(abs(x),abs(y)));
}   


double UTIL::cint(double x){    
	double test =  std::fmod(x,0);

    if (test>=.5)
		return x>=0 ? std::ceil(x) : std::floor(x);
	else
		return x<0?std::ceil(x):std::floor(x);
}

double UTIL::round(double r,int places){
	double off=std::pow(10,places);
	return UTIL::cint(r*off)/off;
}

double UTIL::roundNDec(double x,int n ){
    std::cout<<"\n===========ROUNDNDEC CALL===========\n"

    << std::setprecision(std::numeric_limits<long double>::digits10) 
    <<"Input x: "<<x<<"\n"<<"Input n: "<<n<<"\n";

    double multiplier = std::pow(10.0, n);  
    std::cout<<"Multiplier: "<<multiplier<<"\n";
    double output = multiplier * x;
    
    int firstDecVal =fmod((output * 10),10);
    std::cout<<"firstDecVal: "<<firstDecVal<<"\n";

    output += firstDecVal <= 4 ? -1 : 1;
    std::cout<< "Output: " << output <<"\n";

    output = fmod(output,1);

    std::cout << "Output Again: "<< output<< "\n";

    std::cout << "out/mult: "<<output/multiplier<<"\n";
    std::cout<<"\n=========END ROUNDNDEC CALL=========\n";

    return output/multiplier;

}







