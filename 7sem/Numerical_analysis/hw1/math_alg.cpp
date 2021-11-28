#include "math_alg.h"

void solve_3diag_matrix(const double *l, const double *d, const double *r,
                        const double *rhs, double *answer, unsigned int size) {
  math_vec al(size - 1);
  math_vec be(size - 1);

  al[0] = -r[0] / d[0];
  be[0] = rhs[0] / d[0];
  for (unsigned int i = 1; i <= size - 2; i++) {
    double tmp = d[i] + l[i - 1] * al[i - 1];
    al[i] = -r[i] / tmp;
    be[i] = (rhs[i] - l[i - 1] * be[i - 1]) / tmp;
  }

  answer[size - 1] = (rhs[size - 1] - l[size - 2] * be[size - 2]) /
                     (d[size - 1] + l[size - 2] * al[size - 2]);

  for (unsigned int i = size - 2; i >= 0; i--)
    answer[i] = al[i] * answer[i + 1] + be[i];
}

double norm_c(const double *vector, unsigned int size)   {

  double max = std::abs(vector[0]);
  for (unsigned int m = 1; m < size; m++) {
    double tmp = std::abs(vector[m]);
    max = max > tmp ? max : tmp;
  }

  return max;
}

double norm_l2(const double *vector, unsigned int size, double h) {
  double dot_product =
      (vector[0] * vector[0] + vector[size - 1] * vector[size - 1]) * 0.5;

  for (unsigned int i = 1; i < size - 1; i++)
    dot_product += vector[i] * vector[i];

  return std::sqrt(dot_product * h);
}

double norm_w21(const double *vector, unsigned int size, double h) {
  double dot_product =
      (vector[0] * vector[0] + vector[size - 1] * vector[size - 1]) * 0.5;

  double square_sum = (vector[1] - vector[0]) * (vector[1] - vector[0]) +
                      (vector[size - 1] - vector[size - 2]) *
                          (vector[size - 1] - vector[size - 2]);

  for (unsigned int i = 1; i < size - 1; i++) {
    dot_product += vector[i] * vector[i];
    square_sum += (vector[i + 1] - vector[i]) * (vector[i + 1] - vector[i]);
  }

  return std::sqrt(dot_product * h + square_sum / h);
}
