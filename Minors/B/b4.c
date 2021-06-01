#include <stdio.h>

int main (void)
{
	int number;
	scanf ("%d", &number);

	int digits = 0;

	while (number)
	{
		digits++;
		number /= 10;
	}

	if (digits == 3)
		printf("YES\n");
	else
		printf("NO\n");


	return 0;
}