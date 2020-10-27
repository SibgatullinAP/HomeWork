#ifndef HASH_H
#define HASH_H

#include "hashNode.h"
#include "command.h"

class Hash
{
    private:
        HashNode * Table = nullptr;
	int Key = 0;

    public:
	Hash() = default;
	Hash(int key);
	~Hash();

	void print();
	int hashFunc(Record &tmp);
	void deleteHash();
	void insert(ListNode * source);
	void deleteValue(ListNode * reference);
	ListNode * search(Command & current, int flagType, int flag, ListNode *&begin);
};

#endif // HASH_H
