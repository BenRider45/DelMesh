#include <stdlib.h>
#include <algorithm>

#pragma once
class UTIL{
    public:
        static int const NUM_DECIMALS = 10;
        constexpr static double const EPSILON = 10.0e-12;
        static bool compDouble(double x, double y);
        static double roundNDec(double x, int n=NUM_DECIMALS);
        static double cint(double x);
        static double round(double r,int places=NUM_DECIMALS);
};