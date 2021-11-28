#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef PI
#define PI    3.141592653589793238463
#endif

// tochnoe reshenie

double u(double t,double x)
{
        return (double)(exp(t)*cos(PI*x));
}

// pravai chast

double f(double t,double x,double mu)
{
return (double)(exp(t)*(1.+PI*PI*mu)*cos(PI*x)-exp(2*t)*PI*sin(2*PI*x));
}

