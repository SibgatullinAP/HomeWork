#include <stdio.h>

int pow_ (int base, int exp)
{
	int answer = 1;
	for (int i = 0; i < exp; i++)
		answer *= base;

	return answer;
}

int main (void)
{
	int base, exp;
	scanf ("%d %d", &base, &exp);

	printf("%d\n", pow_ (base, exp));

	return 0;
}