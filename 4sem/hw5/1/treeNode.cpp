#include "treeNode.h"

bool TreeNode::is_set_left(TreeNode *input)
{
	if(this -> LeftChild)
	{
		return false;
	}
	else
	{
		this -> LeftChild = input;
		return true;
	}
}

bool TreeNode::is_set_right(TreeNode *input)
{
	if(this -> RightChild)
	{
		return false;
	}
	else
	{
		this -> RightChild = input;
		return true;
	}
}

TreeNode* TreeNode::get_left() const
{
	return LeftChild;
}

TreeNode* TreeNode::get_right() const
{
	return RightChild;
}
