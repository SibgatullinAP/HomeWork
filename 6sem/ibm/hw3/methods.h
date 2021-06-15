#ifndef METHODS_H
#define METHODS_H

#include "common.h"
#include "function.h"

typedef std::vector<double> vec;

void solve_matrix (vec &l, vec &d, vec &r, vec &rhs, vec &answer, int n);

class newton
{
private:
  int m_n = 0;
  double m_a = 0;
  double m_b = 0;
  vec m_vec_newton_x = {};
  vec m_vec_newton_y = {};
  function *m_func = nullptr;

public:
  newton () = default;
  void set_func (function *func);
  void update(double a, double b, int n);
  double calc_value (double x);
  std::function<double(double)> get_func ();
  function_type m_curr_func_type = function_type::COUNT;

protected:
  void recalculate ();
};

class spline
{
private:
  int m_n = 0;
  double m_a = 0;
  double m_b = 0;

  vec x = {};
  vec xi = {};
  vec y = {};

  vec rhs = {};
  vec l = {};
  vec d = {};
  vec r = {};

  vec answer = {};

  vec c_1 = {};
  vec c_2 = {};
  vec c_3 = {};

  function *m_func = nullptr;

public:
  spline () = default;
  void set_func (function *func);
  void update(double a, double b, int n);
  double calc_value (double x);
  std::function<double(double)> get_func ();
  function_type m_curr_func_type = function_type::COUNT;

protected:
  void recalculate ();
};

#endif // METHODS_H
