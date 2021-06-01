#include <stdio.h>
#include <string.h>

int main (void)
{
	char str_1[1024];
	char str_2[1024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	unsigned int alph_1[256] = {0};
	unsigned int alph_2[256] = {0};

	fscanf (fin, "%s %s", str_1, str_2);

	for (int i = 0; str_1[i]; ++i)
		alph_1[(unsigned int)str_1[i]] += 1;

	for (int i = 0; str_2[i]; ++i)
		alph_2[(unsigned int)str_2[i]] += 1;

	for (int i = 0; i < 256; ++i)
	{
		if (alph_1[i] == 1 && alph_2[i] == 1)
			fprintf(fout, "%c ", i);
	}

	fclose (fin);
	fclose (fout);
	return 0;
}