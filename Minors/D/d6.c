#include <stdio.h>

void reverse_string(char *str)
{
	if (*str == 0 || *str == '.')
	{
		
		return;
	}

	reverse_string (str + 1);
	printf ("%c", *str);
}

int main (void)
{
	char str[1024];
	scanf ("%[^\n]", str);

	reverse_string (str);
	printf("\n");
	return 0;
}