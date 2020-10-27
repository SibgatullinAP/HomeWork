#ifndef RedBlackTreeNameNODE_H
#define RedBlackTreeNameNODE_H

#include "record.h"

class RedBlackTreeName;

class RedBlackTreeNameNode
{
    private:
        RedBlackTreeNameNode * LeftChild = nullptr;
	RedBlackTreeNameNode * RightChild = nullptr;
	RedBlackTreeNameNode * Parent = nullptr;
	Record * Data = nullptr;
	color Color = RED;

    public:
	friend class RedBlackTreeName;
	RedBlackTreeNameNode() = default;
	~RedBlackTreeNameNode() = default;

	int operator> (const RedBlackTreeNameNode &x)
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

	int operator< (const RedBlackTreeNameNode &x)
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

	int operator== (const RedBlackTreeNameNode &x)
	{
	    return Data->getGroup() == x.Data->getGroup()
	           && Data->getPhone() == x.Data->getPhone()
	           && !strcmp(Data->getName(),x.Data->getName()) ;
	}


};

#endif // RedBlackTreeNameNODE_H


