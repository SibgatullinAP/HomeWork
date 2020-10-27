#include <stdio.h>
#include <time.h>
#include "database.h"
#include "errors.h"
#include "record.h"

int main(int argc, char *argv[]){
	double t;
	int size;

	if(!(argc == 2 || argc == 3) || (size = atoi(argv[1])) <= 0){
		printf("Usage: %s size [file]\n", argv[0]);
		return 1;
	}

	database base(size);

	if(argc == 3){
		const char *name = argv[2];

		FILE *fp = fopen(name, "r");
		if(!fp){
			printf("Error: can not open \"%s\"\n", name);
			return 2;
		}

		t = clock();
		int ret = base.read(fp);
		if(ret < 0){
			printf("Error: ");
			switch(ret){
				case ERR_READ: printf("can not read \"%s\"\n", name); break;
				case ERR_MEMORY: printf("not enough memory\n"); break;
				case ERR_OVERLAP: printf("equal elements in \"%s\"\n", name); break;
				default: printf("read unknown error\n");
			}
			fclose(fp);
			return 3;
		}
		t = clock() - t;
		
		printf("Reading time: %.2lf\n", t / CLOCKS_PER_SEC);
		fclose(fp);
	}

	t = clock();
	base.task();
	t = clock() - t;

	printf("Execution time: %.2lf\n", t / CLOCKS_PER_SEC);
	return 0;
}
