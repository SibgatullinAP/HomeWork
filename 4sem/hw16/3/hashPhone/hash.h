#ifndef HASH_H
#define HASH_H

#include "hashNode.h"

class Hash
{
    private:
        HashNode * Table = nullptr;
	int Key = 0;

    public:
	Hash() = default;
	Hash(int key);
	~Hash();

	int read(FILE *inFile);
	void print();
	void insert(char *Name, int Phone, int Group);
	void deleteValue(char *Name, int Phone, int Group);
	AVLTreeNode * searchByPhone(int Phone);
};

#endif // HASH_H
