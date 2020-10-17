#include "string_.h"

int read (const char *file_name, char **arr, int size)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  char buff[STRING_BUFF] = {0};
  for (int i = 0; i < size; i ++)
    {
      if (fgets (buff, STRING_BUFF, file) == NULL)
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }

      int len = strlen (buff);
      if (buff[len - 1] == '\n')
        buff[len - 1] = 0;
      arr[i] = (char*) malloc ((len + 1) * sizeof (char));
      if (arr[i] == NULL)
        {
          fclose (file);
          return NOT_ENOUGH_MEMMORY;
        }
      strcpy (arr[i], buff);
    }

  fclose (file);
  return 0;
}

void print (char **arr, int size)
{
  int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (int i = 0; i < print_limit; i++)
    printf ("\t[%d] = %s\n", i, arr[i]);
}

void free_ (char **arr, int size)
{
  for (int i =0; i < size; i++)
    {
      if (arr[i] != NULL)
        free (arr[i]);
    }
  if (arr != NULL)
    free (arr);
}

//4_1
int strcspn_ (const char *string_1, const char *string_2)
{
  int i = 0, j = 0;
  int int_size_bit = 8 * sizeof (int);
  int int_size_bit_sgn = 7 * sizeof (int);
  unsigned int buff[256 / (8 * sizeof (int))] = {0};

  int temp = int_size_bit;
  for (i = 0; temp > 0; i++)
    temp >>= i;

  int pow_2_int_size_bit = i;
  for (i = 0; string_2[i]; i++)
    {
      j = (unsigned int) string_2[i];
      buff[j >> pow_2_int_size_bit] |= (1 << (int_size_bit_sgn - (j & (int_size_bit - 1))));
    }

  for (i = 0; string_1[i]; i ++)
    {
      j = (unsigned int) string_1[i];
      if (buff[j >> pow_2_int_size_bit] & (1 << (int_size_bit_sgn - (j & (int_size_bit - 1)))))
        return i;
    }

  return i;
}

//4_2
int array_rebuilding_1 (char **arr, int size, int k, char *string)
{
  int shift = 0;
  int entry_counter = 0;
  for (int i = 0; i < size; i++)
    {
      if (strstr (arr[i], string) != NULL)
        entry_counter++;
      else
        {
          if (entry_counter >= k)
            shift += entry_counter;
          entry_counter = 0;
        }

      if (shift != 0)
        {
          free (arr[i - shift]);
          arr[i - shift] = arr[i];
          arr[i] = 0;
        }
    }
  if (entry_counter >= k)
    shift += entry_counter;

  return size - shift;
}

//4_3
int array_rebuilding_2 (char **arr, int size, int k, char *string)
{
  int i = 0;
  int j = 0;
  int int_size_bit = 8 * sizeof (int);
  int int_size_bit_sgn = 7 * sizeof (int);
  unsigned int buff[256 / (8 * sizeof (int))] = {0};

  int temp = int_size_bit;
  for (i = 0; temp > 0; i++)
    temp >>= i;

  int pow_2_int_size_bit = i;
  for (i = 0; string[i]; i++)
    {
      j = (unsigned int) string[i];
      buff[j >> pow_2_int_size_bit] |= (1 << (int_size_bit_sgn - (j & (int_size_bit - 1))));
    }

  int l = 0;
  int shift = 0;
  bool flag = false;
  int entry_counter = 0;
  for (i = 0; i < size; i++)
    {
      flag = true;
      for (j = 0; arr[i][j]; j++)
        {
          l = (unsigned int) arr[i][j];
          if (!(buff[l >> pow_2_int_size_bit] &
                (1 << (int_size_bit_sgn - (l & (int_size_bit - 1))))))
            {
              flag = false;
              break;
            }
        }

      if (flag)
        entry_counter++;
      else
        {
          if (entry_counter >= k)
            shift += entry_counter;
          entry_counter = 0;
        }

      if (shift != 0)
        {
          free (arr[i - shift]);
          arr[i - shift] = arr[i];
          arr[i] = 0;
        }
    }
  if (entry_counter >= k)
    shift += entry_counter;

  return size - shift;
}

//4_4
int read (const char *file_name, char** matrix, int m_matrix_size,
          int n_matrix_size, char* space_string)
{
  FILE *file = fopen (file_name, "r");
  if (file == NULL)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < m_matrix_size; i++)
    {
      char buff[STRING_BUFF] = {0};
      if (fgets (buff, STRING_BUFF, file) == NULL)
        {
          fclose (file);
          return CANNOT_READ_FILE;
        }
      char *saveptr;
      char *word = strtok_r (buff, space_string, &saveptr);
      for (int j = 0; j < n_matrix_size; j++)
        {
          if (word != NULL)
            {
              int len = strlen (word);
              matrix[i * n_matrix_size + j]
                  = (char*) malloc ((len + 1) * sizeof (char));
              if (matrix[i * n_matrix_size + j] == NULL)
                {
                  fclose (file);
                  return NOT_ENOUGH_MEMMORY;
                }

              if (word[len - 1] == '\n')
                word[len - 1] = 0;
              else
                word[len] = 0;

              strcpy (matrix[i * n_matrix_size + j], word);
            }
          else
            {
              matrix[i * n_matrix_size + j]
                  = (char*) malloc (sizeof (char));
              if (matrix[i * n_matrix_size + j] == NULL)
                {
                  fclose (file);
                  return NOT_ENOUGH_MEMMORY;
                }
              matrix[i * n_matrix_size + j][0] = 0;
            }
          word = strtok_r (NULL, space_string, &saveptr);
        }
    }

  fclose (file);
  return 0;
}

