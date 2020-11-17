#include "constants.h"

int solve_bisect (double a, double b, double eps, double *answer,
                  double (*func)(double));

int solve_newton (double x_0, double eps, double *answer,
                  double (*func)(double), double (*deriv)(double));

int solve_chord (double a, double b, double eps, double *answer,
                 double (*func)(double));

int solve_secant (double a, double b, double eps, double *answer,
                 double (*func)(double));
