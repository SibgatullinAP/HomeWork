#include "math_alg.h"

math_vec vec_diffs(const math_vec &lhs, const math_vec &rhs) {
  if (lhs.size() - rhs.size())
    printf("lhs != rhs\n");

  math_vec result(lhs.size());
  for (unsigned int i = 0; i < lhs.size(); i++)
    result[i] = lhs[i] - rhs[i];

  return result;
}

void solve_matrix(double *l, double *d, double *r, double *rhs,
                        double *answer, unsigned int size) {
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

  for (int i = size - 2; i >= 0; i--)
    answer[i] = al[i] * answer[i + 1] + be[i];


  CGS(std::vector<math_vec> {math_vec(l), math_vec(d), math_vec(r)}, math_vec(answer), math_vec (rhs), 2000, NEARZERO);
}

math_vec solve_matrix(math_vec &l, math_vec &d, math_vec &r,
                            math_vec &rhs) {
  math_vec answer(d.size());
  solve_matrix(l.data(), d.data(), r.data(), rhs.data(), answer.data(),
                     d.size());
  return answer;
}

double norm(const double *vector, unsigned int size) {

  double max = std::abs(vector[0]);
  for (unsigned int m = 1; m < size; m++) {
    double tmp = std::abs(vector[m]);
    max = max > tmp ? max : tmp;
  }

  return max;
}
double norm(const math_vec &vec) { return norm_c(vec.data(), vec.size()); }

double norm_c(const double *vector, unsigned int size) {

  double max = std::abs(vector[0]);
  for (unsigned int m = 1; m < size; m++) {
    double tmp = std::abs(vector[m]);
    max = max > tmp ? max : tmp;
  }

  return max;
}
double norm_c(const math_vec &vec) { return norm_c(vec.data(), vec.size()); }

double norm_l2(const double *vector, unsigned int size, double h) {
  double dot_product =
      (vector[0] * vector[0] + vector[size - 1] * vector[size - 1]) * 0.5;

  for (unsigned int i = 1; i < size - 1; i++)
    dot_product += vector[i] * vector[i];

  return std::sqrt(dot_product * h);
}
double norm_l2(const math_vec &vec, double h) {
  return norm_l2(vec.data(), vec.size(), h);
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
double norm_w21(const math_vec &vec, double h) {
  return norm_w21(vec.data(), vec.size(), h);
}

int CGS(const math_matr &A, math_vec &x, const math_vec &b, int &max_iter, double &tol)
{
  double resid;
  math_vec rho_1(1), rho_2(1), alpha(1), beta(1);
  math_vec p, phat, q, qhat, vhat, u, uhat;

  double normb = norm(b);
  math_vec r = b - A*x;
  math_vec rtilde = r;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) {
    rho_1(0) = dot(rtilde, r);
    if (rho_1(0) == 0) {
      tol = norm(r) / normb;
      return 2;
    }
    if (i == 1) {
      u = r;
      p = u;
    } else {
      beta(0) = rho_1(0) / rho_2(0);
      u = r + beta(0) * q;
      p = u + beta(0) * (q + beta(0) * p);
    }
    phat = M.solve(p);
    vhat = A*phat;
    alpha(0) = rho_1(0) / dot(rtilde, vhat);
    q = u - alpha(0) * vhat;
    uhat = M.solve(u + q);
    x += alpha(0) * uhat;
    qhat = A * uhat;
    r -= alpha(0) * qhat;
    rho_2(0) = rho_1(0);
    if ((resid = norm(r) / normb) < tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
  }

  tol = resid;
  return 1;
}
