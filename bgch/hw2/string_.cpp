#include "string_.h"

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

              if (str_temp[k] < from || str_temp[k] > to)
                break;
              else
                {
                  j += 4;
                  continue;
                }
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

void parse_8 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  if (str_pattern_copy[0] == '*')
    {
      regexp.error = -1;
      return;
    }

  int i;
  for (i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\')
        {
          i++;
          if (str_pattern_copy[i] != '*' && str_pattern_copy[i] != '\\')
            {
              regexp.error = -1;
              return;
            }
        }
    }

  int j;
  char temp;
  for (i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '*' && str_pattern_copy[i - 1] != '\\')
        {
          regexp.is_regexp = true;
          temp = str_pattern_copy[i - 1];
          for (j = i + 1; str_pattern_copy[j]
               && str_pattern_copy[j] == temp; j++)
            {
              str_pattern_copy[j - 1] = str_pattern_copy[j];
            }

          str_pattern_copy[j - 1] = '*';
        }
    }

  return;
}

bool cmp_8 (char *str, char *str_pattern, Parse_results &regexp)
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

  int j, k = 0;
  char temp;
  for (i = 0; str[i] && str_pattern[k + j]; i++, k++)
    {
      if (!str_pattern[k + j + 1])
        {
          if (str_pattern[k + j] != str[i])
            {
              k = -1;
              j = 0;
            }
          else
            return true;
        }
      else
        {
          if (str_pattern[k + j] == '\\')
            j++;

          if (str_pattern[k + j + 1] == '*')
            {
              if (str_pattern[k + j] == str[i])
                {
                  temp = str_pattern[k + j];
                  for (; str[i] && str[i] == temp; i++);
                }
              i--;
              j++;
            }
          else
            {
              if (str_pattern[k + j] != str[i])
                {
                  k = -1;
                  j = 0;
                }
            }
        }
    }

  if (str_pattern[k + j] == '\\') j++;
  if (str_pattern[k + j + 1] && str_pattern[k + j + 1] == '*'
      && !str_pattern[k + j + 2])
    return true;

  while (str_pattern[k + j] && str_pattern[k + j] == '*')
    k++;

  if ((regexp.is_regexp && strstr (str, str_pattern) != nullptr)
      || !str_pattern[k + j])
    return true;

  return false;
}

void parse_7 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  if (str_pattern_copy[0] == '+')
    {
      regexp.error = -1;
      return;
    }

  int i;
  for (i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\')
        {
          i++;
          if (str_pattern_copy[i] != '+' && str_pattern_copy[i] != '\\')
            {
              regexp.error = -1;
              return;
            }
        }
    }

  int j;
  char temp;
  for (i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '+' && str_pattern_copy[i - 1] != '\\')
        {
          regexp.is_regexp = true;
          temp = str_pattern_copy[i - 1];
          for (j = i + 1; str_pattern_copy[j]
               && str_pattern_copy[j] == temp; j++)
            {
              str_pattern_copy[j - 1] = str_pattern_copy[j];
            }

          str_pattern_copy[j - 1] = '+';
        }
    }

  return;
}

bool cmp_7 (char *str, char *str_pattern, Parse_results &regexp)
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

  int j = 0, k = 0;
  char temp;
  for (i = 0; str[i] && str_pattern[k + j]; i++, k++)
    {
      if (str_pattern[k + j] != '+')
        {
          if (str_pattern[k + j] == '\\')
            j++;

          if (str_pattern[k + j] != str[i])
            {
              k = -1;
              j = 0;
            }
        }
      else
        {
          temp = str_pattern[k + j - 1];
          while (str[i] && str[i] == temp)
            {
              i++;
            }

          i--;
        }
    }

  while (str_pattern[k + j] && str_pattern[k + j] == '+')
    {
      k++;
    }

  if ((regexp.is_regexp && strstr (str, str_pattern) != nullptr)
      || !str_pattern[k + j])
    return true;

  return false;
}

void parse_6 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  if (str_pattern_copy[0] == '?')
    {
      regexp.error = -1;
      return;
    }

  for (int i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\')
        {
          i++;
          if (str_pattern_copy[i] != '?' && str_pattern_copy[i] != '\\')
            {
              regexp.error = -1;
              return;
            }
        }
    }

  return;
}

bool cmp_6 (char *str, char *str_pattern, Parse_results &regexp)
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

  int j, k;
  for (i = 0; str[i]; i++)
    {
      char *str_temp = str + i;
      for (k = 0, j = 0; str_temp[k] && str_pattern[j]; j++, k++)
        {
          //          if (str_pattern[j] == '?')
          //            {
          //              j++;
          //            }
          //          if (str_temp[k] == '\\')
          //            {
          //              k++;
          //            }
          //          if (str_temp[k] != str_pattern[j])
          //            {
          //              if (str_pattern[j + 1] && str_pattern[j + 1] == '?')
          //                {
          //                  j++;
          //                  k--;
          //                }
          //              else
          //                break;
          //            }
          if (str_pattern[j] == '\\')
            {
              j++;
              if (str_temp[k] != str_pattern[j])
                {
                  if (str_pattern[j + 1] == '?')
                    {
                      j++;
                      k--;
                      continue;
                    }
                  break;
                }
            }
          if (str_pattern[j] == '?')
            {
              k--;
              continue;
            }
          if (str_temp[k] != str_pattern[j])
            {
              if (str_pattern[j + 1] == '?')
                {
                  j++;
                  k--;
                  continue;
                }
              break;
            }
        }

      if (!str_pattern[j])
        return true;
    }

  return false;
}

