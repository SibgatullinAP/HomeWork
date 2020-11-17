#include "constants.h"

int read (char *file_name, int array_length, double *arr);
void print (int array_length, double *arr);

double lagr_interpolation (int array_length, double x_0, double *x, double *y);
double lagr_interpolation_div_diff (int array_length, double x_0, double *x, double *y);
double lagr_interpolation_deriv (int array_length, double x_0, double *x, double *y, double *d);
