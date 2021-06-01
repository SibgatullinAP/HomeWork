#include <stdio.h>

int big_count (char *str, int *ans)
{
	if (*str == 0 || *str == '.')
		return *ans;

	if ((*str >= 'A') && (*str <= 'Z'))
		(*ans)++;

	big_count (str + 1, ans);
}

int main (void)
{
	char str[1024];
	scanf("%[^\n]", str);

	int ans = 0;

	printf("%d\n", big_count (str, &ans));
	return 0;
}