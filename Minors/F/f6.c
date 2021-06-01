#include <stdio.h>

int is_similar (int *arr)
{
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (j != i && arr[i] == arr[j])
				return 1;
		}
	}
	return 0;
}

int main (void)
{
	int arr[100] = {0};
	for (int i = 0; i < 100; ++i)
		scanf ("%d", arr + i);

	if (is_similar (arr))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}