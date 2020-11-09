#include <iostream>
#include <cstring>
#include <time.h>

#define LEN 1234

int solve (const char *file_name_in, const char *file_name_out, char *string);
int chek_s_right_here (char * buf, const char *string);


int chek_s_right_here (char *buf, const char *s)
{
  int i, j;
  for (i = 0, j = 0; buf[i] && s[j]; i++, j++)
    {
      if (s[j] == '\\')
        {
          j++;
          if (s[j] == '>')
            {
              if ((buf[i] != 0) && (buf[i] != ' ') && (buf[i] != '\t'))
                  return 0;
              else
                {
                  if (!buf[i])
                    i--;

                  continue;
                }
            }
        }

      if (buf[i] != s[j])
          return 0;
    }

  if (!buf[i])
    {
      if (s[j] && s[j + 1] && s[j] == '\\' && s[j + 1] == '>')
        return 1;
    }

  if (s[j])
      return 0;

  return 1;
}

int main(int argc, char **argv)
{
  if (argc != 4)
    {
      printf ("\n   \x1b[1;31mUseg:\x1b[0m %s file_in file_out string\n", argv[0]);
      return 1;
    }

  const char *file_name_in = argv[1];
  const char *file_name_out = argv[2];
  char *string = argv[3];

  int res = solve (file_name_in, file_name_out, string);

  if (res < 0)
    {
      printf ("\x1b[1;31mERROR   :  \x1b[0m");
      switch (res)
        {
        case -1:
          printf ("Cannot open %s\n\n", file_name_in);
          break;
        case -2:
          printf ("Cannot open %s\n\n", file_name_out);
          break;
        case -3:
          printf ("Cannot read from %s\n\n", file_name_in);
          break;
        case -4:
          printf ("Not right string s (= %s)\n\n", string);
          break;
        case -5:
          printf ("LEN was not enogh for s_new\n\n");
          break;
        default:
          printf ("Unknown error %d\n\n", res);
          break;
        }
      return 3;
    }

  printf ("\n   \x1b[1;33mResult: \x1b[0m %d\n", res);
  return 0;
}


int solve (const char *file_in, const char *file_out, char *s)
{
  FILE *fin = fopen (file_in, "r");
  if (!fin)
    {
      return -1;
    }
  FILE *fout;
  if (strcmp (file_out, "stdout") == 0)
    {
      fout = stdout;
    }
  else
    {
     fout = fopen (file_out, "w");
      if (!fout)
        {
          fclose (fin);
          return -2;
        }
    }

  char buf[LEN];
  int i, count_res = 0;

  for (i = 0; s[i]; i++)
    {
      if (s[i] == '\\')
        {
          i++;
          if (!s[i] || (s[i] != '\\' && s[i] != '>'))
            return -4;
        }
    }

  while (fgets (buf, LEN, fin))
    {
      for (i = 0; buf[i]; i++)
        {
          if (buf[i] == '\n')
            {
              buf[i] = 0;
              break;
            }
        }

      for (i = 0; buf[i]; i++)
        {
          if (chek_s_right_here (buf + i, s))
            {
              fprintf (fout, "%s\n", buf);
              count_res++;
              break;
            }
        }

    }
  if (strcmp (file_out, "stdout") != 0)
    {
      fclose (fout);
    }
  if (!feof (fin))
    {
      fclose (fin);
      return -3;
    }
  fclose (fin);
  return count_res;
}












