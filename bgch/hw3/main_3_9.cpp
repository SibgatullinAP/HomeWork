#include "integrals.h"
#include "func.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 6 && argc != 5)
    {
      printf ("[ERROR] Please, use: %s A B EPS (Formula_type_X) Formula_type_Y\nBy default x(t) = t is used\n", argv[0]);
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
  double eps  = 0;
  if (sscanf (argv[3], "%lf", &eps) != 1)
    {
      printf ("[ERROR] EPS should be a positive real number!\n");
      return -1;
    }

  int formula_type_x = 1;
  int formula_type_y = 1;
  if (argc == 5)
    {
      if (sscanf (argv[4], "%d", &formula_type_y) != 1 || (formula_type_y < 1 || formula_type_y > 5))
        {
          printf ("[ERROR] Formula_type_y should be integer in [1 ; 5] !\n");
          return -1;
        }
    }

  if (argc == 6)
    {
      if (sscanf (argv[4], "%d", &formula_type_x) != 1 || (formula_type_x < 1 || formula_type_x > 5)
          || sscanf (argv[5], "%d", &formula_type_y) != 1 || (formula_type_y < 1 || formula_type_y > 5))
        {
          printf ("[ERROR] Formula_type_x and Formula_type_y should be integer in [1 ; 5] !\n");
          return -1;
        }
    }

  double (*function_x) (double);
  switch (formula_type_x)
    {
    case 1:
      function_x = f_1;
      break;
    case 2:
      function_x = f_2;
      break;
    case 3:
      function_x = f_3;
      break;
    case 4:
      function_x = f_4;
      break;
    case 5:
      function_x = f_5;
      break;
    default:
      function_x = f_1;
    }

  double (*function_y) (double);
  switch (formula_type_y)
    {
    case 1:
      function_y = f_1;
      break;
    case 2:
      function_y = f_2;
      break;
    case 3:
      function_y = f_3;
      break;
    case 4:
      function_y = f_4;
      break;
    case 5:
      function_y = f_5;
      break;
    default:
      function_y = f_1;
    }

  double answer = 0;
  double time = clock ();
  int ret = length (a, b, eps, &answer, function_x, function_y);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      printf ("[ERROR] Can't calcualte lenght of line :( \n");
      return -2;
    }

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] Iterations: %d\n", ret);
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  return 0;
}
