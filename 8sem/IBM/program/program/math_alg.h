#ifndef MATH_ALG_H
#define MATH_ALG_H

#include "common.h"

using math_vec = std::vector<double>;
using math_matr = std::vector<math_vec>;

math_vec vec_diffs (const math_vec &lhs, const math_vec &rhs);

void solve_matrix(const double *l, const double *d, const double *r,
                        const double *rhs, double *answer, unsigned int size);

void solve_matrix(double *l, double *d, double *r,
                        double *rhs, double *answer, unsigned int size);


math_vec solve_matrix(math_vec &l, math_vec &d,
                            math_vec &r, math_vec &rhs);

int CGS(const math_matr &A, math_vec &x, const math_vec &b, int &max_iter, double &tol);

double norm(const double *vector, unsigned int size);
double norm(const math_vec &vec);

double norm_c(const double *vector, unsigned int size);
double norm_c(const math_vec &vec);

double norm_l2(const double *vector, unsigned int size, double h);
double norm_l2(const math_vec &vec, double h);

double norm_w21(const double *vector, unsigned int size, double h);
double norm_w21(const math_vec &vec, double h);

#endif // MATH_ALG_H
