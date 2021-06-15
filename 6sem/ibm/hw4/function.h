#ifndef FUNCTION_H
#define FUNCTION_H

#include "common.h"
#include "domain.h"

enum class function_type
{
  CONST, // f(x,y) = 1
  LINEAR_X, // f(x,y) = x
  LINEAR_Y, // f(x,y) = y
  LINEAR_X_Y, // f(x,y) = x + y
  SQUARED_X_Y_SQRT, // f(x,y) = sqrt(x^2 + y^2)
  SQUARED_X_Y, // f(x,y) = x^2 + y^2
  EXP_X_Y, // f(x,y) = exp (x^2 - y^2)
  NON_POLYNOM_X_Y, //f(x,y) = 1 / (25 * (x^2 + y^2) + 1)

  COUNT
};

using std::optional;

const char *enum_to_string (function_type func_type);
function_type operator++(function_type &x);
std::pair<double, double> find_min_max (double a, double b, std::function<double(double)> func, int pnt_quantity);
std::function<double(double, double)> residual (std::function<double(double, double)> func
                                                , std::function<double(double, double)> approx);

double max_of_abs (double a, double b);

class function
{
private:
  function_type m_func_type;
  QString m_func_name;
  std::function<double(double, double)> m_func;

  domain m_rectangle = {};
  int m_pertrub_counter = 0;
  point_3d m_pertrub_center = {};
  double m_func_max = 0;
  bool m_pertrub_need_to_recalculate = true;

public:
  function (int func_type);
  function (function_type func_type = function_type::CONST);
  function& operator++();
  void set_func_type (function_type func_type);
  void set_domain (const domain &rectangle) {m_rectangle = rectangle;}

  void update_pertrub ();
  void increase_pertrub () { m_pertrub_counter++;}
  void decrease_pertrub () { m_pertrub_counter--;}
  double get_pertrub () {return 0.1 * m_func_max * m_pertrub_counter;}

  std::function<double(double, double)> get_func ();
  QString get_func_name () const {return m_func_name;}
  function_type get_func_type () const {return m_func_type;}

protected:
  std::function<double(double, double)> get_func_by_type (function_type func_type);
};

class approx_function
{
  int m_nx = 0;
  int m_ny = 0;
  domain m_rectangle = {};
  const double *m_approx_answer = nullptr;

public:
  approx_function () = default;
  ~approx_function () = default;

  void update (const domain &rectangle, int nx, int ny, const double *approx_answer);
  double basis_func (double x1, double y1, double x2, double y2, double x3, double y3, double x0, double y0) const;
  int find_x (double x, double a, double b, double n) const;
  int find_y (double y, double a, double b, double n) const;
  double approx_func (double x, double y) const;
  std::function <double(double, double)> get_func () const;
};

double f_const (double x, double y);
double f_linear_x (double x, double y);
double f_linear_y (double x, double y);
double f_linear_x_y (double x, double y);
double f_squared_x_y_sqrt (double x, double y);
double f_squared_x_y (double x, double y);
double f_exp_x_y (double x, double y);
double f_non_polynom_x_y (double x, double y);

#endif // FUNCTION_H
