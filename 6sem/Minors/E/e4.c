#include <stdio.h>

int main (void)
{
	int arr[10] = {0};

	for (int i = 0; i < 10; i++)
		scanf ("%d", arr + i);

	int max = arr[0];
	int prev_max = arr[0];

	int ind_max = 0;
	for (int i = 0; i < 10; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			ind_max = i;
		}
	}

	for (int i = 0; i < 10; i++)
		prev_max = arr[i] > prev_max && ind_max != i ? arr[i] : prev_max;

	printf("%d\n", max + prev_max);
	return 0;
}	