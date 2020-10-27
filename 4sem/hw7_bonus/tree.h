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

                void delete_tree(TreeNode *root); //common destroyer
                int read(FILE *fp);
                void print(TreeNode *Root, int level = 0, int max_print = 0);

                TreeNode* add(TreeNode *tmp, TreeNode *Root); // common adding

                TreeNode* add_left(TreeNode *tmp, TreeNode *root); //done
                TreeNode* add_right(TreeNode *tmp, TreeNode *root); //done
                TreeNode* get_root() const; // done

                TreeNode* go_left(TreeNode* root); //done
                TreeNode* go_right(TreeNode* root);  //done
                TreeNode* go_root(TreeNode* root); //done

                TreeNode* del_left(); // done
                TreeNode* del_right(); // done
                TreeNode* del_root(); // done

		TreeNode* del_sub_left(); // done 
		TreeNode* del_sub_right(); // done 

                //HeapSort
                void heapSort();
};

#endif
