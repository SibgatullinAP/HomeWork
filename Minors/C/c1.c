#include <stdio.h>

int abs (int number)
{
	return (number > 0 ? number : (-1) * number);
}

int main (void)
{
	int number = 0;
	scanf ("%d", &number);

	printf("%d\n", abs (number));

	return 0;
}