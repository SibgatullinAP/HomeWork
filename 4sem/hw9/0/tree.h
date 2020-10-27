#ifndef TREE_H
#define TREE_H 

#include "treeNode.h"
#include "student.h"
#include "addons.h"
#include <math.h>

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
		void print(TreeNode *Root, int max_print);

		void add(TreeNode *tmp, TreeNode *Root); // ÑÐ´ÐµÐ»Ð°Ð½Ð¾

		TreeNode* get_root() const; // ÑÐ´ÐµÐ»Ð°Ð½Ð¾

		TreeNode* set_left(); 
		TreeNode* set_right();  
		TreeNode* set_root(); 

		TreeNode* del_left(); 
		TreeNode* del_right(); 
		TreeNode* del_root(); 

		TreeNode* del_sub_level(); // done 
		TreeNode* del_sub_tree(); // done 

       	int func1(int k);
       	int solve1(int k, int *count);

       	int func2(int k);
       	int solve2(int k, int &count);

       	int func3(int k);
       	int func4(int k);

       	int func5(int k);
       	int solve5(int k);

        int func6(int k); 

};

#endif