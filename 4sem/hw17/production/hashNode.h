#ifndef HASHNODE_H
#define HASHNODE_H

#include "AVLTree.h"

class Hash;

class HashNode: public AVLTree
{
    private:
	int HashValue = 0;

    public:
	HashNode() = default;
	~HashNode() = default;

	friend class Hash;
};

#endif // HASHNODE_H
