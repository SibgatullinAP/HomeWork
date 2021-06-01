#include <stdio.h>

int f_ (int x)
{
	if (x >= -2 && x < 2)
		return x * x;
	else if (x >= 2)
		return x * x + 4 * x + 5;
	else
		return 4;
}

int main (void)
{
	int x = 0;
	int f_x = 0;
	int max_f_x = 0;

	scanf ("%d", &x);
	max_f_x = f_x = f_ (x);

	while (scanf ("%d", &x) == 1 && x)
	{
		f_x = f_ (x);
		max_f_x = (f_x > max_f_x ? f_x : max_f_x);
	}

	printf("%d\n", max_f_x);
	return 0;
}