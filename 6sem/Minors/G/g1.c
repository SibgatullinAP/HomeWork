#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[2000];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);
	fprintf(fout, "%s, %s, %s %lu", str, str, str, strlen (str));

	fclose (fin);
	fclose (fout);
	return 0;
}