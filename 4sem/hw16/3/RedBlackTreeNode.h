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
	    if(NameSearch != nullptr && PhoneSearch != nullptr)
	    {
		NameSearch->print(NameSearch->getRoot());
		PhoneSearch->print();
	    }
	    //printf("%d\n", NameSearch->Root->Data->getGroup());
	}

	int operator> (const ListNode &x)
	{
	    return NameSearch->getRoot()->Data->getGroup() > x.getGroup();
	}

	int operator< (const ListNode &x)
	{
	    return NameSearch->getRoot()->Data->getGroup() < x.getGroup();
	}

	int operator== (const ListNode &x)
	{
	    return NameSearch->getRoot()->Data->getGroup() == x.getGroup();
	}
};

#endif // RedBlackTreeNODE_H


