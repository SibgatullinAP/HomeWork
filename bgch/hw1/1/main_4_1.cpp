#include "string_.h"

int main (int argc, char *argv[])
{
  if (argc != 3)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s String_1 String_2\n", argv[0]);
      return -1;
    }

  char *string_1 = argv[1];
  char *string_2 = argv[2];

  double time = clock ();
  int ret = strcspn_ (string_1, string_2);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\x1b[32m[OUTPUT] \x1b[0mAnswer = %d\n", ret);
  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  return 0;
}
