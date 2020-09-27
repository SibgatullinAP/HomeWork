#include "sort.h"

int main (int argc, char *argv[])
{
  if (argc != 3)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: %s Array_size File_name\n", argv[0]);
      return -1;
    }
  int array_size = atoi (argv[1]);
  if (array_size == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mArray_size should be positive integer\n");
      return -1;
    }

  double *arr = (double*)malloc(array_size * sizeof(double));
  if (arr == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array_1\n");
      return -2;
    }

  char *name = argv[2];
  int ret = read (name, arr, array_size);
  if (ret < 0)
    {
      switch(ret)
        {
        case CANNOT_OPEN_FILE:
          printf("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", name);
          break;
        case CANNOT_READ_FILE:
          printf("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", name);
          break;
        case INVALID_FILE:
          printf("\x1b[31m[ERROR] \x1b[0mInvalid file (only part of the file is read)\n");
          break;
        default:
          printf("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }

      free (arr);

      return -3;
    }

  printf("\x1b[32m[OUTPUT] \x1b[0mArray:\n");
  print (arr, array_size);

  double time = clock ();
  heap_sort (arr, array_size);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf("\x1b[32m[OUTPUT] \x1b[0mArray after sorting:\n");
  print (arr, array_size);

  check(arr, array_size);
  printf("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  free (arr);

  return 0;
}
