#include "array.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  if (argc != 3 && argc != 2)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use:"
              " %s Array_size (File_name)\n", argv[0]);
      return -1;
    }
  int array_size = atoi (argv[1]);
  if (array_size == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mArray_size should be positive integer\n");
      return -1;
    }

  double *arr = (double*) malloc (array_size * sizeof (double));
  if (arr == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory\n");
      return -2;
    }

  if (argc == 3)
    {
      char *file_name = argv[2];
      int ret = read (file_name, arr, array_size);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
              break;
            case CANNOT_READ_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
              break;
            case INVALID_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                      " (only part of the file is read)\n", file_name);
              break;
            default:
              printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
            }

          free (arr);

          return -3;
        }
    }
  else
    {
      randomize (arr, array_size);
    }

  double x = 0;
  printf ("\x1b[34m[INPUT] \x1b[0mPlease, enter X = ");
  if (scanf ("%lf", &x) != 1)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mIncorrect input values\n");
      free (arr);
      return -1;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mArray:\n");
  print (arr, array_size);

  double time = clock ();
  int new_array_size = shift (arr, array_size, x);
  time = (clock () - time) / CLOCKS_PER_SEC;


  printf ("\x1b[32m[OUTPUT] \x1b[0mArray after shifting:\n");
  print (arr, new_array_size);

  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  free (arr);

  return 0;
}
