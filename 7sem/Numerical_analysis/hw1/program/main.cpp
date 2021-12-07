#include "io.h"
#include "problem_info.h"
#include "tex_table.h"

int main(int argc, const char *argv[]) {

  problem_info problem;
  if (!problem.parse_cmd_line(argc, argv))
    return -1;

  auto problems_info = problem.get_problem_infos();
  std::vector<CDS_solver> solvers;

  int row_limit = problem.m_gr_factor ? *problem.m_gr_factor + 1 : problem.m_n_max;
  int col_limit = problem.m_m_max;

  //Filling Solvers
  for (int row = 0; row < row_limit; row++)
    {
      for (int col = 0; col < col_limit; col++)
        {
          PDE_gas_info &curr_gas_info = problems_info[col + row * col_limit].first;// (problem.m_mu, problem.m_C, problem.m_gamma);
          domain_grid_info curr_grid_info = problems_info[col + row * col_limit].second;//(problem.m_X, problem_infos[], problem.m_T, nt);

          solvers.push_back(CDS_solver(curr_gas_info, curr_grid_info));
        }
    }

  //Parrallel solving
#ifdef NDEBUG
  #pragma omp parallel for
#endif
  for(unsigned int i = 0; i < solvers.size (); i++)
    solvers[i].solve();

  //Lambdas for tables filling
  auto fill_table_time = [] (tex_table<std::string> &table, int i, int j, double value)
  {
    char str_buff [MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%1.3e", value);
    str_buff[term_pos] = 0;

    table.get_data(j, i) = std::string (str_buff);
  };

  auto fill_table_value = [] (tex_table<std::string> &table, int i, int j, double normc, double norml2, double normw21)
  {
    table.get_data(j, i) = string_format(" $%1.3e$ ", normc) + string_format(" $%1.3e$ ", norml2) + string_format(" $%1.3e$ ", normw21);
  };

  auto init_table_metadata = [&problem, &solvers, fill_table_time](tex_table<std::string> &table)
  {
      if (problem.m_gr_factor)
         table.get_data(0, 0) = "$k / \\tau = h$";
      else
        table.get_data(0, 0) = "$\\tau / h$";

    int row_limit = problem.m_gr_factor ? *problem.m_gr_factor + 1 : problem.m_n_max;
    int col_limit = problem.m_m_max;

    for (int row = 0; row < row_limit; row++)
      {
        double legend_row = problem.m_gr_factor ? *solvers[row * col_limit].m_grid.m_grf : solvers[row * col_limit].m_grid.dt ();
        fill_table_time(table, row + 1, 0, legend_row);
      }

    for (int col = 0; col < col_limit; col++)
      {
        double legend_col = solvers[col].m_grid.dx();
        fill_table_time(table, 0, col + 1, legend_col);
      }
  };

  //Tables filling
  tex_table table_time (col_limit + 1, row_limit + 1, "Table of times.");
  tex_table H_table (col_limit + 1, row_limit + 1, string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  tex_table V_table (col_limit + 1, row_limit + 1, string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  std::string path_to_tables;

  init_table_metadata(table_time);
  init_table_metadata(H_table);
  init_table_metadata(V_table);

  if (problem.m_gr_factor)
    {
      for (int col = 0; col < col_limit; col++)
        {
          CDS_solver &solver = solvers[col];

          double time = solver.get_calc_time();
          fill_table_time (table_time, 1, col + 1, time);

          math_vec ethalon_H = solver.get_ethalon_H();
          math_vec ethalon_V = solver.get_ethalon_V();

          math_vec answer_H = solver.get_answer_H();
          math_vec answer_V = solver.get_answer_V();

          math_vec diff_H = vec_diffs(ethalon_H, answer_H);
          math_vec diff_V = vec_diffs(ethalon_V, answer_V);

          fill_table_value (H_table, 1, col + 1, norm_c(diff_H), norm_l2(diff_H, solver.m_grid.dx()), norm_w21(diff_H, solver.m_grid.dx()));
          fill_table_value (V_table, 1, col + 1, norm_c(diff_V), norm_l2(diff_V, solver.m_grid.dx()), norm_w21(diff_V, solver.m_grid.dx()));
        }

      for (int row = 1; row < row_limit; row++)
        {
          for (int col = 0; col < col_limit; col++)
            {
              CDS_solver &solver = solvers[col + row * col_limit];
              CDS_solver &solver_ethalon = solvers[col];

              double time = solver.get_calc_time();
              fill_table_time (table_time, row + 1, col + 1, time);

              math_vec ethalon_H = solver_ethalon.get_ethalon_H();
              math_vec ethalon_V = solver_ethalon.get_ethalon_V();

              math_vec answer_H = solver.get_answer_H();
              math_vec answer_V = solver.get_answer_V();

              math_vec diff_H = vec_diffs(ethalon_H, answer_H);
              math_vec diff_V = vec_diffs(ethalon_V, answer_V);

              fill_table_value (H_table, row + 1, col + 1, norm_c(diff_H), norm_l2(diff_H, solver.m_grid.dx()), norm_w21(diff_H, solver.m_grid.dx()));
              fill_table_value (V_table, row + 1, col + 1, norm_c(diff_V), norm_l2(diff_V, solver.m_grid.dx()), norm_w21(diff_V, solver.m_grid.dx()));
            }
        }

      path_to_tables = "/home/artur.sibgatullin/HomeWork/7sem/Numerical_analysis/hw1/tables_grf/";
    }
  else
    {
      for (int row = 0; row < row_limit; row++)
        {
          for (int col = 0; col < col_limit; col++)
            {
              CDS_solver &solver = solvers[col + row * col_limit];

              double time = solver.get_calc_time();
              fill_table_time (table_time, row + 1, col + 1, time);

              math_vec ethalon_H = solver.get_ethalon_H();
              math_vec ethalon_V = solver.get_ethalon_V();

              math_vec answer_H = solver.get_answer_H();
              math_vec answer_V = solver.get_answer_V();

              math_vec diff_H = vec_diffs(ethalon_H, answer_H);
              math_vec diff_V = vec_diffs(ethalon_V, answer_V);

              fill_table_value (H_table, row + 1, col + 1, norm_c(diff_H), norm_l2(diff_H, solver.m_grid.dx()), norm_w21(diff_H, solver.m_grid.dx()));
              fill_table_value (V_table, row + 1, col + 1, norm_c(diff_V), norm_l2(diff_V, solver.m_grid.dx()), norm_w21(diff_V, solver.m_grid.dx()));
            }
        }

      path_to_tables = "/home/artur.sibgatullin/HomeWork/7sem/Numerical_analysis/hw1/tables/";
    }

  std::string h_filename = string_format("H_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);
  std::string v_filename = string_format("V_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);

  table_time.print_to_tex(path_to_tables + "Times.tex", "w");
  H_table.print_to_tex(path_to_tables + h_filename, "w");
  V_table.print_to_tex(path_to_tables + v_filename, "w");

  return 0;
}
