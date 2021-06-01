#include <stdio.h>

int digit_to_num (char symb)
{
	if (symb == '0')
		return 0;
	else if (symb == '1')
		return 1;
	else if (symb == '2')
		return 2;
	else if (symb == '3')
		return 3;
	else if (symb == '4')
		return 4;
	else if (symb == '5')
		return 5;
	else if (symb == '6')
		return 6;
	else if (symb == '7')
		return 7;
	else if (symb == '8')
		return 8;
	else if (symb == '9')
		return 9;
	else 
		return 0;
}

int main (void)
{
	char str[1024];
	fgets (str, 1024, stdin);

	int counter = 0;
	for (int i = 0; str[i]; i++)
		counter += digit_to_num (str[i]);

	printf("%d\n", counter);
	return 0;
}