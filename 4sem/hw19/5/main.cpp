#include <stdio.h>
#include <math.h>

double f1(double x, double y, double a)
{
    return (exp(-1.0*(x/(sqrt(1.0+x*x)) + cos(y) -1) * (x/(sqrt(1.0+x*x)) + cos(y) -1)))/(1.0+a*a);
}

double f2(double x, double y, double a)
{
    (void) a ;
    return ((-1.0)/(3.0)) * (1.0/(1.0 + y*y) + (x*x)/(2*sqrt(1.0+x*x)));
}

int main(int argc, char *argv[])
{
    double eps = 0;
    double a = 0;
    int itter_max = 1000;
    if(argc != 3 || (sscanf(argv[1], "%lf", &a) != 1) || (sscanf(argv[2], "%le", &eps) != 1))
    {
	printf("Incorrect input values, please use:\n%s a eps\n", argv[0]);
	return -1;
    }
    double x0 = 0;
    double y0 = 0;
    double x1 = f1(x0,y0,a);
    double y1 = f2(x0,y0,a);
    int i = 0;
    while ( i < itter_max && (sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1)) > eps))
    {
	i++;
	x0 = x1;
	y0 = y1;

	x1 = f1(x0,y0,a);
	y1 = f2(x0,y0,a);
    }
    printf("Result:\n");
    printf("x = %0.12e\ny = %0.12e\n", x1,y1);
    printf("Error = %.12e\n",(sqrt((x0-x1)*(x0-x1) + (y0-y1)*(y0-y1))))	;
    printf("Quantity of itteration = %d\n", i);

    return 0;
}
