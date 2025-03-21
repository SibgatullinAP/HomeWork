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
  double time = clock ();
  int result = type_of_sequence (file_name);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (result < 0)
    {
      switch (result)
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

  switch (result)
    {
    case SEQ_TYPE_UNKNOWN:
      printf ("\x1b[32m[OUTPUT] \x1b[0m%d - unkwon type\n", result);
      break;
    case SEQ_TYPE_ARITHMETICAL_PROGRESSION:
      printf ("\x1b[32m[OUTPUT] \x1b[0m0"
              "%d - arithmetical progression\n", result);
      break;
    case SEQ_TYPE_GEOMETRICAL_PROGRESSION:
      printf ("\x1b[32m[OUTPUT] \x1b[0m0"
              "%d - geometrical progression\n", result);
      break;
    case SEQ_TYPE_CONST:
      printf ("\x1b[32m[OUTPUT] \x1b[0m0"
              "%d - constant sequence\n", result);
      break;
    case SEQ_TYPE_NOT_ENOUGH_DATA:
      printf ("\x1b[32m[OUTPUT] \x1b[0m0"
              "%d - not enough data to establish\n", result);
      break;
    default:
      printf ("\x1b[31m[ERROR] \x1b[0mSomething is going wrong\n");
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  return 0;
}
