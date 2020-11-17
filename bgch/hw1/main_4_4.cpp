#include "string_.h"

int main (int argc, char *argv[])
{
  if (argc != 5)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mPlease, use: "
              "%s M N Space_string File_name\n", argv[0]);
      return -1;
    }
  int m_matrix_size = atoi (argv[1]);
  int n_matrix_size = atoi (argv[2]);

  if (m_matrix_size == 0 || n_matrix_size == 0)
    {
      printf ("\x1b[31m[ERROR] \x1b[0m M and N "
              "should be positive integer\n");
      return -1;
    }

  char **matrix = (char**) malloc (m_matrix_size
                                   * n_matrix_size * sizeof (char*));
  if (matrix == NULL)
    {
      printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory\n");
      return -1;
    }
  for (int i = 0; i < m_matrix_size * n_matrix_size; i++)
      matrix[i] = NULL;

  char *space_string = argv[3];
  char *file_name = argv[4];
  int ret = read (file_name, matrix, m_matrix_size,
                  n_matrix_size, space_string);
  if (ret < 0)
    {
      switch (ret)
        {
        case CANNOT_OPEN_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't open %s\n", file_name);
          break;
        case CANNOT_READ_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mCan't read %s\n", file_name);
          break;
        case INVALID_FILE:
          printf ("\x1b[31m[ERROR] \x1b[0mInvalid file %s"
                  " (only part of the file is read)\n", file_name);
          break;
        case NOT_ENOUGH_MEMMORY:
          printf ("\x1b[31m[ERROR] \x1b[0mNot enough memmory\n");
          break;
        default:
          printf ("\x1b[31m[ERROR] \x1b[0mUnknown error\n");
        }
      free_ (matrix, m_matrix_size, n_matrix_size);
      return -3;
    }

  printf ("\x1b[32m[OUTPUT] \x1b[0mMatrix:\n");
  print (matrix, m_matrix_size, n_matrix_size);

  double time = clock ();
  quick_sort (matrix, m_matrix_size, n_matrix_size);
  time = (clock () - time) / CLOCKS_PER_SEC;

  printf ("\x1b[32m[OUTPUT] \x1b[0mArray after sorting:\n");
  print (matrix, m_matrix_size, n_matrix_size);

  printf ("\x1b[32m[OUTPUT] \x1b[0mTime = %.4lf\n", time);

  free_ (matrix, m_matrix_size, n_matrix_size);

  return 0;
}
