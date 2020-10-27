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


                int func1(TreeNode* root); // quantity of list

                int func2(TreeNode* root); // max depth

                int func3(TreeNode* root); // max width of tree
                int subfunc3(TreeNode* root, int level); // finding width of tree's level

                int func4(TreeNode* root, int *answer);

                int func5(TreeNode* root); // quantity of 1 children parent




                int func11(TreeNode* root, int k); // quantity of subtree with #node <= k
                int subfunc11(TreeNode* root, int k, int &answer); // quantity of nodes

                int func22(TreeNode* root, int k); // same as 1st
                int subfunc22(TreeNode* root, int k, int &answer);

                int func33(TreeNode* root, int k);
                int depth(TreeNode* root);
                int subfunc33(TreeNode* root, int k, int &answer); // quantity of subtrees with depth <= k

                int func55(TreeNode* root, int level); // finding width of tree's level



};

#endif
