#include "constants.h"

double integral_trapeze (double a, double b, int n, double (*func)(double));
double integral_simpson (double a, double b, int n, double (*func)(double));

int integral_trapeze_auto_steps (double a, double b, double eps, double *answer, double (*func)(double));
int integral_simpson_auto_steps (double a, double b, double eps, double *answer, double (*func)(double));

double improper_integral (double a, double eps, double *answer, double (*func)(double),
                          int (*integral) (double, double, double, double *, double (*)(double)));

int length (double a, double b, double eps, double *answer, double (*func_x)(double), double (*func_y)(double));
