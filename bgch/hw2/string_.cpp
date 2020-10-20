#include "string_.h"

int parse_1 (char *str_pattern, char *str_pattern_copy)
{
  int i = 0;
  int shift = 0;

  strcpy (str_pattern_copy, str_pattern);

  if (str_pattern_copy[0] == '^')
    {
      while(str_pattern_copy[i])
        {
          i++;
          str_pattern_copy[i - 1] = str_pattern_copy[i];
        }
      str_pattern_copy[i] = 0;

      return 1;
    }

  for (i = 0; str_pattern_copy[i]; )
    {
      if(str_pattern_copy[i] == '\\')
        {
          if(str_pattern_copy[i + 1] &&
             (str_pattern_copy[i + 1] == '\\'
              || str_pattern_copy[i + 1]== '^'))
            {
              shift++;
              i++;
              str_pattern_copy[i - shift] = str_pattern_copy[i];
              i++;
            }
          else
            return -1;
        }
      else
        {
          str_pattern_copy[i - shift] = str_pattern_copy[i];
          i++;
        }
    }

  str_pattern_copy[strlen (str_pattern_copy) - shift] = 0;
  strcpy (str_pattern_copy, str_pattern);

  return 0;
}

bool cmp_1 (char *str, char *str_pattern, int is_begin)
{
  if((is_begin > 0 && strstr(str, str_pattern) == str)
     || (is_begin == 0 && (bool) strstr(str, str_pattern)))
    return true;

  return false;
}

int parse_2 (char *str_pattern, char *str_pattern_copy)
{
  strcpy (str_pattern_copy, str_pattern);

  int len = strlen (str_pattern_copy);
  if((unsigned int)str_pattern_copy[len - 1] == '$')
    {
      str_pattern_copy[len - 1] = 0;
      return 1;
    }

  int i = 0;
  int shift = 0;

  for (i = 0; str_pattern_copy[i]; )
    {
      if(str_pattern_copy[i] == '\\')
        {
          if(str_pattern_copy[i + 1] &&
             (str_pattern_copy[i + 1] == '\\'
              || str_pattern_copy[i + 1]== '$'))
            {
              shift++;
              i++;
              str_pattern_copy[i - shift] = str_pattern_copy[i];
              i++;
            }
          else
            return -1;
        }
      else
        {
          str_pattern_copy[i - shift] = str_pattern_copy[i];
          i++;
        }
    }

  str_pattern_copy[len - shift] = 0;
  return len;
}

bool cmp_2 (char *str, char *str_pattern, int is_begin)
{
  if((is_begin > 0 && strstr(str, str_pattern) == str + (strlen (str) - is_begin))
     || (is_begin == 0 && (bool) strstr(str, str_pattern)))
    return true;

  return false;
}

int regexp (char *in_file_name, char *out_file_name, char *str_pattern,
            int (*parse)(char *, char *),
            bool (*cmp)(char *, char *, int ))
{
  FILE *in_file = fopen (in_file_name, "r");
  if (in_file == NULL)
    return CANNOT_OPEN_FILE_IN;

  FILE *out_file = fopen (out_file_name, "w");
  if (out_file == NULL)
    {
      fclose (in_file);
      return CANNOT_OPEN_FILE_OUT;
    }

  char buff[STRING_BUFF_LEN];
  char str_pattern_copy[STRING_BUFF_LEN];

  int is_regexp = parse (str_pattern, str_pattern_copy);
  if (is_regexp < 0)
    {
      fclose (in_file);
      fclose (out_file);
      return INCORRECT_REGEXP;
    }

  int answer = 0;
  while (fgets (buff, STRING_BUFF_LEN, in_file))
    {
      if (cmp (buff, str_pattern_copy, is_regexp))
        {
          answer++;
          if (!fprintf (out_file, "%s", buff))
            {
              fclose (in_file);
              fclose (out_file);
              return CANNOT_WRITE_FILE_OUT;
            }
        }
    }

  if (!feof (in_file))
    {
      fclose (in_file);
      fclose (out_file);
      return CANNOT_READ_FILE_IN;
    }

  fclose (in_file);
  fclose (out_file);
  return answer;
}
