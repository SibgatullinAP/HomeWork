#include <stdio.h>

int is_digit (char symb)
{
	return '0' <= symb && symb <= '9';
}

int main (void)
{
	char str[1024];
	fgets (str, 1024, stdin);

	int counter = 0;
	for (int i = 0; str[i]; i++)
		counter += is_digit (str[i]);

	printf("%d\n", counter);
	return 0;
}