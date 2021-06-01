#include <stdio.h>
#include <string.h>

int is_palindrom (char *str)
{

	int len = strlen(str);
	printf("%d\n", len);
	for (int i = 0; i < len / 2; ++i)
	{
		if (str[i] != str[len - 1 - i])
			return 0;
	}

	return 1;
}

int main (void)
{
	char str[1024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	fscanf (fin, "%[^\n]", str);

	if (is_palindrom (str))
		fprintf (fout, "%s\n", "YES");
	else
		fprintf (fout, "%s\n", "NO");

	fclose (fin);
	fclose (fout);
	return 0;
}