#include <stdio.h>

int main (void)
{
	int arr[10] = {0};

	for (int i = 0; i < 10; i++)
		scanf ("%d", arr + i);

	int min = arr[0];
	int max = arr[0];
	int ind_min = 0;
	int ind_max = 0;
	for (int i = 0; i < 10; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			ind_max = i;
		}

		if (arr[i] < min)
		{
			min = arr[i];
			ind_min = i;
		}
	}

	ind_min ++;
	ind_max ++;

	printf("%d %d %d %d\n", ind_max, max, ind_min, min);
	return 0;
}	