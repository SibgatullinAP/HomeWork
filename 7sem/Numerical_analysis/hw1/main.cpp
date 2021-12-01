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
          PDE_gas_info curr_gas_info (problem.m_mu);
          domain_grid_info curr_grid_info (problem.m_X, nx, problem.m_T, nt);

          solvers.push_back(CDS_solver(curr_gas_info, curr_grid_info));
          nx *= problem.m_k_dr;
        }
      nt *= problem.m_k_dr;
    }

  //Parrallel solving
//  #pragma omp parallel for
  for(unsigned int i = 0; i < solvers.size (); i++)
    solvers[i].solve();

  //Tables filling
  tex_table table_time (problem.m_n_max + 1, problem.m_m_max + 1, "Table of times");

  tex_table H_table_c (problem.m_n_max + 1, problem.m_m_max + 1, "Table of C norms (H)");
  tex_table H_table_l2 (problem.m_n_max + 1, problem.m_m_max + 1, "Table of L2 norms (H)");
  tex_table H_table_w21 (problem.m_n_max + 1, problem.m_m_max + 1, "Table of W21 norms (H)");

  tex_table V_table_c (problem.m_n_max + 1, problem.m_m_max + 1, "Table of C norms (V)");
  tex_table V_table_l2 (problem.m_n_max + 1, problem.m_m_max + 1, "Table of L2 norms (V)");
  tex_table V_table_w21 (problem.m_n_max + 1, problem.m_m_max + 1, "Table of W21 norms (V)");

  auto fill_table = [] (tex_table<std::string> &table, int i, int j, double value) {
    char str_buff [MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%1.3e", value);
    str_buff[term_pos] = 0;

    table.get_data(i, j) = std::string (str_buff);
  };

  auto init_table_metadata = [&problem, fill_table](tex_table<std::string> &table) {

    unsigned int nt = problem.m_N0;
    unsigned int nx = problem.m_M0;

    table.get_data(0, 0) = "$\\tau / h$";
    for (int time_ref = 0; time_ref < problem.m_n_max; time_ref++) {
      fill_table(table, 0, time_ref + 1, problem.m_T / nt);
      nt *= problem.m_k_dr;
    }

    for (int domain_ref = 0; domain_ref < problem.m_m_max; domain_ref++) {
      fill_table(table, domain_ref + 1, 0, problem.m_X / nx);
      nx *= problem.m_k_dr;
    }
  };

  init_table_metadata(table_time);

  init_table_metadata(H_table_c);
  init_table_metadata(H_table_l2);
  init_table_metadata(H_table_w21);

  init_table_metadata(V_table_c);
  init_table_metadata(V_table_l2);
  init_table_metadata(V_table_w21);

  init_table_metadata(H_table_c);

  for (int time_ref = 0; time_ref < problem.m_n_max; time_ref++)
    {
      for (int domain_ref = 0; domain_ref < problem.m_m_max; domain_ref++)
        {
          CDS_solver &solver = solvers[domain_ref + time_ref * problem.m_m_max];

          double time  = solver.get_calc_time();
          fill_table (table_time, time_ref + 1, domain_ref + 1, time);

          math_vec ethalon_H = solver.get_ethalon_H();
          math_vec ethalon_V = solver.get_ethalon_V();

          math_vec answer_H = solver.get_answer_H();
          math_vec answer_V = solver.get_answer_V();

          math_vec diff_H = vec_diffs(ethalon_H, answer_H);
          math_vec diff_V = vec_diffs(ethalon_V, answer_V);

          fill_table (H_table_c, time_ref + 1, domain_ref + 1, norm_c(diff_H));
          fill_table (H_table_l2, time_ref + 1, domain_ref + 1, norm_c(diff_H));
          fill_table (H_table_w21, time_ref + 1, domain_ref + 1, norm_c(diff_H));

          fill_table (V_table_c, time_ref + 1, domain_ref + 1, norm_c(diff_V));
          fill_table (V_table_l2, time_ref + 1, domain_ref + 1, norm_c(diff_V));
          fill_table (V_table_w21, time_ref + 1, domain_ref + 1, norm_c(diff_V));
        }
    }

//  std::string path_to_tables = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/tables/";

//  table_time.print_to_tex(path_to_tables + "Times.tex", "w");

//  H_table_c.print_to_tex(path_to_tables + "H_C_norms.tex", "w");
//  H_table_l2.print_to_tex(path_to_tables + "H_L2_norms.tex", "w");
//  H_table_w21.print_to_tex(path_to_tables + "H_W21_norms.tex", "w");

//  V_table_c.print_to_tex(path_to_tables + "V_C_norms.tex", "w");
//  V_table_l2.print_to_tex(path_to_tables + "V_L2_norms.tex", "w");
//  V_table_w21.print_to_tex(path_to_tables + "V_W21_norms.tex", "w");

  return 0;
}
