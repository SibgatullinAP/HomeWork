#include <stdio.h>
#define SIZE 30

int is_array_down (int a[], int size)
{
	for (int i = 1; i < size; ++i)
		if (a[i] >= a[i - 1]) return 0;

	return 1;
}

int main (void)
{
	int size = SIZE;
	int a[SIZE];

	for (int i = 0; i < size; ++i)
		scanf ("%d", a + i);

	if (is_array_down(a, size))
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}