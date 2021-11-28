#include "integrals.h"
#include "func.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 5)
    {
      printf ("[ERROR] Please, use: %s A B N Formula_type\n", argv[0]);
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
  int n = 0;
  if (sscanf (argv[3], "%d", &n) != 1)
    {
      printf ("[ERROR] N should be a positive integer!\n");
      return -1;
    }
  int formula_type = 0;
  if (sscanf (argv[4], "%d", &formula_type) != 1 || (formula_type < 1 || formula_type > 5))
    {
      printf ("[ERROR] Formula_type should be integer in [1 ; 5] !\n");
      return -1;
    }

  double (*function) (double);
  double (*antiderivative) (double);
  switch (formula_type)
    {
    case 1:
      function = f_1;
      antiderivative = anti_d_1;
      break;
    case 2:
      function = f_2;
      antiderivative = anti_d_2;
      break;
    case 3:
      function = f_3;
      antiderivative = anti_d_3;
      break;
    case 4:
      function = f_4;
      antiderivative = anti_d_4;
      break;
    case 5:
      function = f_5;
      antiderivative = anti_d_5;
      break;
    default:
      function = f_1;
      antiderivative = anti_d_1;
    }

  double time = clock ();
  double answer = integral_squared (a, b, n, function, partial_simpson);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] Error rate: %10.3e\n", fabs (answer - (antiderivative(b) - antiderivative(a))));
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  return 0;
}
