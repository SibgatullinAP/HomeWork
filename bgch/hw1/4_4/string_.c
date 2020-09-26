#include "string_.h"

int read (const char *file_name, char** matrix, int m_matrix_size,
          int n_matrix_size, char* space_string)
{
	FILE *file = fopen (file_name, "r");
	if (file == NULL)
		return CANNOT_OPEN_FILE;

	for (int i = 0; i < m_matrix_size; i++)
		{
			char buff[STRING_BUFF] = {0};
			if (fgets (buff, STRING_BUFF, file) == NULL)
				{
					fclose (file);
					return CANNOT_READ_FILE;
				}
			char *saveptr;
			char *word = strtok_r (buff, space_string, &saveptr);
			for (int j = 0; j < n_matrix_size; j++)
				{
					if (word != NULL)
						{
							matrix[i * n_matrix_size + j]
							    = (char*) malloc ((strlen (word) + 1) * sizeof (char));
							if (matrix[i * n_matrix_size + j] == NULL)
								{
									fclose (file);
									return NOT_ENOUGH_MEMMORY;
								}

							if (word[strlen (word) - 1] == '\n')
								word[strlen (word) - 1] = 0;
							else
								word[strlen (word)] = 0;

							strcpy (matrix[i * n_matrix_size + j], word);
						}
					else
						{
							matrix[i * n_matrix_size + j]
							    = (char*) malloc (sizeof (char));
							if (matrix[i * n_matrix_size + j] == NULL)
								{
									fclose (file);
									return NOT_ENOUGH_MEMMORY;
								}
							matrix[i * n_matrix_size + j][0] = 0;
						}
					word = strtok_r (NULL, space_string, &saveptr);
				}
		}

	fclose (file);
	return 0;
}

void print (char **matrix, int m_matrix_size, int n_matrix_size)
{
	int m_print_limit = ((m_matrix_size > M_MAX_PRINT)
	                     ? M_MAX_PRINT : m_matrix_size);
	int n_print_limit = ((n_matrix_size > N_MAX_PRINT)
	                     ? N_MAX_PRINT : n_matrix_size);
	for (int i = 0; i < m_print_limit; i++)
		{
			//printf ("\t");
			for (int j = 0; j < n_print_limit; j++)
				{
					//printf("%lu", strlen(matrix[i * n_matrix_size + j]));
					printf ("|%20s|", matrix[i * n_matrix_size + j]);
				}
			printf ("\n");
		}
}

void free_ (char **matrix, int m_matrix_size, int n_matrix_size)
{
	for (int i =0; i < m_matrix_size * n_matrix_size; i++)
		{
			if (matrix[i] != NULL)
				free (matrix[i]);
		}

	if (matrix != NULL)
		free (matrix);
}

void quick_sort (char **matrix, int m_matrix_size, int n_matrix_size)
{
	int position;
	int base_element;

	if (m_matrix_size < 2)
		return ;

	while (m_matrix_size > 2)
		{
			base_element = m_matrix_size / 2;
			position = matrix_redbuilding (matrix, m_matrix_size,
			                               n_matrix_size, base_element);
			if (position < m_matrix_size - position)
				{
					quick_sort (matrix, position, n_matrix_size);
					matrix += position * n_matrix_size;
					m_matrix_size -= position;
				}
			else
				{
					quick_sort (matrix + position * n_matrix_size,
					            m_matrix_size - position, n_matrix_size);
					m_matrix_size = position;
				}
		}
	if (m_matrix_size == 2
	    && (cmp_lines(matrix, n_matrix_size,
	                  m_matrix_size - 2, m_matrix_size - 1) < 0))

		swap_lines (matrix, n_matrix_size, m_matrix_size - 2, m_matrix_size - 1);
	return ;
}


int matrix_redbuilding (char **matrix, int m_matrix_size,
                        int n_matrix_size, int i)
{
	int left = 0;
	int right = m_matrix_size - 1;
	char *i_max = matrix[i * n_matrix_size
	              + max_of_line(matrix, n_matrix_size, i)];
	while (left <= right)
		{
			while (cmp_line_with_element(matrix, n_matrix_size, left, i_max) > 0)
				left++;
			while (cmp_line_with_element(matrix, n_matrix_size, right, i_max) < 0)
				right--;
			if (left <= right)
				{
					swap_lines (matrix, n_matrix_size, left, right);
					right--;
					left++;
				}
		}
	return left;
}

void swap_lines (char **matrix, int n_matrix_size, int i, int j)
{
	char *temp;
	int i_p = i * n_matrix_size;
	int j_p = j * n_matrix_size;
	for (int k = 0; k < n_matrix_size; k++)
		{
			temp = matrix[i_p + k];
			matrix[i_p + k] = matrix[j_p + k];
			matrix[j_p + k] = temp;
		}
}

int  max_of_line (char **matrix, int n_matrix_size, int i)
{
	int max_position = 0;
	int i_p = i * n_matrix_size;
	for (int j = 0; j < n_matrix_size; j++)
		{
			if (strcmp(matrix[i_p + j], matrix[i_p + max_position]) > 0)
				max_position = j;
		}
	return max_position;
}

int cmp_lines (char **matrix, int n_matrix_size, int i, int j)
{
	char* i_max = matrix[i * n_matrix_size];
	char* j_max = matrix[j * n_matrix_size];
	int i_p = i * n_matrix_size;
	int j_p = j * n_matrix_size;
	for (int k = 0; k < n_matrix_size; k++)
		{
			if (strcmp(matrix[i_p + k], i_max) > 0)
				i_max = matrix[i_p + k];

			if (strcmp(matrix[j_p + k], j_max) > 0)
				j_max = matrix[j_p + k];
		}

	return strcmp (i_max, j_max);
}

int cmp_line_with_element (char **matrix, int n_matrix_size, int i, char * j)
{
	char* i_max = matrix[i * n_matrix_size];
	int i_p = i * n_matrix_size;
	for (int k = 0; k < n_matrix_size; k++)
		{
			if (strcmp(matrix[i_p + k], i_max) > 0)
				i_max = matrix[i_p + k];
		}
	return strcmp (i_max, j);
}


