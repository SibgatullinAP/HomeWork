#include "hash.h"

Hash::Hash(int key)
{
    Key = key;
    if(Key != 0)
    {
	Table = new HashNode [Key];
    }
}

Hash::~Hash()
{
    delete [] Table;
    Key = 0;
}

int Hash::read(FILE *inFile)
{
    char buff[BUFF_LEN];
    char name[BUFF_LEN];
    int phone = 0, group = 0;

    while (fgets(buff, BUFF_LEN, inFile))
    {
	if(sscanf(buff,"%s %d %d", name, &phone, &group) != 3)
	{
	    return ERROR_CANNOT_READ_INPUT_FILE;
	}
	insert(name, phone, group);
    }
    return 0;
}

void Hash::print()
{
    for(int i = 0; i < Key && i < MAX_PRINT_HASH; i++)
    {
	printf("HashTable[%d] : \n", i);
	Table[i].print(Table[i].getRoot());
    }
}

void Hash::insert(char *Name, int Phone, int Group)
{
    int sum = 0, phoneBuff = Phone;
    while(phoneBuff != 0)
    {
	sum += phoneBuff % 10;
	phoneBuff /= 10;
    }
    Table[(int)(sum % Key)].insert(Name, Phone, Group);
    Table[(int)(sum % Key)].HashValue = sum;
}

void Hash::deleteValue(char *Name, int Phone, int Group)
{
    int sum = 0, phoneBuff = Phone;
    while(phoneBuff != 0)
    {
	sum += phoneBuff % 10;
	phoneBuff /= 10;
    }

    Table[(int)(sum % Key)].deleteValue(Name, Phone, Group);
}
