#include "tree.h"

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

    Tree nameSearch;
    nameSearch.read(inFile);

    nameSearch.print(nameSearch.getRoot());

    printf("\n\n");

    nameSearch.insert(ins, 66, 666);
    nameSearch.print(nameSearch.getRoot());

    printf("\n\n");

    nameSearch.deleteValue(del, 4124349, 251);
    nameSearch.print(nameSearch.getRoot());

    fclose(inFile);
    return 0;
}

