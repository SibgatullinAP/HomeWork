#include "methods.h"
#include "function.h"

void solve_matrix (vec &l, vec &d, vec &r, vec &rhs, vec &answer, int n)
{
  for (int i = 0; i < n - 1; i++)
    {
      r[i] /= d[i];
      rhs[i] /= d[i];
      d[i + 1] -= r[i] * l[i + 1];
      rhs[i + 1] -= rhs[i] * l[i + 1];
    }

  rhs[n - 1] /= d[n - 1];

  for (int i = n - 1; i > 0; i--)
    rhs[i - 1] -= rhs[i] * r[i - 1];

  for (int i = 0; i < n; i++)
    answer[i] = rhs[i];
}

void newton::set_func (function *func)
{
  m_func = func;
  m_curr_func_type = m_func->get_func_type ();
}

void newton::update(double a, double b, int n)
{
  bool need_to_recalculate = false;
  if (m_func->get_func_type () != m_curr_func_type)
    {
      m_curr_func_type = m_func->get_func_type ();
      need_to_recalculate = true;
    }

  if (n != m_n )
    {
      m_vec_newton_x.resize (n);
      m_vec_newton_y.resize (n);
      m_n = n;

      need_to_recalculate = true;
    }

  if (fabs (m_a - a) > EPS * max_of_abs (a, m_a)
      || fabs (m_b - b) > EPS * max_of_abs (b, m_b))
    {
      need_to_recalculate = true;

      m_a = a;
      m_b = b;
    }

  if (need_to_recalculate)
    recalculate ();
}

void newton::recalculate ()
{
  auto func = m_func->get_func ();
  double delta = (m_b - m_a) / (m_n - 1);

  for (int i = 0; i < m_n; i++)
    {
      m_vec_newton_x[i] = m_a + delta * i;
      m_vec_newton_y[i] = func (m_a + delta * i);
    }

  m_vec_newton_y[m_n / 2] += m_func->get_pertrubation_value ();

  (void) 0;
  for (int i = 1; i < m_n; i++)
    for (int j = m_n - 1; j >= i; j--)
      m_vec_newton_y[j] = (m_vec_newton_y[j] - m_vec_newton_y[j - 1]) / (m_vec_newton_x[j] - m_vec_newton_x[j - i]);
}


double newton::calc_value (double x)
{
  double answer = 0;

  for (int i = m_n - 2; i >= 0; i--)
    {
      answer += m_vec_newton_y[i + 1];
      answer *= (x - m_vec_newton_x[i]);
    }
  answer += m_vec_newton_y[0];

  return answer;
}


std::function<double(double)> newton::get_func ()
{
  return [&](double x){
      return calc_value (x);
    };
}

void spline::set_func (function *func)
{
  m_func = func;
  m_curr_func_type = m_func->get_func_type ();
}

void spline::update(double a, double b, int n)
{
  bool need_to_recalculate = false;
  if (m_func->get_func_type () != m_curr_func_type)
    {
      m_curr_func_type = m_func->get_func_type ();
      need_to_recalculate = true;
    }

  if (n != m_n)
    {
      m_n = n;
      x.resize (m_n);
      xi.resize (m_n + 1);
      y.resize (m_n);

      rhs.resize (m_n + 1);
      l.resize (m_n + 1);
      d.resize (m_n + 1);
      r.resize (m_n + 1);

      answer.resize (m_n + 1);

      c_1.resize (m_n + 1);
      c_2.resize (m_n + 1);
      c_3.resize (m_n + 1);

      need_to_recalculate = true;
    }

  if (fabs (m_a - a) > EPS * max_of_abs (a, m_a)
      || fabs (m_b - b) > EPS * max_of_abs (b, m_b))
    {
      need_to_recalculate = true;

      m_a = a;
      m_b = b;
    }
  if (need_to_recalculate)
    recalculate ();
}

void spline::recalculate ()
{
  auto func = m_func->get_func ();
  auto deriv = m_func->get_deriv ();

  double delta = (m_b - m_a) / (m_n - 1);
  for (int i = 0; i < m_n; i++)
    {
      x[i] = m_a + delta * i;
      y[i] = func (m_a + delta * i);
    }

  y[m_n / 2] += m_func->get_pertrubation_value ();

  xi[0] = m_a - delta / 2;

  for (int i = 1; i < m_n; i++)
    xi[i] = (x[i] + x[i - 1]) / 2;

  xi[m_n] = m_b + delta / 2;


  l[0] = 0;
  d[0] = (1 / (xi[1] - xi[0])) - (1 / (x[0] - xi[0]));
  r[0] = (1 / (xi[1] - x[0])) - (1 / (xi[1] - xi[0]));
  rhs[0] = deriv(x[0]) - ((1 / (x[0] - xi[0])) - (1 / (xi[1] - x[0]))) * y[0];


  for (int i = 1; i < m_n; i++)
    {
      l[i] = (1 / (x[i - 1] - xi[i - 1])) - (1 / (xi[i] - xi[i - 1]));

      d[i] = (1 / (xi[i] - x[i - 1])) + (1 / (xi[i] - xi[i - 1]))
          + (1 / (x[i] - xi[i])) + (1 / (xi[i + 1] - xi[i]));

      r[i] = (1 / (xi[i + 1] - x[i])) - (1 / (xi[i + 1] - xi[i]));

      rhs[i] = ((1 / (x[i - 1] - xi[i - 1])) + (1 / (xi[i] - x[i - 1]))) * y[i - 1]
          + ((1 / (x[i] - xi[i])) + (1 / (xi[i + 1] - x[i]))) * y[i];
    }

  l[m_n] = (1 / (xi[m_n] - xi[m_n - 1])) - (1 / (x[m_n - 1] - xi[m_n - 1]));
  d[m_n] = (1 / (xi[m_n] - x[m_n - 1])) - (1 / (xi[m_n] - xi[m_n - 1]));
  r[m_n] = 0;

  rhs[m_n] = deriv(x[m_n - 1]) - y[m_n - 1] * ((1 / (x[m_n - 1] - xi[m_n - 1])) - (1 / (xi[m_n] - x[m_n - 1])));

  solve_matrix (l, d, r, rhs, answer, m_n + 1);

  for (int i = 0; i < m_n; i++)
    {
      c_1[i] = answer[i];

      c_2[i] = ((y[i] - answer[i]) / (x[i] - xi[i]))
               - ((x[i] - xi[i]) / (xi[i + 1] - xi[i])) * (((answer[i + 1] - y[i]) / (xi[i + 1] - x[i])) - ((y[i] - answer[i]) / (x[i] - xi[i])));

      c_3[i] =  (1 / (xi[i + 1] - xi[i]))
          * (((answer[i + 1] - y[i]) / (xi[i + 1] - x[i])) - ((y[i] - answer[i]) / (x[i] - xi[i])));
    }
}


double spline::calc_value (double x)
{
  int i = (int) ((m_n) * (x - xi[0]) / (xi[m_n] - xi[0]));
  return c_1[i] + c_2[i] * (x - xi[i]) + c_3[i] * (x - xi[i]) * (x - xi[i]);;
}


std::function<double(double)> spline::get_func ()
{
  return [&](double x){
      return calc_value (x);
    };
}
