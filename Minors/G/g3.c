#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[1024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	int count = 0;
	fscanf (fin, "%[^\n]", str);
	unsigned int last_symb = str[strlen(str) - 1];
	int last_symb_index = strlen(str) - 1;

	for (int i = 0; str[i]; ++i)
	{
		if (str[i] == last_symb && i != last_symb_index)
			fprintf(fout, "%d ", i);
	}

	fclose (fin);
	fclose (fout);
	return 0;
}