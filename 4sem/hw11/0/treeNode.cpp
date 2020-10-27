#include "treeNode.h"

bool TreeNode::is_set_child(TreeNode *input)
{
	if(this -> Child)
	{
		return false;
	}
	else
	{
		this -> Child = input;
		return true;
	}
}

bool TreeNode::is_set_brother(TreeNode *input)
{
	if(this -> Brother)
	{
		return false;
	}
	else
	{
		this -> Brother = input;
		return true;
	}
}

TreeNode* TreeNode::get_child() const
{
	return Child;
}

TreeNode* TreeNode::get_brother() const
{
	return Brother;
}
