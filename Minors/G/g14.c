#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[10024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	char *second_name = strtok (str, " ");
	char *first_name = strtok (NULL, " ");
	char *patronymic = strtok (NULL, " ");

	fprintf(fout, "Hello, %s %s!\n", first_name, second_name);

	fclose (fin);
	fclose (fout);
	return 0;
}