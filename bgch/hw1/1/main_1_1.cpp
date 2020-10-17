#include "sequences.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  if (argc != 2)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s File_name\n", argv[0]);
      return -1;
    }

  char *file_name = argv[1];

  int k = 0;
  printf ("\x1b[34m[INPUT] \x1b[0mPlease, enter K = ");
  if (scanf ("%d", &k) != 1)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mIncorrect input values\n");
      return -1;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mSequence: ");
  double time = clock ();
  int ret = rebuild_sequnce (file_name, k);
  time = (clock () - time) / CLOCKS_PER_SEC;

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
        case EMPTY_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mEmpty file %s\n", file_name);
          break;
        default:
          printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }
      return -3;
    }

  printf ("\n");
  printf ("\x1b[32m[OUTPUT] \x1b[0mAnswer = %d\n", ret);
  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  return 0;
}
