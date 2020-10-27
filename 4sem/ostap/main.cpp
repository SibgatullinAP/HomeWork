#include "solve.h"

int main (int argc, char* argv[])
{
	int res = 0, M = 100;
	double t, T;
	const char *name_a = nullptr;
	if (!((argc == 1) || (argc == 2) || (argc == 3)))
	{
		printf("\nUsage %s input.txt (file with records) m (hash's module, must be > 0) \n\n", argv[0]);
		return -1;
	}


	if (argc == 3)
	{
		name_a = argv[1];
		if (!(M = atoi(argv[2])))
		{
			printf("\nM must be positive integer\n\n");
			return -1;
		}
	}
	else
	{
		if (argc == 2)
		{
			name_a = argv[1];
			FILE *fp;
			if (!(fp = fopen(name_a, "r")))
			{
				if (!(M = atoi(argv[1])))
				{
					printf("\nM must be positive integer\n\n");
					return -1;
				}
				name_a = nullptr;
			}
			else
				fclose(fp);
		}
	}

	//printf("M = %d\n", M);

	t = clock();
	res = solve(name_a, M, T);
	T = (clock() - T)/CLOCKS_PER_SEC;
	t = (clock() - t)/CLOCKS_PER_SEC;

	if (res < 0)
	{
		switch (res) {
		case CANNOT_OPEN_FILE_A:
			printf("\nCannot open file %s\n\n", name_a);
			break;
		case READING_ERR:
			printf("\nProblems with reading\n\n");
			break;
		case FGETS_ERR:
			printf("\nProblems with reading command from stdin with fgets\n\n");
			break;
		default:
			printf("\nWOW, It's amaizing\n UNKNONW error = %d!!!\\\n\n", res);
		}
		return -1;
	}

	printf("\x1b[31mTIME\x1b[0m deliting        = %f\n", T);
	printf("\x1b[31mTIME\x1b[0m work            = %f\n\n", t);

	return 0;
}
