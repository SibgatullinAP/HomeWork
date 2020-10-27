#ifndef TREE_NODE_H
#define TREE_NODE_H 

#include "student.h"

class TreeNode;
class Tree;

class TreeNode: public Student
{
	private:
		TreeNode *LeftChild = nullptr;
		TreeNode *RightChild = nullptr;
	public:
		TreeNode() = default;
		~TreeNode() = default;

		bool is_set_left(TreeNode *input);
		bool is_set_right(TreeNode *input);

		TreeNode* get_left() const;
		TreeNode* get_right() const;

		friend class Tree;
};

#endif