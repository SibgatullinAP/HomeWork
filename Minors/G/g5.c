#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[1024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	for (int i = 0; str[i]; ++i)
	{
		if (str[i] == 'a')
			str[i] = 'b';
		else if (str[i] == 'b')
			str[i] = 'a';
		else if (str[i] == 'A')
			str[i] = 'B';
		else if (str[i] == 'B')
			str[i] = 'A';
		else
			str[i] = str[i];
	}

	fprintf(fout, "%s\n", str);

	fclose (fin);
	fclose (fout);
	return 0;
}