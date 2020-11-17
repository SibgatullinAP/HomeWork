#include "interpolations.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

  if (argc != 5)
    {
      printf ("[ERROR] Please, use: %s array_length x_0 file_name_X file_name_Y\n", argv[0]);
      return -1;
    }

  int array_length = atoi (argv[1]);
  if (array_length <= 0)
    {
      printf ("[ERROR] array_length should be a positive integer!\n");
      return -1;
    }

  double x_0 = 0;
  if (sscanf (argv[2], "%lf", &x_0) != 1)
    {
      printf ("[ERROR] x_0 should be a real number!\n");
      return -1;
    }

  double *x = (double *) malloc (array_length * sizeof (double));
  if (x == nullptr)
    {
      printf ("[ERROR] Not enough memmory for X!\n");
      return -2;
    }

  double *y = (double *) malloc (array_length * sizeof (double));
  if (y == nullptr)
    {
      printf ("[ERROR] Not enough memmory for Y!\n");
      free (x);
      return -2;
    }

  char *file_name_x = argv[3];
  int ret = read (file_name_x, array_length, x);
  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE:
          printf ("[ERROR] Can not open %s!\n", file_name_x);
          break;
         case CANNOT_READ_FILE:
          printf ("[ERROR] Can not read %s!\n", file_name_x);
          break;
        default:
          printf ("[ERROR] Unknown error %d in file %s", ret, file_name_x);
        }
      free (x);
      free (y);
      return -3;
    }

  char *file_name_y = argv[4];
  ret = read (file_name_y, array_length, y);
  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE:
          printf ("[ERROR] Can not open %s!\n", file_name_y);
          break;
         case CANNOT_READ_FILE:
          printf ("[ERROR] Can not read %s!\n", file_name_y);
          break;
        default:
          printf ("[ERROR] Unknown error %d in file %s", ret, file_name_y);
        }
      free (x);
      free (y);
      return -3;
    }

  printf ("[OUTPUT] X\n");
  print (array_length, x);

  printf ("[OUTPUT] Y\n");
  print (array_length, y);

  double time = clock ();
  double answer = lagr_interpolation_div_diff (array_length, x_0, x, y);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("[OUTPUT] Answer: %0.15lf\n", answer);
  printf ("[OUTPUT] Elapsed: %lf\n", time);

  free (x);
  free (y);

  return 0;
}
