#include "io.h"
#include "problem_info.h"
#include "tex_table.h"

int main(int argc, const char *argv[]) {

  problem_info problem;
  if (!problem.parse_cmd_line(argc, argv))
    return -1;

  auto problems_info = problem.get_problem_infos();
  std::vector<CDS_solver> solvers;

  int row_limit = 5;
  int col_limit = 5;

  //Filling Solvers
  for (unsigned int row = 0; row < row_limit - 1; row++)
    {
      for (unsigned int col = 0; col < col_limit - 1; col++)
        {
          PDE_gas_info curr_gas_info = problems_info[(row_limit - 1) * row + col].first;
          domain_grid_info curr_grid_info = problems_info[(row_limit - 1) * row + col].second;

          solvers.push_back(CDS_solver(curr_gas_info, curr_grid_info));
        }
    }

  //Parrallel solving
#ifdef NDEBUG
  #pragma omp parallel for
#endif
  for(unsigned int i = 0; i < 1; i++)
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

  auto init_table_metadata = [&](tex_table<std::string> &table)
  {
    table.get_data(0, 0) = "$\\tilde{\\rho} / \\tilde{v}$";

    for (int row = 1; row < row_limit; row++)
       fill_table_int(table, row, 0, row);

    for (int col = 1; col < col_limit; col++)
       fill_table_int(table, 0, col, col);
  };

//  //Tables filling
//  tex_table Time_table (col_limit, row_limit, string_format("Table of stabilization time. $\\mu = %1.4lf$, $C = %1.4lf$, $\\gamma = %1.4lf$", problem.m_mu, problem.m_C, problem.m_gamma));
//  std::string path_to_tables = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/tables_flow/";

//  init_table_metadata(Time_table);

//  for (unsigned int row = 0; row < row_limit - 1; row++)
//    {
//      for (unsigned int col = 0; col < col_limit - 1; col++)
//          fill_table (Time_table, row + 1, col + 1, solvers[row * (row_limit - 1) + col].get_stab_time());
//    }


//  std::string time_filename = string_format("Time_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", problem.m_mu, problem.m_C, problem.m_gamma);
//  Time_table.print_to_tex(path_to_tables + time_filename, "w");

  std::string path_to_graphs = "/home/pam/HomeWork/7sem/Numerical_analysis/hw1/graph_data_flow/";
  std::string grap_filename = string_format("Slices_mu%1.3lf_C%1.3lf_gamma%1.3lf.txt", problem.m_mu, problem.m_C, problem.m_gamma);
  std::string grap_preamble = string_format("Slices of H and V for mu=%1.3lf C=%1.3lf gamma=%1.3lf", problem.m_mu, problem.m_C, problem.m_gamma);

  FILE *graph_file = fopen(std::string(path_to_graphs + grap_filename).c_str(), "w");

  //Print preamble
  fprintf(graph_file, "%s\n", grap_preamble.c_str());

  //Print x-axis to file
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", i * (problem.m_X / problem.m_M0));


  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_h_n4()[i]);

  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_v_n4()[i]);


  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_h_n2()[i]);

  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_v_n2()[i]);

  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_h_3n4()[i]);

  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_v_3n4()[i]);


  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_h_n()[i]);

  fprintf(graph_file, "\n");
  for (int i = 0; i < problem.m_M0; i++)
    fprintf(graph_file, "%lf ", solvers[0].get_v_n()[i]);

  fclose(graph_file);

  return 0;
}
