#include <stdio.h>

int is_correct_brackets (const char *str)
{
	int scope_counter = 0;

	int i = 0;
	while (str[i] && str[i] != '.')
	{
		if (str[i] == '(')
		{
			scope_counter++;
			i++;
			continue;
		}

		if (scope_counter > 0 && (str[i] == ')'))
			scope_counter--;

		i++;
	}

	return !scope_counter;
}

int main (void)
{
	char str[2000];
	fgets (str, 2000, stdin);

	int is_correct = is_correct_brackets (str);

	if (is_correct)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}