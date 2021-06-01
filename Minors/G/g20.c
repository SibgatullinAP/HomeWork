#include <stdio.h>
#include <string.h>

int is_palindrom (char *str)
{

	unsigned int alphabet[256] = {0};
	for (int i = 0; i < str[i]; ++i)
		alphabet[str[i]] += 1;

	int is_all_even = 0;
	for (int i = 'a'; i <= 'z'; ++i)
	{
		if ((alphabet[i] % 2) != 0)
		{
			is_all_even = 0;
			break;
		}
		
		is_all_even = 1;
	}

	if (is_all_even)
		return 1;

	int flag = 0;
	for (int i = 'a'; i <= 'z'; ++i)
	{
		if ((alphabet[i] % 2) != 0 && flag)
			return 0;

		if ((alphabet[i] % 2) != 0)
			flag = 1;
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
		fprintf (stdout, "%s\n", "YES");
	else
		fprintf (stdout, "%s\n", "NO");

	fclose (fin);
	fclose (fout);
	return 0;
}