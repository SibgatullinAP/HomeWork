#include "array.h"

int main (int argc, char *argv[])
{
  if (argc != 4 && argc != 3)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use:"
              " %s Array_length File_name_sequence File_name_subsequence\n", argv[0]);
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
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memory for array\n");
      return -2;
    }

  if (argc == 4)
    {
      char *file_name_subseq = argv[3];
      int ret = read (file_name_subseq, arr, array_size);
      if (ret < 0)
        {
          switch (ret)
            {
            case CANNOT_OPEN_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_subseq);
              break;
            case CANNOT_READ_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_subseq);
              break;
            case INVALID_FILE:
              printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                      " (only part of the file is read)\n", file_name_subseq);
              break;
            default:
              printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
            }

          free (arr);

          return -3;
        }
    }
  else
    randomize (arr, array_size);

  char *file_name_seq = argv[2];
  double time = clock ();
  int ret = occurrences (arr, array_size, file_name_seq);
  time = (clock () - time) / CLOCKS_PER_SEC;
  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name_seq);
          break;
        case CANNOT_READ_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name_seq);
          break;
        case INVALID_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                  " (only part of the file is read)\n", file_name_seq);
          break;
        default:
          printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }

      free (arr);
      return -3;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mAnswer = %d\n", ret);
  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  free (arr);
  return 0;
}
