#include "constants.h"

int solve_bisect (double a, double b, double eps, double *answer,double (*func)(double));

int solve_newton (double x_0, double eps, double *answer,
                  double (*func)(double), double (*deriv)(double));

int solve_chord (double a, double b, double eps, double *answer, double (*func)(double));

int solve_secant (double a, double b, double eps, double *answer, double (*func)(double));

int solve_inv_squared_interpolation (double a, double b, double eps, double *answer, double (*func)(double));

int solve_m_th_interpolation (double a, double b, double eps, double *d, int m,
                              double *answer, double (*func)(double));

int solve_contraction_mapping (double x_0, double eps, double *answer, double (*func)(double));

int max_auto_steps (double a, double b, double eps, double *answer, double (*func)(double));

int max_golden_secants (double a, double b, double eps, double *answer, double (*func)(double));

int max_squared_interpolations (double a, double b, double eps, double *answer, double (*func)(double));

double sign (double x);
