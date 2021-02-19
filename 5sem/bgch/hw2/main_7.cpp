#include "string_.h"

int main (int argc, char *argv[])
{
  if (argc != 4)
    {
      printf ("[ERROR] Please, use: "
              "%s Input_file_name Output_file_name str_pattern\n", argv[0]);
      return -1;
    }

  char *in_file_name = argv[1];
  char *out_file_name = argv[2];
  char *str_pattern = argv[3];

  double time = clock ();
  int ret = regexp_solve (in_file_name, out_file_name, str_pattern, parse_7, cmp_7);
  time = (clock () - time) / CLOCKS_PER_SEC;

  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE_IN:
          printf ("[ERROR] Can't open %s to read.\n", in_file_name);
          break;
        case CANNOT_OPEN_FILE_OUT:
          printf ("[ERROR] Can't open %s to write.\n", out_file_name);
          break;
        case CANNOT_READ_FILE_IN:
          printf ("[ERROR] Can't read %s\n", in_file_name);
          break;
        case CANNOT_WRITE_FILE_OUT:
          printf ("[ERROR] Can't write to %s\n", out_file_name);
          break;
        case INVALID_FILE_IN:
          printf ("[ERROR] Invalid file %s"
                  " (only part of the file is read)\n", in_file_name);
          break;
        case EMPTY_FILE_IN:
          printf ("[ERROR] Empty file %s\n", out_file_name);
          break;
        case INCORRECT_REGEXP:
          printf ("[ERROR] Incorrect regular expression %s\n", str_pattern);
          break;
        default:
          printf ("[ERROR] Unknown error\n");
        }
      return -2;
    }

  printf ("[OUTPUT] Answer = %d\n", ret);

  return 0;
}
