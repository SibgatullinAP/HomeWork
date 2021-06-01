#include <stdio.h>

int main (void)
{
	int x_1 = 0;
	int y_1 = 0;
	int x_2 = 0;
	int y_2 = 0;

	if (scanf ("%d %d %d %d", &x_1, &y_1, &x_2, &y_2) != 4)
	{
		printf ("Incorrect input values!\n");
		return -1;
	}

	float k = (y_1 - y_2) / (float) (x_1 - x_2);
	float b = (y_2 * x_1 - y_1 * x_2) / (float) (x_1 - x_2);

	printf ("%.2f %.2f\n", k, b);
	return 0;
}