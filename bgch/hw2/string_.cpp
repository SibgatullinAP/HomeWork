#include "string_.h"

void parse_2 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  int i = 0;
  int shift = 0;

  if (strlen (str_pattern) <= 0)
    {
      regexp.error = -1;
      return;
    }

  for (i = 0, shift = 0; str_pattern[i]; i++)
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
          str_pattern_copy[shift] = str_pattern[i];
          shift++;
          continue;
        }
      str_pattern_copy[shift] = str_pattern[i];
      shift++;

    }
  str_pattern_copy[shift] = str_pattern[i];

  regexp.pattern_len = shift;
  return ;
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

  if ((regexp.is_regexp && strstr (str + i - regexp.pattern_len, str_pattern) != nullptr)
      || (strstr (str, str_pattern) != nullptr))
    return true;

  return false;
}

void parse_1 (char *str_pattern, char *str_pattern_copy, Parse_results &regexp)
{
  if (*str_pattern == '^')
    regexp.is_regexp = true;

  for (int i = 0; str_pattern[i]; i++)
    {
      if (str_pattern[i] == '\\')
        {
          i++;
          if ((str_pattern[i] != '\\') && str_pattern[i] != '^')
            {
              regexp.error = -1;
              return ;
            }
        }
    }

  int shift = 0;
  if (str_pattern[0] == '^')
    shift = 1;

  for (int i = 0; i < STRING_BUFF_LEN && str_pattern[shift]; i++, shift++)
    {
      if (str_pattern[shift] == '\\')
        shift++;

      str_pattern_copy[i] = str_pattern[shift];
    }

  if (str_pattern[shift])
    {
      regexp.error = -1;
      return;
    }

  return ;
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

  if ((regexp.is_regexp && strstr (str, str_pattern) == str)
      || (strstr (str, str_pattern) != NULL))
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
