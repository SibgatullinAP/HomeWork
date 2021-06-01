#include <stdio.h>
#include <string.h>

void to_capital (char *str, char *ans_str)
{
	int shift = 'a' - 'A';
	int i = 0;
	while (str[i] && str[i] != '.')
	{

		if ('a' <= str[i] && str[i] <= 'z')
		{
			ans_str[i] = str[i] - shift;
		}
		else
			ans_str[i] = str[i];

		i++;
	}
	ans_str[i] = 0;

}

int main (void)
{
	char str[1000];
	char ans_str[1000];
	fgets (str, 1000, stdin);

	to_capital (str, ans_str);

	printf("%s\n", ans_str);
	return 0;
}