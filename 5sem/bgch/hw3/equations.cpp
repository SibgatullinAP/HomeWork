#include "equations.h"

int solve_bisect (double a, double b, double eps, double *answer,
                  double (*func)(double))
{
  double f_left = func (a);
  double f_right = func (b);

  unsigned short int size_of_double = sizeof (double);

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
      if (!memcmp ((void*)&a, (void*)&center, size_of_double)
          || !memcmp ((void*)&b, (void*)&center, size_of_double))
        break;

      //      if (fabs (a - b) < EPS * (fabs (a) + fabs (b)))
      //        break;

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

  if (i < MAX_ITTER)
    {
      *answer = center;
      return i;
    }

  return -1;
}

int solve_newton (double x_0, double eps, double *answer,
                  double (*func)(double), double (*deriv)(double))
{
  int i = 0;
  unsigned short int size_of_double = sizeof (double);

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

      if (!memcmp ((void*)&x_0, (void*)&center, size_of_double))
        break;

      x_0 = center;
      d_begin = deriv (center);
      f_begin = func (center);

      if(fabs (f_begin) < eps)
        break;
    }

  if (i < MAX_ITTER)
    {
      *answer = center;
      return i;
    }

  return -1;
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

  unsigned short int size_of_double = sizeof (double);
  int i = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {
      if (fabs (f_right - f_left) < EPS)
        return -1;

      center = (f_right * a - f_left * b) / (f_right - f_left);

      if (!memcmp ((void*)&a, (void*)&center, size_of_double)
          || !memcmp ((void*)&b, (void*)&center, size_of_double))
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

  if (i < MAX_ITTER)
    {
      *answer = center;
      return i;
    }

  return -1;
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

  unsigned short int size_of_double = sizeof (double);
  int i = 0;
  for (i = 1; i < MAX_ITTER; i++)
    {

      if (fabs (f_right - f_left) < EPS)
        return -1;

      center = (f_right * a - f_left * b) / (f_right - f_left);

      if (!memcmp ((void*)&a, (void*)&center, size_of_double)
          || !memcmp ((void*)&b, (void*)&center, size_of_double))
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

  if (i < MAX_ITTER)
    {
      *answer = center;
      return i;
    }

  return -1;
}

//int solve_inv_squared_interpolation (double a, double b, double eps, double *answer, double (*func)(double))
//{
//  double x_prev = a;
//  double x_curr = (a + b) / 2.0;
//  double x_next = b;

//  if (fabs (a - b) < EPS * (fabs (a) + fabs (b)))
//    {
//      *answer = x_curr;
//      return 0;
//    }

//  double f_prev = func (x_prev);
//  double f_curr = func (x_curr);
//  double f_next = func (x_next);

//  if (fabs (f_prev) < EPS)
//    {
//      *answer = x_prev;
//      return 0;
//    }
//  if (fabs (f_curr) < EPS)
//    {
//      *answer = x_curr;
//      return 0;
//    }
//  if (fabs (f_next) < EPS)
//    {
//      *answer = x_next;
//      return 0;
//    }

//  int i = 0;
//  double x = 0;
//  double f_x = 0;
//  for (i = 0; i < MAX_ITTER; i++)
//    {
//      if ((fabs (f_prev - f_curr) < EPS * (fabs (f_prev) + fabs (f_curr)))
//          || (fabs (f_curr - f_next) < EPS * (fabs (f_curr) + fabs (f_next)))
//          || (fabs (f_next - f_prev) < EPS * (fabs (f_next) + fabs (f_prev))))
//        return -1;

//      x = x_prev * (f_curr * f_next) / ((f_prev - f_curr) * (f_prev - f_next))
//          + x_curr * (f_prev * f_next) / ((f_curr - f_prev) * (f_curr - f_next))
//          + x_next * (f_prev * f_curr) / ((f_next - f_prev) * (f_next - f_curr));

//      f_x = func (x);

//      if (fabs (f_x) < eps)
//        break;

//      x_prev = x_curr;
//      x_curr = x_next;
//      x_next = x;

//      f_prev = f_curr;
//      f_curr = f_next;
//      f_next = f_x;

//    }

//  if (i < MAX_ITTER)
//    {
//      *answer = x;
//      return i;
//    }

//  return -1;
//}

int solve_inv_squared_interpolation (double a, double b, double eps, double *answer, double (*func)(double))
{
  unsigned short int size_of_double = sizeof (double);

  double x_prev = a;
  double x_curr = (a + b) / 2.0;
  double x_next = b;

  if (!memcmp ((void*)&x_prev, (void*)&x_curr, size_of_double)
      || !memcmp ((void*)&x_next, (void*)&x_curr, size_of_double))
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

  double x = 0;
  double f_x = 0;

  double f_[3] = {0};
  double interp_[3] = {0};

  int i = 0;
  for (i = 0; i < MAX_ITTER; i++)
    {
      f_[0] = f_prev;
      f_[1] = f_curr;
      f_[2] = f_next;

      interp_[0] = x_prev;
      interp_[1] = x_curr;
      interp_[2] = x_next;


      for (int k = 1; k < 3; k++)
        {
          for (int j = 2; j >= k; j--)
            interp_[j] = (interp_[j - 1] * f_[j] - interp_[j] * f_[j - k]) / (f_[j] - f_[j - k]);
        }

      x = interp_[2];
      f_x = func (x);

      if (fabs (f_x) < eps)
        break;

      if (!(fabs (f_x) > fabs (f_prev) && fabs (f_x) > fabs (f_curr) && fabs (f_x) > fabs (f_next)))
        {
          if (fabs (f_prev) > fabs (f_x) && fabs (f_prev) > fabs (f_curr) && fabs (f_prev) > fabs (f_next))
            {
              x_prev = x;
              f_prev = f_x;
            }
          else
            {
              if (fabs (f_curr) > fabs (f_x) && fabs (f_curr) > fabs (f_prev) && fabs (f_curr) > fabs (f_next))
                {
                  x_curr = x;
                  f_curr = f_x;
                }
              else
                {
                  if (fabs (f_next) > fabs (f_x) && fabs (f_next) > fabs (f_prev) && fabs (f_next) > fabs (f_curr))
                    {
                      x_next = x;
                      f_next = f_x;
                    }
                  else
                    return -1;
                }
            }
        }
      else
        return -1;
    }

  if (i < MAX_ITTER)
    {
      *answer = x;
      return i;
    }

  return -1;
}

int solve_m_th_interpolation (double a, double b, double eps, double *d, int m,
                              double *answer, double (*func)(double))
{
  double *arr_args = d + m + 1;
  double *arr_func = d;
  double *arr_interp = d + 2 * m + 2;

  int i = 0;
  for (i = 0; i < m + 1; i++)
    {
      arr_args[i] = a + i * (b - a) / m;
      arr_func[i] = func (arr_args[i]);
      arr_interp[i] = arr_args[i];

      if (fabs (arr_func[i]) < eps)
        {
          *answer = arr_args[i];
          return 0;
        }
    }

  int max_pos = 0;
  double max = 0;
  int j = 0, k = 0;
  double x_ = 0;
  double fx_ = 0;

  for (i = 1; i < MAX_ITTER; i++)
    {
      for (k = 1; k < m + 1; k++)
        for (j = m; j >= k; j--)
          arr_interp[j] = (arr_interp[j - 1] * arr_func[j] - arr_interp[j] * arr_func[j - k])
              / (arr_func[j] - arr_func[j - k]);

      x_ = arr_func[3 * m - 2];
      fx_ = func (x_);
      if (fabs (fx_) < eps)
        break;

      max = -1;
      for (k = 0; k < m + 1; k++)
        if (fabs (arr_func[k]) > max)
          {
            max_pos = k;
            max = fabs (arr_func[k]);
          }

      if (fabs(fx_) <= max)
        {
          arr_args[max_pos] = x_;
          arr_func[max_pos] = fx_;
          for (j = 0; j < m + 1; j++)
            arr_interp[j] = arr_args[j];
        }
      else
        return -1;
    }

  if (i < MAX_ITTER)
    {
      *answer = x_;
      return i;
    }
  return -1;
}

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

