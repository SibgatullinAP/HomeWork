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

int solve_inv_squared_interpolation (double a, double b, double eps, double *answer,
                                     double (*func)(double))
{
  double x_prev = a;
  double x_curr = (a + b) / 2.0;
  double x_next = b;

  if (fabs (a - b) < EPS * (fabs (a) + fabs (b)))
    {
      *answer = x_curr;
      return 0;
    }

  double f_prev = func (x_prev);
  double f_curr = func (x_curr);
  double f_next = func (x_next);

  if (fabs (f_prev) < EPS)
    {
      *answer = x_prev;
      return 0;
    }
  if (fabs (f_curr) < EPS)
    {
      *answer = x_curr;
      return 0;
    }
  if (fabs (f_next) < EPS)
    {
      *answer = x_next;
      return 0;
    }

  int i = 0;
  double x = 0;
  double f_x = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      if ((fabs (f_prev - f_curr) < EPS * (fabs (f_prev) + fabs (f_curr)))
          || (fabs (f_curr - f_next) < EPS * (fabs (f_curr) + fabs (f_next)))
          || (fabs (f_next - f_prev) < EPS * (fabs (f_next) + fabs (f_prev))))
        return -1;

      x = x_prev * (f_curr * f_next) / ((f_prev - f_curr) * (f_prev - f_next))
          + x_curr * (f_prev * f_next) / ((f_curr - f_prev) * (f_curr - f_next))
          + x_next * (f_prev * f_curr) / ((f_next - f_prev) * (f_next - f_curr));

      f_x = func (x);

      if (fabs (f_x) < eps)
        break;

      x_prev = x_curr;
      x_curr = x_next;
      x_next = x;

      f_prev = f_curr;
      f_curr = f_next;
      f_next = f_x;

    }

  *answer = x;

  if (i >= MAX_ITTER)
    return -1;

  return i;
}

//int solve_m_th_interpolation (double a, double b, double eps, double *d, int m,
//                              double *answer, double (*func)(double))
//{
//  int it = 0, j, itmax;
//  double d_, fd_, ymax;

//  int i = 0;
//  for(i = 0; i < m + 1; i++)
//    {
//      d[i + m + 1] = a + i * (b - a) / m;
//      d[i + (m << 2) + 2] = d[i + m + 1];
//      d[i] = func (d[i + m + 1]);

//      if(fabs (d[i]) < EPS)
//        {
//          *answer = d[i + m  +1];
//          return 0;
//        }
//    }

//  double x = 0;
//  double f_x = 0;
//  for(it = 1; it < MAX_ITTER; it++)
//    {
//      for(i = 1; i < m + 1;i++)
//        {
//          for(int j = m; j >= i; j--)
//            d[j + (m << 2) + 2] = (d[j + (m << 2) + 2] * (0 - d[j - i]) - d[j - 1 + (m << 2) + 2] * (0 - d[j]))
//                / (d[j] - d[j - i]);
//        }

//      d_ = d[3 * m - 2];
//      fd_ = func (d_);

//      if(fabs (fd_) < eps)
//        break;

//      ymax = -1;
//      for(i = 0; i < m + 1; i++)
//        if(fabs (d[i]) > ymax)
//          {
//            itmax = i;
//            ymax = fabs (d[i]);
//          }

//      if (fabs (fd_) > ymax)
//        return -1;
//      else
//        {
//          d[itmax + m + 1] = d_;
//          d[itmax] = fd_;
//          for (int j = 0; j < m + 1; j++)
//            d[j + (m << 2) + 2] = d[j + m + 1];
//        }
//    }

//  if(it < MAX_ITTER)
//    {
//      *answer = d_;
//      return it;
//    }

//  return -1;
//}

int solve_contraction_mapping (double x_0, double eps, double *answer, double (*func)(double))
{
  int i = 0;
  double x_approx;

  for (i = 0; i < MAX_ITTER; i++)
    {
      x_approx = func (x_0);
      if (fabs (x_approx - x_0) < eps)
        break;

      x_0 = x_approx;
    }

  if (i < MAX_ITTER)
    {
      *answer = x_approx;
      return i;
    }

  return -1;
}

