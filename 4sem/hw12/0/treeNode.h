#ifndef TREE_NODE_H
#define TREE_NODE_H 

#include "queue.h"

template <class T, template <class> class T1>
class Tree;

template <class T, template <class> class T1>
class TreeNode: public T1 <T>
{
	private:
		TreeNode *Child = nullptr;
		TreeNode *Brother = nullptr;
	public:
		TreeNode() = default;
		~TreeNode() = default;

		//
		bool is_set_child(TreeNode *input)
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

		bool is_set_brother(TreeNode *input)
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

		//
		TreeNode* get_child() const
		{
		        return Child;
		}
		TreeNode* get_brother() const
		{
		        return Brother;
		}

		friend class Tree<T, T1>;
};

#endif
