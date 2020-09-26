#ifndef STRING__H
#define STRING__H

#include "constants.h"

int read (const char *file_name, char** matrix, int m_matrix_size,
          int n_matrix_size, char* space_string);
void print (char **matrix, int m_matrix_size, int n_matrix_size);
void matrix_sorting (char **matrix, int m_matrix_size, int n_matrix_size);
void free_ (char **matrix, int m_matrix_size, int n_matrix_size);

void swap_lines (char **matrix, int n_matrix_size, int i, int j);
int matrix_redbuilding (char **matrix, int m_matrix_size,
                        int n_matrix_size, int i);
int cmp_lines (char **matrix, int n_matrix_size, int i, int j);
int cmp_line_with_element (char **matrix, int n_matrix_size, int i, char *j);
int  max_of_line (char **matrix, int n_matrix_size, int i);
void quick_sort (char **matrix, int m_matrix_size, int n_matrix_size);

#endif //STRING__H
