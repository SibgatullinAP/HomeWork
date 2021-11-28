#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef PI
#define PI    3.141592653589793238463
#endif

// koeficient perenosa

double aa(double t,double x)
{
        return (double)(sin(PI*x));
}

// tochnoe reshenie

double u(double t,double x)
{
        return (double)(exp(t)*cos(PI*x));
}

// pravai chast

double f(double t,double x)
{
return (double)(exp(t)*(cos(PI*x)+PI*cos(2*PI*x)));
}

