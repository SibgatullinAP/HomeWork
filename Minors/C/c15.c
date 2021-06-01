#include <stdio.h>

int is_incr (int number)
{
	int digits[10] = {0};

	int prev_digit = number % 10;
	number /= 10;

	while (number)
	{
		if ((number % 10) >= prev_digit)
			return 0;

		prev_digit = number % 10;
		number /= 10;
	}

	return 1;
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	if (is_incr (number))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}