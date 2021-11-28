#include "io.h"

void printf_to_main_process (const char *format, ...)
{
  int my_rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  va_list args;
  va_start (args, format);

  if (my_rank == 0)
    vprintf (format, args);

  va_end (args);
}

void print_arr (double *arr, int size)
{
  int my_rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  for (int i = 0; i < size && i < MAX_PRINT; i++)
    printf_to_main_process ("%lf ", arr[i]);

  printf_to_main_process ("\n");
}

int read_arr (double *arr, int size, const char *file_name)
{
  FILE *file = fopen (file_name, "r");
  if (file == nullptr)
    return CANNOT_OPEN_FILE;

  for (int i = 0; i < size; i++)
    {
      if (fscanf (file, "%lf", arr + i) != 1)
        return fclose (file), CANNOT_READ_FILE;
    }

  fclose (file);
  return OK;
}


void init_formula (double *arr, int size)
{
  auto func = [] (int ind)->double {
      return ind;
    };

  for (int i = 0; i < size; i++)
    arr[i] = func (i);
}

int error_hadler (int error_code, const char *object_name)
{
  switch (error_code)
    {
    case CANNOT_OPEN_FILE:
      printf_to_main_process ("[ERROR] Can't open %s\n", object_name);
      break;
    case CANNOT_READ_FILE:
      printf_to_main_process ("[ERROR] Can't read %s\n", object_name);
      break;
    case INVALID_FILE:
      printf_to_main_process ("[ERROR] Invalid file %s (only part of the file is read)\n", object_name);
      break;
    default:
      printf_to_main_process ("[ERROR] Unknown error\n");
    }

  return 0;
}
