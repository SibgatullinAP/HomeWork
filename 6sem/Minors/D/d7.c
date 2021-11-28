#include <stdio.h>

void print_digit_revert (int number)
{
	if (number == 0)
	{
		printf("\n");
		return;
	}

	printf ("%d ", number);
	print_digit_revert (number - 1);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	print_digit_revert (number);
	return 0;
}