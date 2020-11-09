#include "string_.h"

void parse_9 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

 strcpy (str_pattern_copy, str_pattern);

  for (int i = 0; str_pattern[i]; i++)
    {
      if (str_pattern[i] == '[')
        {
          if (!str_pattern[i + 1] || !str_pattern[i + 2]
              || !str_pattern[i + 3] || !str_pattern[i + 4]
              || str_pattern[i + 2] != '-' || str_pattern[i + 4] != ']')
            {
              regexp.error = -1;
              return;
            }
          else
            i += 5;
        }
      if (str_pattern[i] == '\\')
        {
          i++;
          if ((str_pattern[i] != '[') && (str_pattern[i] != '\\')
              && (str_pattern[i] != ']'))
            {
              regexp.error = -1;
              return;
            }
        }
    }

  return;
}

bool cmp_9 (char *str, char *str_pattern, Parse_results &regexp)
{
  (void) regexp;

  int i;
  for (i = 0; str[i]; i++)
    {
      if (str[i] == '\n')
        {
          str[i] = 0;
          break;
        }
    }

  int j = 0;
  int k = 0;
  char *str_temp = nullptr;
  char from, to;
  for (i = 0; str[i]; i++)
    {
      str_temp = str + i;
      for (j = 0, k = 0; str_temp[k] && str_pattern[j]; k++, j++)
        {
          if (str_pattern[j] == '[')
            {
              from = str_pattern[j + 1];
              to = str_pattern[j + 3];

              if (str_temp[k] >= from && str_temp[k] <= to)
                return true;
              else
                break;
            }

          if (str_pattern[j] == '\\')
            j++;

          if (str_temp[k] != str_pattern[j])
            break;
        }
      if (!str_pattern[j])
        return true;
    }
  return false;
}

//void parse_3 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
//{
//  regexp.pattern_len = strlen (str_pattern);
//  if (regexp.pattern_len <= 0)
//    {
//      regexp.error = -1;
//      return;
//    }

//  int shift = 0;
//  for (int i = 0; str_pattern_copy[i]; i++)
//    {
//      if (str_pattern_copy[i] == '\\')
//        {
//          if (str_pattern_copy[i + 1] && (str_pattern_copy[i + 1] == '<'))
//            {
//              shift++;
//              i++;
//              str_pattern_copy[i - shift] = str_pattern_copy[i];

//              shift++;
//              i++;
//              str_pattern_copy[i - shift] = str_pattern_copy[i];
//            }
//          else
//            {
//              regexp.error = -1;
//              return;
//            }
//        }
//      else if (i && str_pattern_copy[i] == '<')
//        {
//          regexp.error = -1;
//          return;
//        }
//      else
//        {
//          str_pattern_copy[i - shift] = str_pattern_copy[i];
//        }
//    }

//  return;
//}

//bool cmp_3 (char *str, char *str_pattern, Parse_results &regexp)
//{
//  int i;
//  for (i = 0; str[i]; i++)
//    {
//      if (str[i] == '\n')
//        {
//          str[i] = 0;
//          break;
//        }
//    }

//  int j,
//      for (i = 0; str[i]; i++)
//  {
//    for (j = 0;   )
//      if (chek_s_right_here (buf + i, s));
//  }

//  return false;
//}

void parse_2 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  int shift = 0;
  int i;
  for (i = 0; str_pattern[i]; i++)
    {
      if (str_pattern[i] == '$')
        {
          if (str_pattern[i + 1])
            {
              regexp.error = -1;
              return;
            }
          str_pattern_copy[shift] = 0;
          regexp.is_regexp = true;
          regexp.pattern_len = shift;
          return;
        }
      if (str_pattern[i] == '\\')
        {
          i++;
          if (str_pattern[i] != '$' && str_pattern[i] != '\\')
            {
              regexp.error = -1;
              return;
            }
        }
      str_pattern_copy[shift] = str_pattern[i];
      shift++;
    }

  str_pattern_copy[shift] = str_pattern[i];
  regexp.pattern_len = shift;

  return;
}

bool cmp_2 (char *str, char *str_pattern, Parse_results &regexp)
{
  int i;
  for (i = 0; str[i]; i++)
    {
      if (str[i] == '\n')
        {
          str[i] = 0;
          break;
        }
    }
  if ((regexp.is_regexp && strstr (str + i - regexp.pattern_len, str_pattern) != NULL)
      || (!regexp.is_regexp && strstr (str, str_pattern) != NULL))
    return true;

  return false;
}

void parse_1 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  if (str_pattern[0] == '^')
    regexp.is_regexp = true;

  strcpy (str_pattern_copy, str_pattern);

  int shift = 0;
  for (int i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\')
        {
          if (str_pattern_copy[i + 1] && (str_pattern_copy[i + 1] == '^' || str_pattern_copy[i + 1] == '\\'))
            {
              shift++;
              i++;
              str_pattern_copy[i - shift] = str_pattern_copy[i];
            }
          else
            {
              regexp.error = -1;
              return;
            }
        }
      else if (i && str_pattern_copy[i] == '^')
        {
          regexp.error = -1;
          return;
        }
      else
        {
          str_pattern_copy[i - shift] = str_pattern_copy[i];
        }
    }

  str_pattern_copy[regexp.pattern_len - shift] = 0;
  return;
}

bool cmp_1 (char *str, char *str_pattern, Parse_results &regexp)
{
  for (int i = 0; str[i]; i++)
    {
      if (str[i] == '\n')
        {
          str[i] = 0;
          break;
        }
    }

  if ((regexp.is_regexp && strstr (str, str_pattern + 1) == str)
      || (!regexp.is_regexp && strstr (str, str_pattern) != NULL))
    return true;

  return false;
}

int regexp_solve (char *in_file_name, char *out_file_name, char *str_pattern,
                  void (*parse)(char *, char *, Parse_results &),
                  bool (*cmp)(char *, char *, Parse_results &))
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

  Parse_results obj;
  Parse_results &regexp = obj;
  parse (str_pattern, str_pattern_copy, regexp);

  if (regexp.error < 0)
    {
      fclose (in_file);
      fclose (out_file);
      return INCORRECT_REGEXP;
    }

  int answer = 0;
  while (fgets (buff, STRING_BUFF_LEN, in_file))
    {
      if (cmp (buff, str_pattern_copy, regexp))
        {
          answer++;
          if (!fprintf (out_file, "%s\n", buff))
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
