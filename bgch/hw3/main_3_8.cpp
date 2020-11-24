#include "integrals.h"
#include "func.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 4)
    {
      printf ("[ERROR] Please, use: %s A EPS Formula_type\n", argv[0]);
      return -1;
    }

  double a = 0;
  if (sscanf (argv[1], "%lf", &a) != 1)
    {
      printf ("[ERROR] A should be a real number!\n");
      return -1;
    }
  double eps  = 0;
  if (sscanf (argv[2], "%lf", &eps) != 1)
    {
      printf ("[ERROR] EPS should be a positive real number!\n");
      return -1;
    }
  int formula_type = 0;
  if (sscanf (argv[3], "%d", &formula_type) != 1 || (formula_type < 1 || formula_type > 5))
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

  double answer = 0;
  double time = clock ();
  double ret = improper_integral (a, eps, &answer, function, integral_simpson_auto_steps);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      printf ("[ERROR] Can't calcualte integral :( \n");
      return -2;
    }

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] Error rate: %10.3e\n", fabs (answer - (antiderivative(1e40) - antiderivative(a))));
  printf ("[OUTPUT] B: %lf\n", ret);
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  return 0;
}
