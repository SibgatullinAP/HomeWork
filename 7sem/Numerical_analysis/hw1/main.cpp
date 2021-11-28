#include "tex_table.h"


int main(int argc, const char *argv[])
{
  tex_table table (2, 3, "puck");
  for (unsigned int row_id = 0; row_id < table.row_count(); row_id++)
    {
      for (unsigned int column_id = 0; column_id < table.column_count(); column_id++)
        table.get_data(column_id, row_id) = "a";
    }

  table.print_to_tex ("/home/pam/HomeWork/7sem/Numerical_analysis/hw1/my.tex", "a");


  return 0;
}
