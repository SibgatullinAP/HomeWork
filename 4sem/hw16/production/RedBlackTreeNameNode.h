#ifndef RedBlackTreeNameNODE_H
#define RedBlackTreeNameNODE_H

#include "record.h"
#include "listNode.h"

class RedBlackTreeName;
class RedBlackTree;

class RedBlackTreeNameNode
{
    private:
        RedBlackTreeNameNode * LeftChild = nullptr;
	RedBlackTreeNameNode * RightChild = nullptr;
	RedBlackTreeNameNode * Parent = nullptr;
	ListNode * Data = nullptr;
	color Color = RED;

    public:

	friend class RedBlackTreeNode;
	friend class RedBlackTreeName;
	friend class RedBlackTree;

	RedBlackTreeNameNode() = default;
	~RedBlackTreeNameNode() = default;

	int operator> (const ListNode &x)
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.getPhone())
		{
		    return Data->getGroup() > x.getGroup();
		}
		else
		{
		    return Data->getPhone() > x.getPhone();
		}
	    }
	    else
	    {
		return (flag > 0 ? 1 : 0);
	    }
	}

	int operator< (const ListNode &x)
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.getPhone())
		{
		    return Data->getGroup() < x.getGroup();
		}
		else
		{
		    return Data->getPhone() < x.getPhone();
		}
	    }
	    else
	    {
		return (flag < 0 ? 1 : 0);
	    }
	}

	int operator== (const ListNode &x)
	{
	    return Data->getGroup() == x.getGroup()
	           && Data->getPhone() == x.getPhone()
	           && !strcmp(Data->getName(),x.getName()) ;
	}


	int operator> (const Record &x)
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.getPhone())
		{
		    return Data->getGroup() > x.getGroup();
		}
		else
		{
		    return Data->getPhone() > x.getPhone();
		}
	    }
	    else
	    {
		return (flag > 0 ? 1 : 0);
	    }
	}

	int operator< (const Record &x)
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		if(Data->getPhone() == x.getPhone())
		{
		    return Data->getGroup() < x.getGroup();
		}
		else
		{
		    return Data->getPhone() < x.getPhone();
		}
	    }
	    else
	    {
		return (flag < 0 ? 1 : 0);
	    }
	}

	int operator== (const Record &x)
	{
	    return Data->getGroup() == x.getGroup()
		   && Data->getPhone() == x.getPhone()
		   && !strcmp(Data->getName(),x.getName()) ;
	}
};

#endif // RedBlackTreeNameNODE_H


