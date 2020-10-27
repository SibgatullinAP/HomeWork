#include "tree.h"

int main(int argc, char *argv[])
{

    if(argc != 3)
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

    char * del = argv[2];

    Tree nameSearch;
    nameSearch.read(inFile);

    nameSearch.print(nameSearch.getRoot());

    nameSearch.deleteValue(del, 22, 222);
    nameSearch.print(nameSearch.getRoot());

    fclose(inFile);
    return 0;
}

