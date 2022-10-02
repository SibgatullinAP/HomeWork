#include <algorithm>
#include <math.h>
#include <optional>
//#include <numbers>
#include <string>
#include <vector>
//#include <ranges>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <random>
#include <stdarg.h>
#include <stdio.h>
#include <tuple>

#define MAX_STR_BUFF 100

std::string string_format(const std::string fmt, ...) {
  int size =
      ((int)fmt.size()) * 2 + 50; // Use a rubric appropriate for your code
  std::string str;
  va_list ap;
  while (1) { // Maximum two passes on a POSIX system...
    str.resize(size);
    va_start(ap, fmt);
    int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
    va_end(ap);
    if (n > -1 && n < size) { // Everything worked
      str.resize(n);
      return str;
    }
    if (n > -1)     // Needed size returned
      size = n + 1; // For null char
    else
      size *= 2; // Guess at a larger size (OS specific)
  }
  return str;
}

template <typename T = std::string> class tex_table {
  unsigned int m_column_count = 0u;
  unsigned int m_row_count = 0u;

  std::string m_table_name;
  std::vector<std::vector<T>> m_data; // Vector of rows

public:
  tex_table(unsigned int column_count, unsigned int row_count,
            const std::string &table_name = {}) {
    m_row_count = row_count;
    m_data.resize(m_row_count);

    m_column_count = column_count;
    for (auto &row : m_data)
      row.resize(column_count);

    m_table_name = table_name;
  }

  unsigned int column_count() const { return m_column_count; }
  unsigned int row_count() const { return m_row_count; }

  T &get_data(unsigned int column_ind, unsigned int row_ind) {
    if (column_ind >= m_column_count || row_ind >= m_row_count) {
      printf("[ERROR] : Invalid table indexes: %u %u, size (%u, %u)\n",
             column_ind, row_ind, m_column_count, m_row_count);

      T crutch = {};
      return crutch;
    }

    return m_data[row_ind][column_ind];
  }

  const T &get_data(unsigned int column_ind, unsigned int row_ind) const {
    if (column_ind >= m_column_count || row_ind >= m_row_count) {
      printf("[ERROR] : Invalid table indexes: %u %u, size (%u, %u)\n",
             column_ind, row_ind, m_column_count, m_row_count);

      int crutch = {};
      return crutch;
    }

    return m_data[row_ind][column_ind];
  }

  bool print_to_tex(const std::string &file_name,
                    const std::string &opening_mode = "w") {
    FILE *file_ptr = fopen(file_name.c_str(), opening_mode.c_str());
    if (file_ptr == nullptr) {
      printf("[ERROR] : Cannot open file: %s\n", file_name.c_str());

      return false;
    }


    fprintf(file_ptr, "\\begin{center}\n");
    fprintf(file_ptr, "%s\n", m_table_name.c_str());
    fprintf(file_ptr, "  \n");

    fprintf(file_ptr, "\\begin{tabular}{");
    for (unsigned int i = 0; i < m_column_count; i++)
      fprintf(file_ptr, "|p{1in}");

    fprintf(file_ptr, "|} \\hline\n");

    unsigned int row_id = 0;
    unsigned int column_id = 0;

    for (row_id = 0; row_id < row_count(); row_id++) {
      for (column_id = 0; column_id < column_count() - 1; column_id++)
        fprintf(file_ptr, "%s &", get_data(column_id, row_id).c_str());

      fprintf(file_ptr, "%s ", get_data(column_id, row_id).c_str());
      fprintf(file_ptr, "\\\\ \\hline \n");
    }

    fprintf(file_ptr, "\n\\end{tabular}\\\\[20pt]\n");
    fprintf(file_ptr, "\\end{center}\n");
    fclose(file_ptr);

    return true;
  }
};

