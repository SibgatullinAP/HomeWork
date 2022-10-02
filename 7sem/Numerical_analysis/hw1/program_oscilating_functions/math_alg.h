#ifndef MATH_ALG_H
#define MATH_ALG_H

#include "common.h"

using math_vec = std::vector<double>;

math_vec vec_diffs (const math_vec &lhs, const math_vec &rhs);

void solve_3diag_matrix(const double *l, const double *d, const double *r,
                        const double *rhs, double *answer, unsigned int size);

void solve_3diag_matrix(double *l, double *d, double *r,
                        double *rhs, double *answer, unsigned int size);


math_vec solve_3diag_matrix(math_vec &l, math_vec &d,
                            math_vec &r, math_vec &rhs);

//math_vec solve_3diag_matrix(const math_vec &l, const math_vec &d,
//                            const math_vec &r, const math_vec &rhs);

double norm_c(const double *vector, unsigned int size);
double norm_c(const math_vec &vec);

double norm_l2(const double *vector, unsigned int size, double h);
double norm_l2(const math_vec &vec, double h);

double norm_w21(const double *vector, unsigned int size, double h);
double norm_w21(const math_vec &vec, double h);

#endif // MATH_ALG_H
