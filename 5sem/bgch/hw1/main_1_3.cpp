#include "sequences.h"

int main (int argc, char *argv[])
{
  feenableexcept (FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);

  if (argc != 2)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: %s File_name\n", argv[0]);
      return -1;
    }

  char *file_name = argv[1];
  double answer = 0;

  double time = clock ();
  int ret = rms_deviation (file_name, &answer);
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

  printf ("\x1b[32m[OUTPUT] \x1b[0mS = %0.5lf\n", answer);
  printf ("\x1b[32m[OUTPUT] \x1b[0mS is root-mean-square"
          " deviation of %d elements from %s\n", ret, file_name);
  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  return 0;
}
