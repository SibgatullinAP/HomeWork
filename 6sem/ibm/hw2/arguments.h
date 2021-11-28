#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "constants.h"
#include "matrix.h"


class arguments
{
private:
  std::string m_file_name = "";
  int m_formula_type = 0;

  int m_matrix_size = 0;
  int m_block_size = 0;
  int m_print_size = 0;

  int m_comm_size = 0;
  int m_rank = 0;

  int m_block_quantity = 0;
  int m_dev = 0;
  int m_rem = 0;

public:
  arguments() = default;
  ~arguments() = default;

  const char* get_file_name () const { return m_file_name.c_str();}
  int get_formula_type () const { return m_formula_type;}

  int get_matrix_size () const { return m_matrix_size;}
  int get_block_size () const { return m_block_size;}
  int get_print_size () const { return m_print_size;}

  int get_comm_size () const { return m_comm_size;}
  int get_rank () const { return m_rank;}

  int get_block_quantity () const { return m_block_quantity;}
  int get_dev () const { return m_dev;}
  int get_rem () const { return m_rem;}

  int get_memmory_size_for_matrix () const;
  int get_matrix_width () const;
  int get_column_size (int j) const;
  int get_column_owner (int j) const;

  bool set_all_arguments (int argc, char *argv[]);
};

#endif // ARGUMENTS_H
