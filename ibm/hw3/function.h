#ifndef FUNCTION_H
#define FUNCTION_H

#include "common.h"

enum class function_type
{
  CONST,
  LINEAR,
  QUADRIC,
  CUBIC,
  FOURTH_DEGREE,
  EXP,
  NON_POLYNOM,

  COUNT
};

using std::optional;

const char *enum_to_string (function_type func_type);
function_type operator++(function_type &x);
std::pair<double, double> find_min_max (double a, double b, std::function<double(double)> func, int pnt_quantity);
std::function<double(double)> residual (std::function<double(double)> func, std::function<double(double)> approx);

double max_of_abs (double a, double b);

class function
{
private:
  function_type m_func_type;
  QString m_func_name;
  std::function<double(double)> m_func;
  std::function<double(double)> m_deriv;
  std::unordered_map<function_type, std::pair<double, double>> m_domain_bounding;

  std::function<double(double)> get_func_by_type (function_type func_type);
  std::function<double(double)> get_deriv_by_type (function_type func_type);

  double m_pertrubation = 0;
  double m_x_center = 0;
  double m_a = 0;
  double m_b = 0;
  int m_n = 0;
  int m_pertrub_counter = 0;
  bool m_pertrub_need_to_update = false;

public:
  function (function_type func_type = function_type::COUNT);
  function& operator++();
  void set_func_type (function_type func_type);

  void set_pertrub_params (optional<double> a, optional<double> b, optional<int> n);
  void recalculate_pertrubtaion ();
  void increase_pertrub ();
  void decrease_pertrub ();
  double get_pertrubation_value ();

  std::pair<double, double> get_domain_bounds (function_type func_type);
  std::function<double(double)> get_func ();
  std::function<double(double)> get_deriv () const {return m_deriv;};
  QString get_func_name () const {return m_func_name;}
  function_type get_func_type () const {return m_func_type;}
};

double f_const (double x);
double f_linear (double x);
double f_quadric (double x);
double f_qubic (double x);
double f_fourth_degree (double x);
double f_exp (double x);
double f_non_polynom (double x);

double d_const (double x);
double d_linear (double x);
double d_quadric (double x);
double d_qubic (double x);
double d_fourth_degree (double x);
double d_exp (double x);
double d_non_polynom (double x);


#endif // FUNCTION_H
