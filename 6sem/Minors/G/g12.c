#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[10024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	char *word_pointer = strtok (str, " ");
	while (word_pointer)
	{
		fprintf(fout, "%s\n", word_pointer);
		word_pointer = strtok (NULL, " ");
	}

	fclose (fin);
	fclose (fout);
	return 0;
}