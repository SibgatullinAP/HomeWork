#include <stdio.h>

int main (void)
{
	int a = 0;
	int b = 0;
	int c = 0;

	if (scanf ("%d %d %d", &a, &b, &c) != 3)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	int is_increasing = (a < b && b < c);

	if (is_increasing)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}