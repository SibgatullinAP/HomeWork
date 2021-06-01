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

	int is_triangle = (a + b > c) && (a + c > b) && (b + c > a);
	if (is_triangle)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}