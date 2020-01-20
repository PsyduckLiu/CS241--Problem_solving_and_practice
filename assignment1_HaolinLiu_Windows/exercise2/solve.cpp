#include <iostream>
#include "solve.h"

using namespace std;
class noroot {};
class notequation {};
double solve(double a,double b,double c)
{
    if (a==0) throw notequation();
    else {
        double dlt=b*b-4*a*c;
        if (dlt<0) throw noroot();
        else {
            return dlt;
        }
    }
}
