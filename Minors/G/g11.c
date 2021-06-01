#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[10024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	int counter = 0;
	char *word_pointer = strtok (str, " ");
	while (word_pointer)
	{
		counter += (word_pointer[strlen (word_pointer) - 1] == 'a');
		word_pointer = strtok (NULL, " ");
	}

	fprintf(fout, "%d\n", counter);

	fclose (fin);
	fclose (fout);
	return 0;
}