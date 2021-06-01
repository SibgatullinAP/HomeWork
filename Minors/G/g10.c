#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[10024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	int max_len = 0;
	char *max_word_pointer = NULL;

	char *word_pointer = strtok (str, " ");
	while (word_pointer)
	{	
		int len = strlen (word_pointer);
		if (len > max_len)
		{
			max_len = len;
			max_word_pointer = word_pointer;
		}

		word_pointer = strtok (NULL, " ");
	}

	fprintf(fout, "%s\n", max_word_pointer);

	fclose (fin);
	fclose (fout);
	return 0;
}