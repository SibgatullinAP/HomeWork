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

                int func1(TreeNode* root, int k); // quantity of subtree with #node <= k
                int subfunc1(TreeNode* root, int k, int &answer); // quantity of nodes

                int func2(TreeNode* root, int k); // same as 1st
                int subfunc2(TreeNode* root, int k, int &answer);

                int func3(TreeNode* root, int k);
                int depth(TreeNode* root);
                int subfunc3(TreeNode* root, int k, int &answer); // quantity of subtrees with depth <= k

                int func4(TreeNode* root); //undone
                int subfunc4(TreeNode* root, int *answer); // undone

                int func5(TreeNode* root, int level); // finding width of tree's level



};

#endif
