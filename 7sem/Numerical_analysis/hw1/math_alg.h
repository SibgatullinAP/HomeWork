#ifndef MATH_ALG_H
#define MATH_ALG_H

#include "common.h"

using math_vec = std::vector<double>;

void solve_3diag_matrix(const double *l, const double *d, const double *r,
                        const double *rhs, double *answer, unsigned int size);

math_vec solve_3diag_matrix(const math_vec &l, const math_vec &d,
                            const math_vec &r, const math_vec &rhs) {
  math_vec answer(d.size());
  solve_3diag_matrix(l.data(), d.data(), r.data(), rhs.data(), answer.data(),
                     d.size());
  return answer;
}

double norm_c(const double *vector, unsigned int size);
double norm_c(const math_vec &vec) { return norm_c(vec.data(), vec.size()); }

double norm_l2(const double *vector, unsigned int size, double h);
double norm_l2(const math_vec &vec, double h) {
  return norm_l2(vec.data(), vec.size(), h);
}

double norm_w21(const double *vector, unsigned int size, double h);
double norm_w21(const math_vec &vec, double h) {
  return norm_w21(vec.data(), vec.size(), h);
}

#endif // MATH_ALG_H
