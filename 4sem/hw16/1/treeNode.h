#ifndef TREENODE_H
#define TREENODE_H

#include "record.h"

class Tree;

class TreeNode: public Record
{
    TreeNode * LeftChild = nullptr;
    TreeNode * RightChild = nullptr;
    int Height = 1;

public:

    friend class Tree;

    TreeNode() = default;
    ~TreeNode() = default;

    friend int getHeight(TreeNode *tmp)
    {
	if(tmp != nullptr)
	{
	    return tmp->Height;
	}
	return 0;
    }

    friend int getBalance(TreeNode *tmp)
    {
	return getHeight(tmp->RightChild) - getHeight(tmp->LeftChild);
    }

    friend void fixHeight(TreeNode *tmp)
    {
	if(tmp != nullptr)
	{
	    int heightLeft = getHeight(tmp->LeftChild);
	    int heightRight = getHeight(tmp->RightChild);

	    tmp->Height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}
	return;
    }
};

#endif // TREENODE_H


