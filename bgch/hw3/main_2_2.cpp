#include "equations.h"
#include "func.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 4)
    {
      printf ("[ERROR] Please, use: %s X_0 EPS Formula_type\n", argv[0]);
      return -1;
    }

  double x_0 = 0;
  if (sscanf (argv[1], "%lf", &x_0) != 1)
    {
      printf ("[ERROR] X_0 should be a real number!\n");
      return -1;
    }
  double eps = 0;
  if (sscanf (argv[2], "%le", &eps) != 1)
    {
      printf ("[ERROR] EPS should be a real number (in scientific form)!\n");
      return -1;
    }
  int formula_type = 0;
  if (sscanf (argv[3], "%d", &formula_type) != 1 || (formula_type < 1 || formula_type > 5))
    {
      printf ("[ERROR] Formula_type should be integer in [1 ; 5] !\n");
      return -1;
    }

  double (*function) (double);
  double (*derivative) (double);

  switch (formula_type)
    {
    case 1:
      function = f_1;
      derivative = d_1;
      break;
    case 2:
      function = f_2;
      derivative = d_2;
      break;
    case 3:
      function = f_3;
      derivative = d_3;
      break;
    case 4:
      function = f_4;
      derivative = d_4;
      break;
    case 5:
      function = f_5;
      derivative = d_5;
      break;
    default:
      function = f_1;
      derivative = d_1;
    }

  double answer = 0;
  double time = clock ();
  int ret = solve_newton (x_0, eps, &answer, function, derivative);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      printf ("[ERROR] Can not find root :(\n");
      return -2;
    }

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] F(Answer): %10.3e\n", fabs (function(answer)));
  printf ("[OUTPUT] Itteration quantity: %d\n", ret);
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  return 0;
}
