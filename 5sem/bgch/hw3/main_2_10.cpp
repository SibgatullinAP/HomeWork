#include "equations.h"
#include "func.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 5)
    {
      printf ("[ERROR] Please, use: %s A B EPS Formula_type\n", argv[0]);
      return -1;
    }

  double a = 0;
  if (sscanf (argv[1], "%lf", &a) != 1)
    {
      printf ("[ERROR] A should be a real number!\n");
      return -1;
    }
  double b = 0;
  if (sscanf (argv[2], "%lf", &b) != 1)
    {
      printf ("[ERROR] B should be a real number!\n");
      return -1;
    }
  double eps = 0;
  if (sscanf (argv[3], "%le", &eps) != 1)
    {
      printf ("[ERROR] EPS should be a real number (in scientific form)!\n");
      return -1;
    }
  int formula_type = 0;
  if (sscanf (argv[4], "%d", &formula_type) != 1 || (formula_type < 1 || formula_type > 5))
    {
      printf ("[ERROR] Formula_type should be integer in [1 ; 5] !\n");
      return -1;
    }

  double (*function) (double);
  switch (formula_type)
    {
    case 1:
      function = f_1;
      break;
    case 2:
      function = f_2;
      break;
    case 3:
      function = f_3;
      break;
    case 4:
      function = f_4;
      break;
    case 5:
      function = f_5;
      break;
    default:
      function = f_1;
    }

  double answer = 0;
  double time = clock ();
  int ret = max_squared_interpolations (a, b, eps, &answer, function);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      printf ("[ERROR] Can not find maximum :(\n");
      return -2;
    }

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] Itteration quantity: %d\n", ret);
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  return 0;
}