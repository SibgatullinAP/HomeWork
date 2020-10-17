#include "string_.h"

int main (int argc, char *argv[])
{
  if (argc != 4)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s Input_file_name Output_file_name str_pattern\n", argv[0]);
      return -1;
    }

  char *in_file_name = argv[1];
  char *out_file_name = argv[2];
  char *str_pattern = argv[3];

  double time = clock ();
  int ret = regexp_1 (in_file_name, out_file_name, str_pattern);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE_IN:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s to read.\n", in_file_name);
          break;
        case CANNOT_OPEN_FILE_OUT:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s to write.\n", out_file_name);
          break;
        case CANNOT_READ_FILE_IN:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", in_file_name);
          break;
        case CANNOT_WRITE_FILE_OUT:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't write to %s\n", out_file_name);
          break;
        case INVALID_FILE_IN:
          printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                  " (only part of the file is read)\n", in_file_name);
          break;
        case EMPTY_FILE_IN:
          printf ("\x1b[31m[ERROR] \x1b[0mEmpty file %s\n", out_file_name);
          break;
        case INCORRECT_REGEXP:
          printf ("\x1b[31m[ERROR] \x1b[0mIncorrect regular expression %s\n", str_pattern);
          break;
        default:
          printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }
      return -2;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mAnswer = %d\n", ret);

  return 0;
}