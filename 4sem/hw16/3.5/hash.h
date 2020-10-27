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
	int function(Record *x);
	void insert(ListNode * source);
	void deleteValue(ListNode * reference);
	AVLTreeNode * searchByPhone(int Phone);
};
#endif // HASH_H
