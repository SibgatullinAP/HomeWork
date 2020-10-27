#ifndef AVLTreeNODE_H
#define AVLTreeNODE_H

#include "record.h"

class AVLTree;

class AVLTreeNode
{
    AVLTreeNode * LeftChild = nullptr;
    AVLTreeNode * RightChild = nullptr;
    Record * Data = nullptr;
    int Height = 1;

public:

    friend class AVLTree;

    AVLTreeNode() = default;
    ~AVLTreeNode() = default;

    friend int getHeight(AVLTreeNode *tmp)
    {
	if(tmp != nullptr)
	{
	    return tmp->Height;
	}
	return 0;
    }

    friend int getBalance(AVLTreeNode *tmp)
    {
	return getHeight(tmp->RightChild) - getHeight(tmp->LeftChild);
    }

    friend void fixHeight(AVLTreeNode *tmp)
    {
	if(tmp != nullptr)
	{
	    int heightLeft = getHeight(tmp->LeftChild);
	    int heightRight = getHeight(tmp->RightChild);

	    tmp->Height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}
	return;
    }

    int operator> (const AVLTreeNode &x)
    {
	if(Data->getPhone() == x.Data->getPhone())
	{
	    int flag = strcmp(Data->getName(),x.Data->getName());
	    if(flag == 0)
	    {
		return Data->getGroup() > x.Data->getGroup();
	    }
	    else
	    {
		return (flag > 0 ? 1 : 0);
	    }
	}
	else
	{
	    return Data->getPhone() > x.Data->getPhone();
	}
    }

    int operator< (const AVLTreeNode &x)
    {
	if(Data->getPhone() == x.Data->getPhone())
	{
	    int flag = strcmp(Data->getName(),x.Data->getName());
	    if(flag == 0)
	    {
		return (Data->getGroup() < x.Data->getGroup());
	    }
	    else
	    {
		return (flag < 0 ? 1 : 0);
	    }
	}
	else
	{
	    return Data->getPhone() < x.Data->getPhone();
	}
    }

    int operator== (const AVLTreeNode &x)
    {
	return Data->getGroup() == x.Data->getGroup();
    }


};

#endif // AVLTreeNODE_H


