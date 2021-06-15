#include "function.h"

const char *enum_to_string (function_type func_type)
{
  switch (func_type)
    {
    case function_type::CONST:
      return "f(x, y) = 1";
    case function_type::LINEAR_X:
      return "f(x, y) = x";
    case function_type::LINEAR_Y:
      return "f(x, y) = y";
    case function_type::LINEAR_X_Y:
      return "f(x, y) = x + y";
    case function_type::SQUARED_X_Y_SQRT:
      return "f(x, y) = sqrt(x^2 + y^2)";
    case function_type::SQUARED_X_Y:
      return "f(x, y) = x^2 + y^2";
    case function_type::EXP_X_Y:
      return "f(x, y) = exp (x^2 - y^2)";
    case function_type::NON_POLYNOM_X_Y:
      return "f(x, y) = 1 / (25 * (x^2 + y^2) + 1)";
    case function_type::COUNT:
      return "Invalid function";
    }
  return "";
}

function_type operator++(function_type &x)
{
  x = (function_type)((std::underlying_type<function_type>::type(x) + 1)
                      % (int) function_type::COUNT);
  return x;
}

std::pair<double, double> find_min_max (double a, double b, std::function<double(double)> func, int pnt_quantity)
{
  double delta = (b - a) / pnt_quantity;
  std::pair<double, double> answer = {0, func (a)};

  double x = a;
  for (int i = 0; i < pnt_quantity; x = a + i * delta, i++)
    {
      double f_x = func (x);
      answer.first = f_x < answer.first ? f_x : answer.first;
      answer.second = f_x > answer.second ? f_x : answer.second;
    }

  return answer;
}

std::function<double(double, double)> residual (std::function<double(double, double)> func
                                                , std::function<double(double, double)> approx)
{
  return [&](double x, double y) {return fabs (func(x, y) - approx(x, y));};
}

double max_of_abs (double a, double b)
{
  return (fabs (a) > fabs (b) ? fabs (a) : fabs (b));
}

function::function (int func_type)
{
  set_func_type ((function_type) func_type);
}

function::function (function_type func_type)
{
  set_func_type (func_type);
}

void function::set_func_type(function_type func_type)
{
  m_func_type = func_type;
  m_func_name = enum_to_string (m_func_type);
  m_func = get_func_by_type (m_func_type);

  m_pertrub_need_to_recalculate = true;
}

std::function<double(double, double)> function::get_func_by_type (function_type func_type)
{
  switch (func_type)
    {
    case function_type::CONST:
      return f_const;
    case function_type::LINEAR_X:
      return f_linear_x;
    case function_type::LINEAR_Y:
      return f_linear_y;
    case function_type::LINEAR_X_Y:
      return f_linear_x_y;
    case function_type::SQUARED_X_Y_SQRT:
      return f_squared_x_y_sqrt;
    case function_type::SQUARED_X_Y:
      return f_squared_x_y;
    case function_type::EXP_X_Y:
      return f_exp_x_y;
    case function_type::NON_POLYNOM_X_Y:
      return f_non_polynom_x_y;
    case function_type::COUNT:
      return {};
    }
  return {};
}

void function::update_pertrub()
{
  m_pertrub_need_to_recalculate = false;

  point_3d a = m_rectangle.get_a ();
  point_3d b = m_rectangle.get_b ();
  point_3d c = m_rectangle.get_c ();

  double hx = (b.m_x - a.m_x) / VISUALIZATION_NX;
  double hy = (a.m_y - c.m_y) / VISUALIZATION_NY;

  m_pertrub_center = {(b.m_x + a.m_x) / 2., (a.m_y + c.m_y) / 2. ,0.};

  double tmp_max = 0;
  for (int i = 0; i < VISUALIZATION_NX + 1; i++)
    for (int j = 0; j < VISUALIZATION_NY + 1; j++)
      tmp_max = fabs (m_func (a.m_x + j * hx, c.m_y + i * hy)) > tmp_max
                ?  fabs (m_func (a.m_x + j * hx, c.m_y + i * hy)) : tmp_max;

  m_func_max = tmp_max;

}

