#include "string_.h"

int read (const char *file_name, char **arr, int size)
{
	FILE *file = fopen (file_name, "r");
	if (file == NULL)
		return CANNOT_OPEN_FILE;

	for (int i = 0; i < size; i ++)
		{
			char buff[STRING_BUFF] = {0};
			if (fgets (buff, STRING_BUFF, file) == NULL)
				{
					fclose (file);
					return CANNOT_READ_FILE;
				}
			arr[i] = (char*) malloc ((strlen (buff) + 1) * sizeof (char));
			if (arr[i] == NULL)
				{
					fclose (file);
					return NOT_ENOUGH_MEMMORY;
				}
			strcpy (arr[i], buff);
			arr[i][strlen (arr[i]) - 1] = 0;
		}

	fclose (file);
	return 0;
}

void print (char **arr, int size)
{
	int print_limit = ((size > MAX_PRINT) ? MAX_PRINT : size);
	for (int i = 0; i < print_limit; i++)
		printf ("\t[%d] = %s\n", i, arr[i]);
}

void free_ (char **arr, int size)
{
	for (int i =0; i < size; i++)
		free (arr[i]);

	free (arr);
}

int array_rebuilding (char **arr, int size, int k, char *string)
{
	int shift = 0;
	int entry_counter = 0;
	for (int i = 0; i < size; i++)
		{
			if (strstr (arr[i], string) != NULL)
				entry_counter++;
			else
				{
					if (entry_counter >= k)
						shift += entry_counter;
					entry_counter = 0;
				}

			if (shift != 0)
				{
					free (arr[i - shift]);
					arr[i - shift] = arr[i];
					arr[i] = 0;
				}
		}
	if (entry_counter >= k)
		shift += entry_counter;

	return size - shift;
}
