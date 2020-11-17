#include "string_.h"

int main (int argc, char *argv[])
{
  if (argc != 5)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s File_len K(parameter) String File_name\n", argv[0]);
      return -1;
    }
  int array_size = atoi (argv[1]);
  int k = atoi (argv[2]);

  if (array_size == 0 || k == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0m K and File_len "
              "should be positive integer\n");
      return -1;
    }

  char **arr = (char**) malloc (array_size * sizeof (char*));
  if (arr == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory\n");
      return -1;
    }
  for (int i = 0; i < array_size; i++)
      arr[i] = NULL;

  char *file_name = argv[4];
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
        case NOT_ENOUGH_MEMMORY:
          printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory\n");
          break;
        default:
          printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }
      free_ (arr, array_size);
      return -3;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mArray:\n");
  print (arr, array_size);

  char *string = argv[3];
  double time = clock ();
  int new_array_size = array_rebuilding_1 (arr, array_size, k, string);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\x1b[32m[OUTPUT] \x1b[0mArray after rebuilding:\n");
  print (arr, new_array_size);
  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  free_ (arr, array_size);

  return 0;
}
