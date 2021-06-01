#include "arguments.h"

bool arguments::set_all_arguments (int argc, char *argv[])
{

  if (argc != 5 && argc != 6)
    {
      printf_to_main_process ("[ERROR] Please, use: %s Matrix_size Block_size Print_size Formula_type (File_name)\n", argv[0]);
      return false;
    }

  int matrix_size = atoi (argv[1]);
  int block_size = atoi (argv[2]);
  int print_size = atoi (argv[3]);

  if (matrix_size <= 0 || block_size <= 0 || print_size <= 0)
    {
      printf_to_main_process ("[ERROR] Matrix_size, Block_size and Print_size should be a positive integer.\n");
      return false;
    }

  int formula_type = atoi (argv[4]);
  if (argc == 5 && ((formula_type == 0 && strcmp (argv[4], "0") != 0)
                    || (formula_type > 4 || formula_type < 0)))
    {
      printf_to_main_process ("[ERROR] Formula_type should be an integer in [0;4].\n");
      return false;
    }
  if (argc == 5 && formula_type == 0)
    {
      printf_to_main_process ("[ERROR] Formula_type should be an integer in [0;4], "
              "it can be equals to 0 iff File_name argument is empty.\n");
      return false;
    }

  if (argc == 6)
    {
      if (formula_type != 0)
        {
          printf_to_main_process ("[ERROR] Formula_type should be equals to 0 if File_name argument isn't empty.\n");
          return false;
        }

      m_file_name = argv[5];
    }

  m_formula_type = formula_type;

  MPI_Comm_rank (MPI_COMM_WORLD, &m_rank);
  MPI_Comm_size (MPI_COMM_WORLD, &m_comm_size);

  m_matrix_size = matrix_size;
  m_block_size = block_size;
  m_print_size = print_size;

  //print_size = (pr_s < m_s) ? pr_s : m_s;

  m_dev = matrix_size / block_size;
  m_rem = matrix_size % block_size;

  m_block_quantity = m_dev + (m_rem > 0);

  return true;
}

int arguments::get_memmory_size_for_matrix () const
{
  int size = 0;
  int i = 0;
  for (i = 0; i < m_dev; i++)
    {
      if (i % m_comm_size == m_rank)
        size += m_matrix_size * m_block_size;
    }
  if (m_rem != 0)
    {
      if (i % m_comm_size == m_rank)
        size += m_matrix_size * m_rem;
    }

  return size;
}

int arguments::get_matrix_width () const
{
  return get_memmory_size_for_matrix () / m_matrix_size;
}

int arguments::get_column_size (int j) const
{
  return j == m_block_quantity ? m_rem : m_block_size;
}

int arguments::get_column_owner (int j) const
{
  return j % m_comm_size;
}
