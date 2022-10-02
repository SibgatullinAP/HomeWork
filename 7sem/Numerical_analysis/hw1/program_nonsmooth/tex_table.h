#ifndef TEX_TABLE_H
#define TEX_TABLE_H

#include "common.h"

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

//    if (opening_mode == "w") {
//      fprintf(file_ptr, "\\documentstyle{article}\n");
//      fprintf(file_ptr, "\\begin{document}\n");
//    }

    fprintf(file_ptr, "\\begin{center}\n");
    fprintf(file_ptr, "%s\n", m_table_name.c_str());
//    fprintf(file_ptr, "\\\\[2.0ex]  \n");
    fprintf(file_ptr, "  \n");

    fprintf(file_ptr, "\\begin{tabular}{");
    for (int i = 0; i < m_column_count; i++)
      fprintf(file_ptr, "|p{0.8in}");

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

//    if (opening_mode == "w") {
//      fprintf(file_ptr, "\\end{document}\n");
//    }
    fclose(file_ptr);

    return true;
  }
};

#endif // TEX_TABLE_H
