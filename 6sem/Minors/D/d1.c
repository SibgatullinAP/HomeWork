#include <stdio.h>

void print_digit (int number)
{
	if (number == 0)
	{
		printf("\n");
		return;
	}
	
	print_digit (number - 1);

	printf ("%d ", number);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	print_digit (number);
	return 0;
}