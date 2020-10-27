#include "hash.h"

int main(int argc, char *argv[])
{

    if(argc != 4)
    {
	printf("Error: Incorrect console argumetns!\nUsage: %s filename.txt\n", argv[0]);
	return -1;
    }

    char * inFileName = argv[1];
    FILE* inFile = nullptr;
    if((inFile = fopen(inFileName, "r")) == nullptr)
    {
	printf("Error: cannot open input file!\n");
	fclose(inFile);
	return -1;
    }

    char * ins = argv[2];
    char * del = argv[3];

    int mod = 10;
    Hash nameSearch (mod);
    nameSearch.read(inFile);

    nameSearch.print();

    printf("\n\n");

    nameSearch.insert(ins, 0, 666);
    nameSearch.print();

    printf("\n\n");

    nameSearch.deleteValue(del, 22, 222);
    nameSearch.print();

    fclose(inFile);
    return 0;
}

