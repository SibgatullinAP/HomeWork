#include <stdio.h>

void rebuild (int *arr)
{
	int arr_even[20] = {0};

	int j = 0;
	int k = 0;
	for (int i = 0; i < 20; ++i)
	{
		if (arr[i] % 2 == 0)
		{
			arr_even[j] = arr[i];
			j++;
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		if (arr[i] % 2 != 0)
		{
			arr_even[j] = arr[i];
			j++;
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		arr[i] = arr_even[i];
	}

}

int main (void)
{
	int arr[20];

	for (int i = 0; i < 20; ++i)
		scanf ("%d", arr + i);

	rebuild (arr);

	for (int i = 0; i < 20; ++i)
		printf ("%d ", arr[i]);

	printf("\n");
	return 0;
}