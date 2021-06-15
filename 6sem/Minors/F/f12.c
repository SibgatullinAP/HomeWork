#include <stdio.h>

void swap_minmax (int a[])
{
	int i = 0;
	int min = a[0];
	int max = a[0];
	int ind_max = 0;
	int ind_min = 0;

	for (i = 0; i < 10; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
			ind_max = i;
		}

		if(a[i] < min)
		{
			min = a[i];
			ind_min = i;
		}
	}

	int tmp = a[ind_min];
	a[ind_min] = a[ind_max];
	a[ind_max] = tmp;
}

int main (void)
{
	int arr[10];
	for (int i = 0; i < 10; ++i)
		scanf ("%d", arr + i);

	swap_minmax (arr);

	for (int i = 0; i < 10; ++i)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}