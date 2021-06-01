#include <stdio.h>
#include <string.h>

int main (void)
{
	char str[1024];

	FILE *fin = fopen ("input.txt", "r");
	FILE *fout = fopen ("output.txt", "w");

	int count = 0;
	fscanf (fin, "%d", &count);
	int j = 0;

	for (int i = 1, j = 2; i < count; i += 2, j += 2)
	{	
		if (j % 8 == 0)
		{
			str[i] = '0' + 8;	
		}
		else 
		{
			str[i] = '0' + j % 8;
		}

	}
	for (int i = 0, j = 0; i < count; i += 2, j++)
	{
		str[i] = 'A' + j;
	}

	str[count] = '\0';
	fprintf(fout, "%s", str);

	fclose (fin);
	fclose (fout);
	return 0;
}