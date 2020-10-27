#ifndef TREE_NODE_H
#define TREE_NODE_H 

#include "student.h"

class TreeNode;
class Tree;

class TreeNode: public Student
{
	private:
		TreeNode *Child = nullptr;
		TreeNode *Brother = nullptr;
	public:
		TreeNode() = default;
		~TreeNode() = default;

		bool is_set_child(TreeNode *input);
		bool is_set_brother(TreeNode *input);

		TreeNode* get_child() const;
		TreeNode* get_brother() const;

		friend class Tree;
};

#endif