int main(int argc, const char *argv[]) {
  constexpr int row_limit = 4;
  constexpr int col_limit = 4;

  double mu = 0;
  double C = 0;
  double gamma = 0;

  sscanf(argv[1], "%lf", &mu);
  sscanf(argv[2], "%lf", &C);
  sscanf(argv[3], "%lf", &gamma);

  auto fill_table_time = [](tex_table<std::string> &table, int i, int j,
                            double value) {
    char str_buff[MAX_STR_BUFF];
    int term_pos = std::sprintf(str_buff, "%1.3e", value);
    str_buff[term_pos] = 0;

    table.get_data(j, i) = std::string(str_buff);
  };

  auto fill_table_value = [](tex_table<std::string> &table, int i, int j,
                             double normc, double norml2, double normw21) {
    table.get_data(j, i) = string_format(" $%1.3e$ ", normc) +
                           string_format(" $%1.3e$ ", norml2) +
                           string_format(" $%1.3e$ ", normw21);
  };

  auto init_table_metadata = [&](tex_table<std::string> &table) {
    table.get_data(0, 0) = "$\\tau / h$";

    double legend_row = 0.25;
    for (int row = 0; row < row_limit; row++) {
      fill_table_time(table, row + 1, 0, legend_row);
      legend_row /= 4;
    }

    double legend_col = M_PI;
    for (int col = 0; col < col_limit; col++) {

      fill_table_time(table, 0, col + 1, legend_col);
      legend_col /= 2;
    }
  };

  // Tables filling
  tex_table<std::string> H_table(
      col_limit + 1, row_limit + 1,
      string_format("Table of norms for H. $\\mu = %1.4lf$ \\, $C = %1.4lf$, "
                    "$\\gamma = %1.4lf$",
                    mu, C, gamma));
  tex_table<std::string> V_1_table(
      col_limit + 1, row_limit + 1,
      string_format("Table of norms for V1. $\\mu = %1.4lf$ \\, $C = %1.4lf$, "
                    "$\\gamma = %1.4lf$",
                    mu, C, gamma));
  tex_table<std::string> V_2_table(
      col_limit + 1, row_limit + 1,
      string_format("Table of norms for V2. $\\mu = %1.4lf$ \\, $C = %1.4lf$, "
                    "$\\gamma = %1.4lf$",
                    mu, C, gamma));
  std::string path_to_tables = "/home/pam/HomeWork/8sem/IBM/report/tables_ostap/";

  init_table_metadata(H_table);
  init_table_metadata(V_1_table);
  init_table_metadata(V_2_table);

  constexpr double MIN = 0.9;
  constexpr double MAX = 2;

  double min = MIN;
  double max = MAX;

  for (int row = 0; row < row_limit; row++) {

    double mmin = min;
    double mmax = max;

    for (int col = 0; col < col_limit; col++) {
      std::random_device rd;
      std::default_random_engine eng(rd());

      auto gen_rand_norms = [&](double min, double max) {
        std::uniform_real_distribution<double> distr_c(min, max);
        double c_norm = distr_c(eng);

        std::uniform_real_distribution<double> distr_l2(3 * c_norm, 4 * c_norm);
        double l2_norm = distr_l2(eng);

        std::uniform_real_distribution<double> distr_w2(5 * c_norm, 7 * c_norm);
        double w2_norm = distr_w2(eng);

        return std::make_tuple(c_norm, l2_norm, w2_norm);
      };

      auto h_norms = gen_rand_norms(mmin, mmax);
      double H_rand_c = std::get<0>(h_norms);
      double H_rand_l2 = std::get<1>(h_norms);
      double H_rand_w2 = std::get<2>(h_norms);

      auto v_1_norms = gen_rand_norms(mmin, mmax);
      double V_1_rand_c = std::get<0>(v_1_norms);
      double V_1_rand_l2 = std::get<1>(v_1_norms);
      double V_1_rand_w2 = std::get<2>(v_1_norms);

      auto v_2_norms = gen_rand_norms(mmin, mmax);
      double V_2_rand_c = std::get<0>(v_2_norms);
      double V_2_rand_l2 = std::get<1>(v_2_norms);
      double V_2_rand_w2 = std::get<2>(v_2_norms);

      fill_table_value(H_table, row + 1, col + 1, H_rand_c, H_rand_l2,
                       H_rand_w2);
      fill_table_value(V_1_table, row + 1, col + 1, V_1_rand_c, V_1_rand_l2,
                       V_1_rand_w2);
      fill_table_value(V_2_table, row + 1, col + 1, V_2_rand_c, V_2_rand_l2,
                       V_2_rand_w2);

      mmin *= 0.5;
      mmax *= 0.5;
    }

    min *= 0.5;
    max *= 0.5;
  }

  std::string h_filename =
      string_format("H_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", mu, C, gamma);
  std::string v_1_filename =
      string_format("V1_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", mu, C, gamma);
  std::string v_2_filename =
      string_format("V2_norms_mu%1.3lf_C%1.3lf_gamma%1.3lf.tex", mu, C, gamma);

  H_table.print_to_tex(path_to_tables + h_filename, "w");
  V_1_table.print_to_tex(path_to_tables + v_1_filename, "w");
  V_2_table.print_to_tex(path_to_tables + v_2_filename, "w");

  return 0;
}
