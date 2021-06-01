#include "function.h"

const char *enum_to_string (function_type func_type)
{
  switch (func_type)
    {
    case function_type::CONST:
      return "F(X) = 1";
    case function_type::LINEAR:
      return "F(X) = x";
    case function_type::QUADRIC:
      return "F(X) = x^2";
    case function_type::CUBIC:
      return "F(X) = x^3";
    case function_type::FOURTH_DEGREE:
      return "F(X) = x^4";
    case function_type::EXP:
      return "F(X) = exp (x)";
    case function_type::NON_POLYNOM:
      return "F(X) = 1 / (25x^2 + 1)";
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

std::function<double(double)> residual (std::function<double(double)> func, std::function<double(double)> approx)
{
  return [&](double x) {return fabs (func(x) - approx(x));};
}

double max_of_abs (double a, double b)
{
  return (fabs (a) > fabs (b) ? fabs (a) : fabs (b));
}

function::function (function_type func_type)
{
  set_func_type (func_type);

  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::CONST, {-1e306, 1e306}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::LINEAR, {-1e306, 1e306}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::QUADRIC, {-1e153, 1e153}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::CUBIC, {-1e100, 1e100}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::FOURTH_DEGREE, {-1e75, 1e75}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::EXP, {-500, 500}));
  m_domain_bounding.insert (std::pair<function_type, std::pair<double, double>> (function_type::NON_POLYNOM, {-1e50, 1e50}));
}


void function::set_func_type(function_type func_type)
{
  m_func_type = func_type;
  m_func_name = enum_to_string (m_func_type);

  m_func = get_func_by_type (m_func_type);
  m_deriv = get_deriv_by_type (m_func_type);
}

void function::set_pertrub_params (optional<double> a, optional<double> b, optional<int> n)
{
  if (a)
    {
      m_a = a.value ();
      m_pertrub_need_to_update = true;
    }
  if (b)
    {
      m_b = b.value ();
      m_pertrub_need_to_update = true;
    }
  if (n)
    {
      m_n = n.value ();
      m_pertrub_need_to_update = true;
    }
}
void function::recalculate_pertrubtaion ()
{
  m_pertrubation = find_min_max (m_a, m_b, m_func, m_n).second;
  m_x_center = m_a + (m_n / 2) * (m_b - m_a) / m_n;
  m_pertrub_need_to_update = false;
}

void function::increase_pertrub ()
{
  m_pertrub_counter++;
}
void function::decrease_pertrub ()
{
  m_pertrub_counter--;
}

double function::get_pertrubation_value ()
{
  if (m_pertrub_need_to_update)
    recalculate_pertrubtaion ();

  return m_pertrubation * 0.1 * m_pertrub_counter;
}

std::function<double(double)> function::get_func ()
{
  if (m_pertrub_need_to_update)
    recalculate_pertrubtaion ();


  return m_func;
//  return [&](double x){
//      return m_func(x) + (fabs(m_x_center - x) < 1e-4 * max_of_abs (x, m_x_center)) * (m_pertrubation * 0.1 * m_pertrub_counter);
//    };
}

std::pair<double, double> function::get_domain_bounds (function_type func_type)
{
  return m_domain_bounding[func_type];
}

function& function::operator++()
{
  m_func_type = (function_type)((std::underlying_type<function_type>::type(m_func_type) + 1) % (int) function_type::COUNT);
  set_func_type (m_func_type);
  m_pertrub_need_to_update = true;
  return *this;
}

std::function<double(double)> function::get_func_by_type (function_type func_type)
{
  switch (func_type)
    {
    case function_type::CONST:
      return f_const;
    case function_type::LINEAR:
      return f_linear;
    case function_type::QUADRIC:
      return f_quadric;
    case function_type::CUBIC:
      return f_qubic;
    case function_type::FOURTH_DEGREE:
      return f_fourth_degree;
    case function_type::EXP:
      return f_exp;
    case function_type::NON_POLYNOM:
      return f_non_polynom;
    case function_type::COUNT:
      return {};
    }
}

std::function<double(double)> function::get_deriv_by_type (function_type func_type)
{
  switch (func_type)
    {
    case function_type::CONST:
      return d_const;
    case function_type::LINEAR:
      return d_linear;
    case function_type::QUADRIC:
      return d_quadric;
    case function_type::CUBIC:
      return d_qubic;
    case function_type::FOURTH_DEGREE:
      return d_fourth_degree;
    case function_type::EXP:
      return d_exp;
    case function_type::NON_POLYNOM:
      return d_non_polynom;
    case function_type::COUNT:
      return {};
    }
}

double f_const (double x) {(void) x; return 1;}
double f_linear (double x) {return x;}
double f_quadric (double x) {return x * x;}
double f_qubic (double x) {return x * x * x;}
double f_fourth_degree (double x) {return x * x * x * x;}
double f_exp (double x) {return exp(x);}
double f_non_polynom (double x) {return 1.0 / (25 * x * x + 1.);}

double d_const (double x) {(void) x; return 0;}
double d_linear (double x) {(void) x; return 1;}
double d_quadric (double x) {return 2 * x;}
double d_qubic (double x) {return 3 * x * x;}
double d_fourth_degree (double x) {return 4 * x * x * x;}
double d_exp (double x) {return exp (x);}
double d_non_polynom (double x) {return -50 * x / ((25 * x * x + 1) * (25 * x * x + 1));}
