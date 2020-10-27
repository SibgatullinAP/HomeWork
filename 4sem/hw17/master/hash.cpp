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

void Hash::deleteHash()
{
    for(int i = 0; i < Key; i++)
    {
	Table[i].deleteAVLTree(Table[i].getRoot());
    }
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
    Table[hashFunc(*source)].insert(source);
}

void Hash::deleteValue(ListNode *reference)
{
    Table[hashFunc(*reference)].deleteValue(reference);
}

ListNode * Hash::search(Command & current, int flagType, int flag, ListNode *&begin)
{
    if(Table[hashFunc(current)].getRoot() != nullptr)
    {
	return Table[hashFunc(current)].search(current, flagType, flag, begin);
    }
    return nullptr;
}

#ifdef ZACHET

    int Hash::hashFunc(Record &tmp)
    {
	return (tmp.getPhone() % Key);
    }

#else
    int Hash::hashFunc(Record &tmp)
    {
	int sum = 0, phoneBuff = tmp.getPhone();
	while(phoneBuff != 0)
	{
	    sum += phoneBuff % 10;
	    phoneBuff /= 10;
	}

	return (sum % Key);
    }
#endif
