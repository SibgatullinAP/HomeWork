#ifndef TREE_H
#define TREE_H

#include "treeNode.h"

class Tree
{
    TreeNode * Root = nullptr;

    public:
        Tree() = default;
	~Tree();

	TreeNode *getRoot();

	void inorder();
	void levelOrder();
	void deleteTree(TreeNode *tmp);
	void print(TreeNode *root, int level = 0, int maxPrint = 0);
	int read(FILE *inFile);

	void rotateLeft(TreeNode *& root, TreeNode *& tmp);
	void rotateRight(TreeNode *& root, TreeNode *& tmp);

	void insert(char *Name, int Phone, int Group);
	TreeNode * binaryInsertion(TreeNode *root, TreeNode *source);
	void balanceInsert(TreeNode *&root, TreeNode *& tmp);

	void deleteValue(char *Name, int Phone, int Group);
	TreeNode* binaryDeletion(TreeNode *root, Record *reference);
	void balanceDelete(TreeNode *tmp);
	TreeNode *minValue(TreeNode *root);
	TreeNode *maxValue(TreeNode *root);
};

#endif // TREE_H
