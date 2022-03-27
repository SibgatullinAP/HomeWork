#include "io.h"
#include "problem_info.h"
#include "tex_table.h"

int main(int argc, const char *argv[]) {

  problem_info problem;
  if (!problem.parse_cmd_line(argc, argv))
    return -1;

  auto problems_info = problem.get_problem_infos();
  std::vector<CDS_solver> solvers;

  int row_limit = 2;
  int col_limit = problem.m_N_period + 1;

  //Filling Solvers
  for (int col = 0; col < col_limit - 1; col++)
    {
       PDE_gas_info &curr_gas_info = problems_info[col].first;
       domain_grid_info &curr_grid_info = problems_info[col].second;

       solvers.push_back(CDS_solver(curr_gas_info, curr_grid_info));
    }

  //Parrallel solving
#ifdef NDEBUG
  #pragma omp parallel for
#endif
  for(unsigned int i = 0; i < solvers.size (); i++)
    solvers[i].solve();

  //Lambdas for tables filling
  auto fill_table = [] (tex_table<std::string> &table, int i, int j, double value)
  {
    char str_buff [MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%1.1e", value);
    str_buff[term_pos] = 0;

    table.get_data(j, i) = std::string (str_buff);
  };

  auto fill_table_int = [] (tex_table<std::string> &table, int i, int j, int value)
  {
    char str_buff [MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%d", value);
    str_buff[term_pos] = 0;

    table.get_data(j, i) = std::string (str_buff);
  };

  auto init_table_metadata = [solvers, fill_table_int, col_limit](tex_table<std::string> &table)
  {
    table.get_data(0, 0) = "$N$";
    table.get_data(0, 1) = "$T_{st}$";

    for (int col = 1; col < col_limit; col++)
      fill_table_int(table, 0, col, solvers[col - 1].m_pde_info.m_N_period);
  };

  //Tables filling
  tex_table time_table (col_limit, row_limit, string_format("Table of stabilize time. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  std::string path_to_tables = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/tables_oscilating_2/";

  init_table_metadata(time_table);

  for (int col = 1; col < col_limit; col++)
    fill_table(time_table, 1, col, solvers[col - 1].get_stab_time());

  std::string time_filename = string_format("Time%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);

  time_table.print_to_tex(path_to_tables + time_filename, "w");
  return 0;
}
