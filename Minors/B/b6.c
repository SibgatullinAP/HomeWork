#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int prev_digit = number % 10;
	number /= 10;

	int cur_digit;

	while (number)
	{
		cur_digit = number % 10;
		number /= 10;

		if (prev_digit == cur_digit)
			return printf("YES\n"), 0;

		prev_digit = cur_digit;
	}

	printf("NO\n");

	return 0;
}