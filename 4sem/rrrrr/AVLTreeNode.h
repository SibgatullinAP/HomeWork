#ifndef AVLTreeNODE_H
#define AVLTreeNODE_H

#include "record.h"
#include "listNode.h"

class AVLTree;

class AVLTreeNode
{
    AVLTreeNode * LeftChild = nullptr;
    AVLTreeNode * RightChild = nullptr;
    ListNode * Data = nullptr;
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

    int operator> (const ListNode &x)
    {
	if(Data->getPhone() == x.getPhone())
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		return Data->getGroup() > x.getGroup();
	    }
	    else
	    {
		return (flag > 0 ? 1 : 0);
	    }
	}
	else
	{
	    return Data->getPhone() > x.getPhone();
	}
    }

    int operator< (const ListNode &x)
    {
	if(Data->getPhone() == x.getPhone())
	{
	    int flag = strcmp(Data->getName(),x.getName());
	    if(flag == 0)
	    {
		return (Data->getGroup() < x.getGroup());
	    }
	    else
	    {
		return (flag < 0 ? 1 : 0);
	    }
	}
	else
	{
	    return Data->getPhone() < x.getPhone();
	}
    }

    int operator== (const ListNode &x)
    {
	return Data->getGroup() == x.getGroup();
    }


};

#endif // AVLTreeNODE_H


