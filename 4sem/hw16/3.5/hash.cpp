#include "hash.h"

int Hash::function(Record *source)
{
    int sum = 0, phoneBuff = source->getPhone();
    while(phoneBuff != 0)
    {
	sum += phoneBuff % 10;
	phoneBuff /= 10;
    }
    return (int)(sum % Key);
}

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
    Table[function(source)].insert(source);
}

void Hash::deleteValue(ListNode *reference)
{
    Table[function(reference)].deleteValue(reference);
}
