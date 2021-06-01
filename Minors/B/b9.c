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

	for (int i = 1; i < 10; i += 2)
		if (digits[i] > 0)
		{
			printf("NO\n");
			return 0;
		}

	printf("YES\n");
	return 0;
}