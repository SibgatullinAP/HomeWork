#include "equations.h"

int solve_bisect (double a, double b, double eps, double *answer,
                  double (*func)(double))
{
  double f_left = func (a);
  double f_right = func (b);

  if (f_left * f_right > 0)
    return -1;

  if (fabs (f_left) < EPS)
    {
      *answer = a;
      return 0;
    }

  if (fabs (f_right) < EPS)
    {
      *answer = b;
      return 0;
    }

  double center = 0;
  double f_center = 0;
  int i = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {
      center = (a + b) / 2.0;
      if (fabs (a - b) < EPS * (fabs (a) + fabs (b)))
        break;

      f_center = func (center);
      if (fabs (f_center) < EPS)
        break;

      if (f_left * f_center < 0)
        {
          b = center;
          f_right = f_center;
        }
      else if (f_right * f_center < 0)
        {
          a = center;
          f_left = f_center;
        }

      if (fabs (b - a) < eps)
        break;
    }

  if (i >= MAX_ITTER)
    return -1;

  *answer = center;
  return i;
}

int solve_newton (double x_0, double eps, double *answer,
                  double (*func)(double), double (*deriv)(double))
{
  int i = 0;
  double f_begin = func (x_0);
  double d_begin = deriv (x_0);

  if (fabs (f_begin) < eps)
    {
      *answer = x_0;
      return i;
    }

  double center = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {
      if(fabs (d_begin) < EPS)
        return -1;

      center = x_0 - f_begin/d_begin;

      if (fabs (x_0 - center) < EPS * (fabs (x_0) + fabs (center)))
        break;

      x_0 = center;
      d_begin = deriv (center);
      f_begin = func (center);

      if(fabs (f_begin) < eps)
        break;
    }

  if(i >= MAX_ITTER)
    return -1;

  *answer = center;
  return i;
}

int solve_chord (double a, double b, double eps, double *answer,
                 double (*func)(double))
{
  double f_left = func (a);
  double f_right = func (b);

  if (f_left * f_right > 0)
    return -1;

  if (fabs (f_left) < EPS)
    {
      *answer = a;
      return 0;
    }

  if (fabs (f_right) < EPS)
    {
      *answer = b;
      return 0;
    }

  double center = 0;
  double f_center = 0;
  int i = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {
      center = (f_right * a - f_left * b) / (f_right - f_left);

      if ((fabs (a - center) < EPS * (fabs (a) + fabs (center)))
          || (fabs (b - center) < EPS * (fabs (b) + fabs (center))))
        break;

      f_center = func (center);

      if (fabs (f_center) < EPS)
        break;

      if (f_left * f_center < 0)
        {
          b = center;
          f_right = f_center;
        }
      else if (f_right * f_center < 0)
        {
          a = center;
          f_left = f_center;
        }

      if (fabs (b - a) < eps)
        break;
    }

  if (i >= MAX_ITTER)
    return -1;

  *answer = center;
  return i;
}

int solve_secant (double a, double b, double eps, double *answer,
                  double (*func)(double))
{
  double f_left = func (a);
  double f_right = func (b);

  if (f_left * f_right > 0)
    return -1;

  if (fabs (f_left) < EPS)
    {
      *answer = a;
      return 0;
    }

  if (fabs (f_right) < EPS)
    {
      *answer = b;
      return 0;
    }

  double center = 0;
  double f_center = 0;
  int i = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {
      if (fabs (f_left - f_right) < EPS * (fabs (f_left) + fabs (f_right)))
        break;

      center = (f_right * a - f_left * b) / (f_right - f_left);

      if ((fabs (a - center) < EPS * (fabs (a) + fabs (center)))
          || (fabs (b - center) < EPS * (fabs (b) + fabs (center))))
        break;

      f_center = func (center);

      if (fabs (f_center) < EPS)
        break;

      if (!(fabs (f_center) > fabs(f_right)
            && fabs (f_center) > fabs (f_left)))
        {
          if (fabs (f_right) >= fabs (f_left))
            {
              b = center;
              f_right = f_center;
            }
          else
            {
              if (fabs (f_left) >= fabs (f_right))
                {
                  a = center;
                  f_left = f_center;
                }
              else
                return -1;
            }
        }

      else
        return -1;

      if (fabs (b - a) < eps)
        break;
    }

  if (i >= MAX_ITTER)
    return -1;

  *answer = center;
  return i;
}