void print (char **matrix, int m_matrix_size, int n_matrix_size)
{
  int m_print_limit = ((m_matrix_size > M_MAX_PRINT)
                       ? M_MAX_PRINT : m_matrix_size);
  int n_print_limit = ((n_matrix_size > N_MAX_PRINT)
                       ? N_MAX_PRINT : n_matrix_size);
  for (int i = 0; i < m_print_limit; i++)
    {
      for (int j = 0; j < n_print_limit; j++)
        {
          printf ("|%20s|", matrix[i * n_matrix_size + j]);
        }
      printf ("\n");
    }
}

void free_ (char **matrix, int m_matrix_size, int n_matrix_size)
{
  for (int i =0; i < m_matrix_size * n_matrix_size; i++)
    {
      if (matrix[i] != NULL)
        free (matrix[i]);
    }

  if (matrix != NULL)
    free (matrix);
}

void swap_lines (char **matrix, int n_matrix_size, int i, int j)
{
  char *temp;
  int i_p = i * n_matrix_size;
  int j_p = j * n_matrix_size;
  for (int k = 0; k < n_matrix_size; k++)
    {
      temp = matrix[i_p + k];
      matrix[i_p + k] = matrix[j_p + k];
      matrix[j_p + k] = temp;
    }
}

int  max_of_line (char **matrix, int n_matrix_size, int i)
{
  int max_position = 0;
  int i_p = i * n_matrix_size;
  for (int j = 0; j < n_matrix_size; j++)
    {
      if (strcmp(matrix[i_p + j], matrix[i_p + max_position]) > 0)
        max_position = j;
    }
  return max_position;
}

int cmp_lines (char **matrix, int n_matrix_size, int i, int j)
{
  char* i_max = matrix[i * n_matrix_size];
  char* j_max = matrix[j * n_matrix_size];
  int i_p = i * n_matrix_size;
  int j_p = j * n_matrix_size;
  for (int k = 0; k < n_matrix_size; k++)
    {
      if (strcmp(matrix[i_p + k], i_max) > 0)
        i_max = matrix[i_p + k];

      if (strcmp(matrix[j_p + k], j_max) > 0)
        j_max = matrix[j_p + k];
    }

  return strcmp (i_max, j_max);
}

int cmp_line_with_element (char **matrix, int n_matrix_size, int i, char * j)
{
  char* i_max = matrix[i * n_matrix_size];
  int i_p = i * n_matrix_size;
  for (int k = 0; k < n_matrix_size; k++)
    {
      if (strcmp(matrix[i_p + k], i_max) > 0)
        i_max = matrix[i_p + k];
    }
  return strcmp (i_max, j);
}

int matrix_redbuilding (char **matrix, int m_matrix_size,
                        int n_matrix_size, int i)
{
  int left = 0;
  int right = m_matrix_size - 1;
  char *i_max = matrix[i * n_matrix_size
      + max_of_line(matrix, n_matrix_size, i)];
  while (left <= right)
    {
      while (left < m_matrix_size && cmp_line_with_element(matrix, n_matrix_size, left, i_max) > 0)
        left++;
      while (right >= 0 && cmp_line_with_element(matrix, n_matrix_size, right, i_max) < 0)
        right--;
      if (left <= right)
        {
          swap_lines (matrix, n_matrix_size, left, right);
          right--;
          left++;
        }
    }
  return left;
}

void quick_sort (char **matrix, int m_matrix_size, int n_matrix_size)
{
  int position;
  int base_element;

  if (m_matrix_size < 2)
    return ;

  while (m_matrix_size > 2)
    {
      base_element = m_matrix_size / 2;
      position = matrix_redbuilding (matrix, m_matrix_size,
                                     n_matrix_size, base_element);
      if (position < m_matrix_size - position)
        {
          quick_sort (matrix, position, n_matrix_size);
          matrix += position * n_matrix_size;
          m_matrix_size -= position;
        }
      else
        {
          quick_sort (matrix + position * n_matrix_size,
                      m_matrix_size - position, n_matrix_size);
          m_matrix_size = position;
        }
    }
  if (m_matrix_size == 2
      && (cmp_lines(matrix, n_matrix_size,
                    m_matrix_size - 2, m_matrix_size - 1) < 0))

    swap_lines (matrix, n_matrix_size, m_matrix_size - 2, m_matrix_size - 1);
  return ;
}