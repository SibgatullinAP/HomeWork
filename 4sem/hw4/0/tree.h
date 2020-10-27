#ifndef TREE_H
#define TREE_H 

#include "treeNode.h"
#include "student.h"

class Tree
{
	private:
		TreeNode *Root = nullptr;
		TreeNode *Current = nullptr;

	public:
		Tree() = default;
		~Tree()
		{
			delete_tree(Root);
		}

		void delete_tree(TreeNode *root); // ÑÐ´ÐµÐ»Ð°Ð½Ð¾
		int read(FILE *fp); // ÑÐ´ÐµÐ»Ð°Ð½Ð¾
		void print(TreeNode *Root, int level = 0, int max_print = 0);

		TreeNode* add(TreeNode *tmp, TreeNode *Root); // ÑÐ´ÐµÐ»Ð°Ð½Ð¾

		TreeNode* get_root() const; // ÑÐ´ÐµÐ»Ð°Ð½Ð¾

		TreeNode* set_left(); 
		TreeNode* set_right();  
		TreeNode* set_root(); 

		TreeNode* del_left(); 
		TreeNode* del_right(); 
		TreeNode* del_root(); 

		TreeNode* del_sub_left(); // done 
		TreeNode* del_sub_right(); // done 

        int func1(TreeNode* root); // quantity of list
        int func2(TreeNode* root); // max depth
        int func5(TreeNode* root); // quantity of 1 children parent

};

#endif