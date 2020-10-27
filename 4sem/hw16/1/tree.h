#ifndef TREE_H
#define TREE_H

#include "treeNode.h"

class Tree
{
    TreeNode * Root = nullptr;

    public:
        Tree() = default;
	~Tree() {deleteTree(Root);}

	TreeNode *getRoot() {return Root;}

	int read(FILE *inFile);
	void print(TreeNode *root, int level = 0, int maxPrint = 0);
	void deleteTree(TreeNode *tmp);

	TreeNode * rotateLeft(TreeNode * center);
	TreeNode * rotateRight(TreeNode * center);
	TreeNode * minValue(TreeNode *root);
	TreeNode * maxValue(TreeNode *root);
	TreeNode * balance(TreeNode * tmp);

	void insert(char *Name, int Phone, int Group);
	TreeNode * binaryInsertion(TreeNode *root, TreeNode *source);

	void deleteValue(char *Name, int Phone, int Group);
	TreeNode * deleteMinValue(TreeNode *min);
	TreeNode * binaryDeletion(TreeNode *root, Record *reference);
};

#endif // TREE_H