void parse_5 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  for (int i = 0; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\')
        {
          i++;
          if (str_pattern_copy[i] != '.' && str_pattern_copy[i] != '\\')
            {
              regexp.error = -1;
              return;
            }
        }
    }

  return;
}

bool cmp_5 (char *str, char *str_pattern, Parse_results &regexp)
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

  int j, k;
  for (i = 0; str[i]; i++)
    {
      char *str_temp = str + i;
      for (k = 0, j = 0; str_temp[k] && str_pattern[j]; j++, k++)
        {
          if (str_pattern[j] != '.')
            {
              if (str_pattern[j] == '\\')
                j++;

              if (str_temp[k] != str_pattern[j])
                break;
            }
        }
      if (!str_pattern[j])
        return true;
    }

  return false;
}

void parse_4 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  int shift = 0;
  int i = 0;
  if (str_pattern_copy[1] && str_pattern_copy[0] == '\\' && str_pattern_copy[1] == '<')
    {
      regexp.is_regexp = true;
      i = 2;
      shift = 2;
    }

  for (; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\' && str_pattern_copy[i + 1])
        {
          if (str_pattern_copy[i + 1] == '\\')
            {
              shift++;
              i++;
              str_pattern_copy[i - shift] = str_pattern_copy[i];
              continue;
            }

          if (str_pattern_copy[i + 1] == '>')
            {
              if (!str_pattern_copy[i + 2])
                {
                  regexp.is_regexp = true;
                  shift += 2;
                  break;
                }
              else
                {
                  if (str_pattern_copy[i + 2] == ' ' || str_pattern_copy[i + 2] == '\t')
                    {
                      shift += 2;
                      i++;
                      continue;
                    }
                  else
                    {
                      regexp.error = -1;
                      return;
                    }
                }
            }

          regexp.error = -1;
          return;
        }
      else
        {
          str_pattern_copy[i - shift] = str_pattern_copy[i];
        }
    }

  str_pattern_copy[regexp.pattern_len - shift] = 0;

  regexp.pattern_len = strlen (str_pattern_copy);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  return;
}

bool cmp_4 (char *str, char *str_pattern, Parse_results &regexp)
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

  char *str_temp = str;
  char *temp;
  while (str_temp)
    {
      temp = strstr (str_temp, str_pattern);
      if (temp == nullptr)
        return false;

      if ((!regexp.is_regexp && temp != nullptr)
          || (regexp.is_regexp && temp != nullptr
              && (temp[regexp.pattern_len] == 0 || temp[regexp.pattern_len] == ' '
                  || temp[regexp.pattern_len] == '\t')))
        {
          return true;
        }
      str_temp += regexp.pattern_len;
    }

  return false;
}

void parse_3 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  regexp.pattern_len = strlen (str_pattern);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  strcpy (str_pattern_copy, str_pattern);

  int shift = 0;
  int i = 0;
  if (str_pattern_copy[1] && str_pattern_copy[0] == '\\' && str_pattern_copy[1] == '<')
    {
      regexp.is_regexp = true;
      i = 2;
      shift = 2;
    }

  for (; str_pattern_copy[i]; i++)
    {
      if (str_pattern_copy[i] == '\\' && str_pattern_copy[i + 1])
        {
          if (str_pattern_copy[i + 1] == '\\')
            {
              shift++;
              i++;
              str_pattern_copy[i - shift] = str_pattern_copy[i];
              continue;
            }

          if (str_pattern_copy[i + 1] == '<')
            {
              if (str_pattern_copy[i - 1] == ' ' || str_pattern_copy[i - 1] == '\t')
                {
                  shift += 2;
                  i++;
                  continue;
                }
              else
                {
                  regexp.error = -1;
                  return;
                }
            }

          regexp.error = -1;
          return;
        }
      else
        {
          str_pattern_copy[i - shift] = str_pattern_copy[i];
        }
    }

  str_pattern_copy[regexp.pattern_len - shift] = 0;

  regexp.pattern_len = strlen (str_pattern_copy);
  if (regexp.pattern_len <= 0)
    {
      regexp.error = -1;
      return;
    }

  return;
}

bool cmp_3 (char *str, char *str_pattern, Parse_results &regexp)
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

  char *str_temp = str;
  char *temp;
  while (str_temp)
    {
      temp = strstr (str_temp, str_pattern);
      if (temp == nullptr)
        return false;

      if ((!regexp.is_regexp && temp != nullptr)
          || (regexp.is_regexp && temp != nullptr
              && (temp == str || temp[-1] == ' ' || temp[-1] == '\t')))
        {
          return true;
        }
      str_temp += regexp.pattern_len;
    }

  return false;
}

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
