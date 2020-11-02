#include <iostream>
#include <cstring>
#include <time.h>

#define LEN 1234

int solve (const char *file_name_in, const char *file_name_out, char *string);
int chek_s_right_here (char * buf, const char *string);


int chek_s_right_here (char *buf, const char *s)
{
  int i, j;
  char n, m;
  //printf ("buf = %s    s = %s\n", buf, s);
  for (i = 0, j = 0; buf[i] && s[j]; i++, j++)
    {
      if (s[j] == '[')
        {
          n = s[j + 1];
          m = s[j + 3];
          if (buf[i] < n || buf[i] > m)
            return 0;
          else
            {
              j += 4;
              continue;
            }
        }
      if (s[j] == '\\')
        {
          j++;
        }
      if (buf[i] != s[j])
          break;
    }

  if (!s[j])
    return 1;

  return 0;
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
      if (s[i] == '[')
        {
          if (!s[i + 1] || !s[i + 2] || !s[i + 3] || !s[i + 4]
              || s[i + 2] != '-' || s[i + 4] != ']')
            {
              return -4;
            }
          else
            {
              i += 5;
            }
        }
      if (s[i] == '\\')
        {
          i++;
          if ((s[i] != '[') && (s[i] != '\\') && (s[i] != ']'))
            {
              return -4;
            }
        }
    }

/*
  int len = strlen (s);
  char *comp_str = new char [len];
  len = compile_string_7 (s, comp_str);
  if (len < 0)
    return len;
  */




  //printf ("Befor: %s\nAfter compile: %s  len = %d\n\n", s, comp_str, len);

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
          //printf ("%s \n", buf + i);
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















