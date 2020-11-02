#include <iostream>
#include <cstring>
#include <time.h>

#define LEN 1234

int solve (const char *file_name_in, const char *file_name_out, char *string);
int chek_s_right_here (char * buf, const char *string);
int compile_string_3 (char *str, char *res, int *flag);

int compile_string_3 (char *str, char *res, int *flag)
{
  int i, j;
  char tmp = ' ';

  if (str[0] && (str[0] == '\\') && str[1] && (str[1] == '<'))
    *flag = 1;
  else
    *flag = 0;



  for (i = 0, j = 0; str[i]; i++)
    {
      if (str[i] == '\\')
        {
          i++;
          if (str[i] == '<')
            {
              if (tmp != ' ')
                return -4;
              else
                continue;
            }

          if (str[i] == '\\')
            {
              res[j] = str[i];
              j++;
              continue;
            }
          return -4;
        }
      res[j] = str[i];
      j++;
    }
  res[j] = str[i];
  return j;
}

int chek_s_right_here (char *buf, const char *s)
{
  int i, j;
  //printf ("buf = %s    s = %s\n", buf, s);
  for (i = 0, j = 0; buf[i] && s[j]; i++, j++)
    {
      if (s[j] == '\\')
        {
          j++;
          if (buf[i] != s[j])
              return 0;
        }

      if (buf[i] != s[j])
          return 0;

    }
  if (s[j] && s[j] != '$')
    {
      return 0;
    }
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
  //int len_buf;

  int len = strlen (s);
  if (len <= 0)
    return -4;

  int flag;
  char *comp_str = new char [len + 1];
  len = compile_string_3 (s, comp_str, &flag);
  if (len < 0)
    return len;

  //printf ("Befor: %s\nAfter: %s  len = %d\n\n", s, comp_str, len);

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
      //len_buf = i;

      if (flag)
        {
          if (strstr (buf, comp_str) != nullptr)
            {
              fprintf (fout, "%s\n", buf);
              count_res++;
              continue;
            }
          for (i = 1; buf[i]; i++)
            {
              if ((buf[i - 1] == ' ') || (buf[i - 1] == '\t'))
                {
                  if (strstr (buf + i, comp_str) != nullptr)
                    {
                      fprintf (fout, "%s\n", buf);
                      count_res++;
                      break;
                    }
                }
            }

          /*
          //printf ("I'm here  len_buf=%d  len=%d \n", len_buf, len);
          if (strstr (buf + len_buf - len, comp_str) != nullptr)
            {
              fprintf (fout, "%s\n", buf);
              count_res++;
            }
          continue;*/
        }
      else
        {
          for (i = 0; buf[i]; i++)
            {
              //printf ("%s \n", buf + i);
              if (strstr (buf + i, comp_str) != nullptr)
                {
                  fprintf (fout, "%s\n", buf);
                  count_res++;
                  break;
                }
            }
        }
    }
  delete [] comp_str;
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















