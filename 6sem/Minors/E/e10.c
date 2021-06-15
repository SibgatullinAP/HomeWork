#include <stdio.h>

int main (void)
{
	int arr[12] = {0};

	for (int i = 0; i < 12; i++)
		scanf ("%d", arr + i);

	int tmp_1 = arr[11];
	int tmp_2 = arr[10];
	int tmp_3 = arr[9];
	int tmp_4 = arr[8];
	for (int i = 11; i > 3; i--)
	{
		arr[i] = arr[i - 4];
	}
	arr[0] = tmp_4;
	arr[1] = tmp_3;
	arr[2] = tmp_2;
	arr[3] = tmp_1;

	for (int i = 0; i < 12; i++)
		printf ("%d ", arr[i]);

	printf ("\n");
	return 0;
}	