#ifndef TREE_NODE_H
#define TREE_NODE_H 

#include "queue.h"

class TreeNode;
class Tree;
class TreeNode: public Queue
{
	private:
		TreeNode *Child = nullptr;
		TreeNode *Brother = nullptr;
	public:
		TreeNode()
		{
		    Child = nullptr;
		    Brother = nullptr;
		}
		~TreeNode() = default;

		bool is_set_child(TreeNode *input);
		bool is_set_brother(TreeNode *input);

		TreeNode* get_child() const;
		TreeNode* get_brother() const;

		friend class Tree;
};

#endif
