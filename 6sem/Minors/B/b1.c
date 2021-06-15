#include <stdio.h>

int main (void)
{
	int limit = 0;
	scanf ("%d", &limit);

	for (int i = 1; i <= limit; ++i)
		printf("%d %d %d\n", i, i * i, i * i * i);

	return 0;
}