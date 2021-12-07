#include "io.h"
#include "problem_info.h"
#include "tex_table.h"

int main(int argc, const char *argv[]) {

  problem_info problem;
  if (!problem.parse_cmd_line(argc, argv))
    return -1;

  auto problem_infos = problem.get_problem_infos();
  std::vector<CDS_solver> solvers;

  unsigned int nt = problem.m_N0;
  unsigned int nx = problem.m_M0;

  //Filling Solvers
  for (int time_ref = 0; time_ref < problem.m_n_max; time_ref++)
    {
      nx = problem.m_M0;
      for (int domain_ref = 0; domain_ref < problem.m_m_max; domain_ref++)
        {
          PDE_gas_info curr_gas_info (problem.m_mu, problem.m_C, problem.m_gamma);
          domain_grid_info curr_grid_info (problem.m_X, nx, problem.m_T, nt);

          solvers.push_back(CDS_solver(curr_gas_info, curr_grid_info));
          nx *= problem.m_k_dr;
        }
      nt *= problem.m_k_dr;
    }

  //Parrallel solving
#ifdef NDEBUG
  #pragma omp parallel for
#endif
  for(unsigned int i = 0; i < solvers.size (); i++)
    solvers[i].solve();

  //Tables filling
  tex_table table_time (problem.m_m_max + 1, problem.m_n_max + 1, "Table of times.");

  tex_table H_table (problem.m_m_max + 1, problem.m_n_max + 1, string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
  tex_table V_table (problem.m_m_max + 1, problem.m_n_max + 1, string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));

  auto fill_table_time = [] (tex_table<std::string> &table, int i, int j, double value) {
    char str_buff [MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%1.3e", value);
    str_buff[term_pos] = 0;

    table.get_data(j, i) = std::string (str_buff);
  };

  auto fill_table_value = [] (tex_table<std::string> &table, int i, int j, double normc, double norml2, double normw21) {
    table.get_data(j, i) = string_format(" $%1.3e$ ", normc) + string_format(" $%1.3e$ ", norml2) + string_format(" $%1.3e$ ", normw21);
  };

  auto init_table_metadata = [&problem, &solvers, fill_table_time](tex_table<std::string> &table) {
    table.get_data(0, 0) = "$\\tau / h$";
    for (int time_ref = 0; time_ref < problem.m_n_max; time_ref++) {
      double dt = solvers[time_ref * problem.m_m_max].m_grid.dt();
      fill_table_time(table, time_ref + 1, 0, dt);
    }

    for (int domain_ref = 0; domain_ref < problem.m_m_max; domain_ref++) {
      double dx = solvers[domain_ref].m_grid.dx();
      fill_table_time(table, 0, domain_ref + 1, dx);
    }
  };

  init_table_metadata(table_time);
  init_table_metadata(H_table);
  init_table_metadata(V_table);

  for (int time_ref = 0; time_ref < problem.m_n_max; time_ref++)
    {
      for (int domain_ref = 0; domain_ref < problem.m_m_max; domain_ref++)
        {
          CDS_solver &solver = solvers[domain_ref + time_ref * problem.m_m_max];

          double time  = solver.get_calc_time();
          fill_table_time (table_time, time_ref + 1, domain_ref + 1, time);

          math_vec ethalon_H = solver.get_ethalon_H();
          math_vec ethalon_V = solver.get_ethalon_V();

          math_vec answer_H = solver.get_answer_H();
          math_vec answer_V = solver.get_answer_V();

          math_vec diff_H = vec_diffs(ethalon_H, answer_H);
          math_vec diff_V = vec_diffs(ethalon_V, answer_V);

          fill_table_value (H_table, time_ref + 1, domain_ref + 1, norm_c(diff_H), norm_l2(diff_H, solver.m_grid.dx()), norm_w21(diff_H, solver.m_grid.dx()));
          fill_table_value (V_table, time_ref + 1, domain_ref + 1, norm_c(diff_V), norm_l2(diff_V, solver.m_grid.dx()), norm_w21(diff_V, solver.m_grid.dx()));
        }
    }

  std::string path_to_tables = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/tables/";

  table_time.print_to_tex(path_to_tables + "Times.tex", "w");

  std::string h_filename = string_format("H_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);
  std::string v_filename = string_format("V_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);

  H_table.print_to_tex(path_to_tables + h_filename, "w");
  V_table.print_to_tex(path_to_tables + v_filename, "w");

  return 0;
}
