#ifndef RedBlackTreeNODE_H
#define RedBlackTreeNODE_H

#include "record.h"

class RedBlackTree;

class RedBlackTreeNode
{
    private:
        RedBlackTreeNode * LeftChild = nullptr;
	RedBlackTreeNode * RightChild = nullptr;
	RedBlackTreeNode * Parent = nullptr;
	Record * Data = nullptr;
	color Color = RED;

    public:
	friend class RedBlackTree;
	RedBlackTreeNode() = default;
	~RedBlackTreeNode() = default;

	int operator> (const RedBlackTreeNode &x)
	{
	    int flag = strcmp(Data->getName(),x.Data->getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.Data->getPhone())
		{
		    return Data->getGroup() > x.Data->getGroup();
		}
		else
		{
		    return Data->getPhone() > x.Data->getPhone();
		}
	    }
	    else
	    {
		return (flag > 0 ? 1 : 0);
	    }
	}

	int operator< (const RedBlackTreeNode &x)
	{
	    int flag = strcmp(Data->getName(),x.Data->getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.Data->getPhone())
		{
		    return Data->getGroup() < x.Data->getGroup();
		}
		else
		{
		    return Data->getPhone() < x.Data->getPhone();
		}
	    }
	    else
	    {
		return (flag < 0 ? 1 : 0);
	    }
	}

	int operator== (const RedBlackTreeNode &x)
	{
	    return Data->getGroup() == x.Data->getGroup();
	}


};

#endif // RedBlackTreeNODE_H


