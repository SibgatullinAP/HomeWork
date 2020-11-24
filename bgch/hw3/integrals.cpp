#include "integrals.h"

double integral_trapeze (double a, double b, int n, double (*func)(double))
{
  double delta = (b - a) / n;
  double sum = 0;

  for (int i = 1; i < n; i++)
    sum += func (a + i * delta);

  return delta * (func (a) * 0.5 + sum + func (b) * 0.5);
}

double integral_simpson (double a, double b, int n, double (*func)(double))
{
  double delta = 0.5 * (b - a) / n;
  double sum_even = 0;
  double sum_odd = func (a + delta);

  for (int i = 1; i < n; i++)
    {
      sum_odd += func (a + ((i << 1) + 1) * delta);
      sum_even += func (a + (i << 1) * delta);
    }

  return (delta / 3.0) * (func (a) + 2.0 * sum_even + 4.0 * sum_odd + func (b));
}


int integral_trapeze_auto_steps (double a, double b, double eps, double *answer, double (*func)(double))
{
  int steps = 1;
  double delta = fabs (b - a);
  double sum = delta * 0.5 * (func (a) + func (b));
  double sum_itter = 0;

  int i = 0;
  for(i = 0; i < MAX_ITTER_INTEGRAL; i++)
    {
      double sum_temp = 0;

      for(int j = 0; j < steps; j++)
        sum_temp += func (a + ((j << 1) + 1) * (delta * 0.5));

      sum_itter = 0.5 * sum +  0.5 * delta * sum_temp;

      if (fabs (sum - sum_itter) < eps)
        break;

      steps <<= 1;
      delta *= 0.5;
      sum = sum_itter;
    }

  if (i < MAX_ITTER_INTEGRAL)
    {
      *answer = sum_itter;
      return 2 * steps;
    }

  return -1;
}


int integral_simpson_auto_steps (double a, double b, double eps, double *answer, double (*func)(double))
{
  int steps = 1;
  double delta = fabs (b - a) * 0.5;

  double f_left = func (a);
  double f_right = func (b);

  double sum_left = 0;
  double sum_right = delta * func (a + delta);
  double sum = (delta / 3.0) * (func (a) + 4.0 * sum_right + func (b));
  double sum_itter = 0;


  int i = 0;
  for(i = 0; i < MAX_ITTER_INTEGRAL; i++)
    {
      double sum_temp = 0;
      for(int j = 0; j < steps << 1; j++)
        sum_temp += func (a + ((j << 1) + 1) * (delta * 0.5));

      sum_temp *= (0.5 * delta);

      sum_itter = delta * f_left / 6.0 + (sum_left + sum_right) / 3.0
          + (4.0 * sum_temp) / 3.0 + (f_right * delta) / 6.0;

      if (fabs (sum - sum_itter) < eps)
        break;

      steps <<= 1;
      delta *= 0.5;

      sum = sum_itter;
      sum_left = 0.5 * (sum_left + sum_right);
      sum_right = sum_temp;
    }

  if (i < MAX_ITTER_INTEGRAL)
    {
      *answer = sum_itter;
      return steps << 1;
    }

  return -1;
}

double improper_integral (double a, double eps, double *answer, double (*func)(double),
                          int (*integral) (double, double, double, double *, double (*)(double)))
{
  double delta = 1;
  double left = a;
  double right = a + delta;

  double sum = 0;
  int i = 0;
  for(i = 0; i < MAX_ITTER_CONV; i++)
    {
      double sum_partial = 0;
      int ret = integral (left, right, eps, &sum_partial, func);
      if (ret < 0)
        return ret;

      if (fabs (sum_partial) < eps)
        break;
      sum += sum_partial;

      delta *= 2.0;
      left = right;
      right += delta;
    }

  if (i < MAX_ITTER_CONV)
    {
      printf ("%d\n", i);
      *answer = sum;
      return right;
    }

  return -1;
}

int length (double a, double b, double eps, double *answer, double (*func_x)(double), double (*func_y)(double))
{
  double delta = fabs (b - a);

  double func_x_left = func_x (a);
  double func_x_right = func_x (b);
  double func_y_left = func_y (a);
  double func_y_right = func_y (b);

  double x_left = 0;
  double x_right = 0;
  double y_left = 0;
  double y_right = 0;

  double len_temp = 0;
  double len = sqrt ((func_x_left - func_x_right) * (func_x_left - func_x_right)
                     + (func_y_left - func_y_right) * (func_y_left - func_y_right));

  int steps = 1;
  int i = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      x_left = func_x_left;
      y_left = func_y_left;
      for (int j = 0; j < (steps << 1); j++)
        {
          y_right = func_y (a + i * 0.5 * delta);
          x_right = func_x (a + i * 0.5 * delta);

          len_temp += sqrt ((x_left - x_right) * (x_left - x_right) + (y_left - y_right) * (y_left - y_right));

          y_left = y_right;
          x_left = x_right;
        }

      if (fabs (len - len_temp) < eps)
        break;

      len = len_temp;
      delta *= 0.5;
      steps <<= 1;
    }

  if (i < MAX_ITTER)
    {
      *answer = len_temp;
      return steps << 1;
    }

  return -1;
}
