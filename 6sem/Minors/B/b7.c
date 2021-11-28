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

	for (int i = 0; i < 10; i++)
		if (digits[i] > 1)
		{
			printf("YES\n");
			return 0;
		}

	printf("NO\n");
	return 0;
}