std::function<double(double, double)> function::get_func ()
{
  if (m_pertrub_need_to_recalculate)
    update_pertrub ();

  return [this](double x, double y){
      return m_func(x, y) + (m_func_max * 0.1 * m_pertrub_counter)
          * (fabs (m_pertrub_center.m_x - x) < 1e-4
             && fabs (m_pertrub_center.m_y - y) < 1e-4);
    };
}

void approx_function::update (const domain &rectangle, int nx, int ny, const double *approx_answer)
{
  m_nx = nx;
  m_ny = ny;
  m_rectangle = rectangle;
  m_approx_answer = approx_answer;
}

double approx_function::basis_func (double x1, double y1, double x2, double y2, double x3, double y3, double x0, double y0) const
{
  return ((x0 - x1) * (y3 - y2) +
          (y0 - y1) * (x2 - x3)) / ((x3 - x1) * (y2 - y1) - (x2 -x1) * (y3 - y1)) + 1;
}

int approx_function::find_x (double x, double a, double b, double n) const
{
  if (x <= a) return 0;
  if (x >= b) return n;

  int i = 0, j = n, z = 0;
  double h = (b - a) / n;

  while (i != j)
    {
      z = (i + j) / 2;
      if (x <= a + z * h)
        j = z;
      else
        i = z + 1;
    }

  return i;
}

int approx_function::find_y (double y, double a, double b, double n) const
{
  if (y <= a) return 0;
  if (y >= b) return n;

  int i = 0, j = n, z = 0;
  double h = (b - a) / n;

  while (i != j)
    {
      z = (i + j) / 2;
      if (y <= a + z * h)
        j = z;
      else
        i = z + 1;
    }

  return i - 1;
}

