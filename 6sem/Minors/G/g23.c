#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *str = argv[1];
	int len = strlen (str);

	char tmp = 0;
	for (int i = 0; i < len / 2; ++i)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}

	printf("%s\n", str);
	return 0;
}