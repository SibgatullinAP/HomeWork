#ifndef RedBlackTreeNODE_H
#define RedBlackTreeNODE_H

#include "record.h"
#include "hash.h"
#include "RedBlackTreeName.h"

class RedBlackTree;

class RedBlackTreeNode
{
    private:
        RedBlackTreeNode * LeftChild = nullptr;
	RedBlackTreeNode * RightChild = nullptr;
	RedBlackTreeNode * Parent = nullptr;
	Hash * PhoneSearch = nullptr;
	RedBlackTreeName * NameSearch = nullptr;
	int Group = 0;
	color Color = RED;

    public:
	friend class RedBlackTree;
	RedBlackTreeNode(int HashSize)
	{
	    NameSearch = new RedBlackTreeName;
	    PhoneSearch = new Hash(HashSize);
	}
	RedBlackTreeNode() = default;

	~RedBlackTreeNode()
	{
	    delete NameSearch;
	    delete PhoneSearch;
	}


	void print()
	{
	    if(NameSearch->Root != NameSearch->NILL && PhoneSearch != nullptr)
	    {
		printf("%d\n", Group);
		NameSearch->print(NameSearch->getRoot());
		printf("-----------------\n");
		PhoneSearch->print();
	    }
	}

	int operator> (const ListNode &x)
	{
	    return Group > x.getGroup();
	}

	int operator< (const ListNode &x)
	{
	    return Group < x.getGroup();
	}

	int operator== (const ListNode &x)
	{
	    return Group == x.getGroup();
	}


	int operator> (const RedBlackTreeNode &x)
	{
	    return Group > x.Group;
	}

	int operator< (const RedBlackTreeNode &x)
	{
	    return Group < x.Group;
	}

	int operator== (const RedBlackTreeNode &x)
	{
	    return Group == x.Group;
	}
};

#endif // RedBlackTreeNODE_H