double approx_function::approx_func (double x, double y) const
{
  int i = 0, j = 0;

  double dx = (m_rectangle.get_d ().m_x -  m_rectangle.get_a ().m_x) / m_nx;
  double dy = (m_rectangle.get_a ().m_y - m_rectangle.get_d ().m_y) / m_ny;

  i = find_x (x,  m_rectangle.get_a ().m_x, m_rectangle.get_d ().m_x, m_nx);
  j = m_ny - find_y (y, m_rectangle.get_d ().m_y, m_rectangle.get_a ().m_y, m_ny);

  if (fabs (y - (m_rectangle.get_a ().m_y - dy * j)) < EPS && fabs (x - ( m_rectangle.get_a ().m_x + dx * i)) < EPS)
    {
      return m_approx_answer[(m_ny - j) * (m_nx + 1) + i];
    }

  if (fabs (y - m_rectangle.get_a ().m_y) < EPS/* * max_of_abs (y, m_rectangle.get_a ().m_y)*/)
    {
      double x1 =  m_rectangle.get_a ().m_x + dx * (i - 1);
      double y1 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x2 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y2 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x3 =  m_rectangle.get_a ().m_x + dx * (i - 1);
      double y3 = m_rectangle.get_a ().m_y - dy * (j + 1);

      double ans = m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x1, y1, x3, x3, x, y) +
                   m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i - 1] * basis_func (x1, y1, x2, y2, x3, y3, x, y);
      return ans;
    }

  if (fabs (y - m_rectangle.get_d ().m_y) < EPS /** max_of_abs (y0, m_rectangle.get_d ().m_y)*/)
    {
      double x1 =  m_rectangle.get_a ().m_x + dx * (i - 1);
      double y1 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x2 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y2 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x3 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y3 = m_rectangle.get_a ().m_y - dy * (j - 1);

      double ans = m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x1, y1, x3, x3, x, y) +
                   m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i - 1] * basis_func (x1, y1, x2, y2, x3, y3, x, y);
      return ans;
    }

  if (fabs (x -  m_rectangle.get_a ().m_x) < EPS /** max_of_abs (x0, m_rectangle.get_a ().m_x)*/)
    {
      double x1 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y1 = m_rectangle.get_a ().m_y - dy * (j - 1);

      double x2 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y2 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x3 =  m_rectangle.get_a ().m_x + dx * (i + 1);
      double y3 = m_rectangle.get_a ().m_y - dy * (j - 1);

      double ans = m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x1, y1, x3, x3, x, y) +
                   m_approx_answer[(m_ny - (j - 1)) * (m_nx + 1) + i + 0] * basis_func (x1, y1, x2, y2, x3, y3, x, y);
      return ans;
    }

  if (fabs (x - m_rectangle.get_d ().m_x) < EPS /** max_of_abs (x0, m_rectangle.get_d ().m_x)*/)
    {
      double x1 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y1 = m_rectangle.get_a ().m_y - dy * (j - 1);

      double x2 =  m_rectangle.get_a ().m_x + dx * (i + 0);
      double y2 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double x3 =  m_rectangle.get_a ().m_x + dx * (i - 1);
      double y3 = m_rectangle.get_a ().m_y - dy * (j + 0);

      double ans = m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x1, y1, x3, x3, x, y) +
                   m_approx_answer[(m_ny - (j - 1)) * (m_nx + 1) + i + 0] * basis_func (x1, y1, x2, y2, x3, y3, x, y);
      return ans;
    }

  double x1 =  m_rectangle.get_a ().m_x + dx * (i - 1);
  double y1 = m_rectangle.get_a ().m_y - dy * (j - 1);

  double x2 =  m_rectangle.get_a ().m_x + dx * (i + 0);
  double y2 = m_rectangle.get_a ().m_y - dy * (j - 1);

  double x3 =  m_rectangle.get_a ().m_x + dx * (i - 1);
  double y3 = m_rectangle.get_a ().m_y - dy * (j + 0);

  double x4 =  m_rectangle.get_a ().m_x + dx * (i + 0);
  double y4 = m_rectangle.get_a ().m_y - dy * (j + 0);

  double ro_1 = (x1 - x) * (x1 - x) + (y1 - y) * (y1 - y);
  double ro_2 = (x4 - x) * (x4 - x) + (y4 - y) * (y4 - y);

  if (ro_1 < ro_2)
    {
      double ans = m_approx_answer[(m_ny - (j - 1)) * (m_nx + 1) + i - 1] * basis_func (x1, y1, x2, y2, x3, y3, x, y) +
                   m_approx_answer[(m_ny - (j - 1)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x1, y1, x3, y3, x, y) +
                   m_approx_answer[(m_ny - (j + 0)) * (m_nx + 1) + i - 1] * basis_func (x3, y3, x1, y1, x2, y2, x, y);
      return ans;
    }
  else
    {
      double ans = m_approx_answer [(m_ny - (j + 0)) * (m_nx + 1) + i + 0] * basis_func (x4, y4, x2, y2, x3, y3, x, y) +
                   m_approx_answer [(m_ny - (j - 1)) * (m_nx + 1) + i + 0] * basis_func (x2, y2, x4, y4, x3, y3, x, y) +
                   m_approx_answer [(m_ny - (j + 0)) * (m_nx + 1) + i - 1] * basis_func (x3, y3, x4, y4, x2, y2, x, y);
      return ans;
    }
}

std::function <double(double, double)> approx_function::get_func () const
{
  return [this] (double x, double y) {
      return approx_func (x, y);
    };
}


double f_const (double x, double y) {(void) x; (void) y; return 1.;}
double f_linear_x (double x, double y) {(void) y; return x;}
double f_linear_y (double x, double y) {(void) x; return y;}
double f_linear_x_y (double x, double y) {return x + y;}
double f_squared_x_y_sqrt (double x, double y) {return sqrt(x * x + y * y);}
double f_squared_x_y (double x, double y) {return x * x + y * y;}
double f_exp_x_y (double x, double y) {return exp (x * x - y * y);}
double f_non_polynom_x_y (double x, double y) {return  1 / (25 * (x * x + y * y) + 1);}
