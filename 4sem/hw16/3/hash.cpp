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

void Hash::print()
{
    for(int i = 0; i < Key && i < MAX_PRINT_HASH; i++)
    {
	printf("HashTable[%d] : \n", i);
	Table[i].print(Table[i].getRoot());
    }
}

void Hash::insert(ListNode * source)
{
    int sum = 0, phoneBuff = source->getPhone();
    while(phoneBuff != 0)
    {
	sum += phoneBuff % 10;
	phoneBuff /= 10;
    }
    Table[(int)(sum % Key)].insert(source);
    Table[(int)(sum % Key)].HashValue = sum;
}

void Hash::deleteValue(ListNode *reference)
{
    int sum = 0, phoneBuff = reference->getPhone();
    while(phoneBuff != 0)
    {
	sum += phoneBuff % 10;
	phoneBuff /= 10;
    }

    Table[(int)(sum % Key)].deleteValue(reference);
}
