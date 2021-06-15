#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int digits[10] = {0};

	while (number)
	{
		digits[number % 10] += 1;
		number /= 10;
	}

	if (digits[9] == 1)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}