int max_auto_steps (double a, double b, double eps, double *answer, double (*func)(double))
{
  double step = 10.0;
  double delta = (b - a) / step;
  double f_left = func (a);
  double f_right = func (b);
  double x_left = a;
  double x_right = 0;

  int i = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      if (fabs (delta) < eps)
        break;

      x_right = x_left + delta;
      f_right = func (x_right);

      if (!(x_right < b))
        {
          x_right = b;
          delta /= (-step);
        }
      if (!(x_right > a))
        {
          x_right = a;
          delta /= (-step);
        }

      if (f_left > f_right)
        delta /= (-step);

      x_left = x_right;
      f_left = f_right;
    }

  if (i < MAX_ITTER)
    {
      *answer = f_right;
      return i;
    }

  return -1;
}

int max_golden_secants (double a, double b, double eps, double *answer, double (*func)(double))
{
  double phi = (sqrt (5.0) + 1.0) / 2.0;
  double f_left = func (a);
  double f_right = func (b);

  int i = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      if (fabs (b - a) < eps)
        break;

      if (f_left < f_right)
        {
          a = a + (b - a) / phi;
          f_left = func (a);
        }
      else
        {
          b = b - (b - a) / phi;
          f_right = func (b);
        }
    }

  if (i < MAX_ITTER)
    {
      *answer = f_right;
      return i;
    }

  return -1;
}

int max_squared_interpolations (double a, double b, double eps, double *answer, double (*func)(double))
{
  double x_prev = a;
  double x_curr = (a + b) / 2.0;
  double x_next = b;

  if (fabs (a - b) < EPS * (fabs (a) + fabs (b)))
    {
      *answer = x_curr;
      return 0;
    }

  double f_prev = func (x_prev);
  double f_curr = func (x_curr);
  double f_next = func (x_next);

  double left = 0;
  double right = 0;

  double x = 0;
  double f_x = 0;

  double *max_pointer;
  double *max_pointer_func;
  double *min_pointer;
  double *min_pointer_func;

  int i = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      left = (((f_prev - f_next) / (x_prev - x_next)) - ((f_next - f_curr) / (x_next - x_curr)))
          / (x_prev - x_curr);

      right = ((f_prev - f_next) / (x_prev - x_next))
          - (x_prev + x_next) * ((((f_prev - f_next) / (x_prev - x_next))
                                  - ((f_next - f_curr) / (x_next - x_curr))))
                                / (x_prev - x_curr);

      if (left > 0)
        return -1;

      x = (-0.5) * right / left;
      f_x = func (x);

      if (f_prev > f_curr)
        {
          if (f_prev > f_next)
            {
              max_pointer_func = &f_prev;
              max_pointer = &x_prev;
            }
          else
            {
              max_pointer_func = &f_next;
              max_pointer = &x_next;
            }
        }
      else
        {
          if (f_curr > f_next)
            {
              max_pointer_func = &f_curr;
              max_pointer = &x_curr;
            }
          else
            {
              max_pointer_func = &f_next;
              max_pointer = &x_next;
            }
        }

      if (f_prev < f_curr)
        {
          if (f_prev < f_next)
            {
              min_pointer_func = &f_prev;
              min_pointer = &x_prev;
            }
          else
            {
              min_pointer_func = &f_next;
              min_pointer = &x_next;
            }
        }
      else
        {
          if (f_curr < f_next)
            {
              min_pointer_func = &f_curr;
              min_pointer = &x_curr;
            }
          else
            {
              min_pointer_func = &f_next;
              min_pointer = &x_next;
            }
        }

      *min_pointer = x;
      *min_pointer_func = f_x;

      if (fabs (f_x - (*max_pointer_func)) < eps || fabs (x - (*max_pointer)) < eps)
        break;
    }

  if (i < MAX_ITTER)
    {
      *answer = f_x;
      return i;
    }

  return -1;
}

