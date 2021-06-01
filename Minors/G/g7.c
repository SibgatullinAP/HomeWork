#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[10024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	unsigned int alphabet[256] = {0};

	for (int i = 0; str[i]; ++i)
		alphabet[str[i]] += 1;

	int small = 0;
	int capital = 0;

	for (int i = 'a'; i <= 'z'; ++i)
		small += alphabet[i];

	for (int i = 'A'; i <= 'Z'; ++i)
		capital += alphabet[i];

	fprintf(fout, "%d %d\n", small, capital);

	fclose (fin);
	fclose (fout);
	return 0;
}