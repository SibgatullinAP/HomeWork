#include "io.h"
#include "problem_info.h"
#include "tex_table.h"

int main(int argc, const char *argv[]) {

  problem_info problem;
  if (!problem.parse_cmd_line(argc, argv))
    return -1;

  auto problems_info = problem.get_problem_infos();
  std::vector<CDS_solver> solvers;

  int row_limit = problem.m_gr_factor.value_or(0) + 2;
  int col_limit = 6;

  //Filling Solvers
  for (int row = 0; row < row_limit - 1; row++)
    {
       PDE_gas_info &curr_gas_info = problems_info[row].first;
       domain_grid_info &curr_grid_info = problems_info[row].second;

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
    int term_pos = std::sprintf(str_buff, "%1.3e", value);
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


  auto fill_table_value = [] (tex_table<std::string> &table, int i, int j, double normc, double norml2, double normw21)
  {
    table.get_data(j, i) = string_format(" $%1.3e$ ", normc) + string_format(" $%1.3e$ ", norml2) + string_format(" $%1.3e$ ", normw21);
  };

  auto init_table_metadata = [solvers, fill_table_int, row_limit](tex_table<std::string> &table)
  {
    table.get_data(0, 0) = "$K$";
    table.get_data(1, 0) = "$N_0$";
    table.get_data(2, 0) = "$N_0 \\tau$";
    table.get_data(3, 0) = "$n = \\frac{N_0}{4}$";
    table.get_data(4, 0) = "$n = \\frac{N_0}{2}$";
    table.get_data(5, 0) = "$n = \\frac{3N_0}{4}$";
    table.get_data(6, 0) = "$n = N_0$";

    for (int row = 1; row < row_limit; row++)
       fill_table_int(table, row, 0, solvers[row - 1].m_grid.m_grf.value_or(0));
  };

  //Tables filling
  tex_table H_table (col_limit + 1, row_limit, string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  tex_table V_table (col_limit + 1, row_limit, string_format("Table of norms for V. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  tex_table Mass_table (col_limit + 1, row_limit, string_format("Table of mass loss. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  std::string path_to_tables = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/tables_nonsmooth_2/";

  init_table_metadata(H_table);
  init_table_metadata(V_table);
  init_table_metadata(Mass_table);

  fill_table_int (V_table, 1, 1, solvers[0].get_stab_step());
  fill_table (V_table, 1, 2, solvers[0].get_stab_time());
  fill_table (V_table, 1, 3, abs (norm_c (solvers[0].get_v_n4 ())));
  fill_table (V_table, 1, 4, abs (norm_c (solvers[0].get_v_n2 ())));
  fill_table (V_table, 1, 5, abs (norm_c (solvers[0].get_v_3n4 ())));
  fill_table (V_table, 1, 6, abs (norm_c (solvers[0].get_v_n ())));


  fill_table_int (Mass_table, 1, 1, solvers[0].get_stab_step());
  fill_table (Mass_table, 1, 2, solvers[0].get_stab_time());
  fill_table (Mass_table, 1, 3, solvers[0].get_mass_n4 ());
  fill_table (Mass_table, 1, 4, solvers[0].get_mass_n2 ());
  fill_table (Mass_table, 1, 5, solvers[0].get_mass_3n4 ());
  fill_table (Mass_table, 1, 6, solvers[0].get_mass_n ());

  for (int row = 2; row < row_limit; row++)
    {
      fill_table_int (V_table, row, 1, solvers[row - 1].get_stab_step());
      fill_table (V_table, row, 2, solvers[row - 1].get_stab_time());
      fill_table (V_table, row, 3, abs (norm_c (solvers[row - 1].get_v_n4 ())));
      fill_table (V_table, row, 4, abs (norm_c (solvers[row - 1].get_v_n2 ())));
      fill_table (V_table, row, 5, abs (norm_c (solvers[row - 1].get_v_3n4 ())));
      fill_table (V_table, row, 6, abs (norm_c (solvers[row - 1].get_v_n ())));

      fill_table_int (Mass_table, row, 1, solvers[row - 1].get_stab_step());
      fill_table (Mass_table, row, 2, solvers[row - 1].get_stab_time());
      fill_table (Mass_table, row, 3, solvers[row - 1].get_mass_n4 ());
      fill_table (Mass_table, row, 4, solvers[row - 1].get_mass_n2 ());
      fill_table (Mass_table, row, 5, solvers[row - 1].get_mass_3n4 ());
      fill_table (Mass_table, row, 6, solvers[row - 1].get_mass_n ());
    }

  std::string h_filename = string_format("H_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);
  std::string v_filename = string_format("V_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);
  std::string mass_filename = string_format("Mass_loss_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);

  H_table.print_to_tex(path_to_tables + h_filename, "w");
  V_table.print_to_tex(path_to_tables + v_filename, "w");
  Mass_table.print_to_tex(path_to_tables + mass_filename, "w");

  return 0;
}
