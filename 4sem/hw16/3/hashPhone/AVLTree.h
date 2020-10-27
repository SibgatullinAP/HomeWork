#ifndef AVLTree_H
#define AVLTree_H

#include "AVLTreeNode.h"

class AVLTree
{
    AVLTreeNode * Root = nullptr;

    public:
        AVLTree() = default;
	~AVLTree() {deleteAVLTree(Root);}

	AVLTreeNode *getRoot() {return Root;}

	int read(FILE *inFile);
	void print(AVLTreeNode *root, int level = 0, int maxPrint = 0);
	void deleteAVLTree(AVLTreeNode *tmp);

	AVLTreeNode * rotateLeft(AVLTreeNode * center);
	AVLTreeNode * rotateRight(AVLTreeNode * center);
	AVLTreeNode * minValue(AVLTreeNode *root);
	AVLTreeNode * maxValue(AVLTreeNode *root);
	AVLTreeNode * balance(AVLTreeNode * tmp);

	void insert(char *Name, int Phone, int Group);
	AVLTreeNode * binaryInsertion(AVLTreeNode *root, AVLTreeNode *source);

	void deleteValue(char *Name, int Phone, int Group);
	AVLTreeNode * deleteMinValue(AVLTreeNode *min);
	AVLTreeNode * binaryDeletion(AVLTreeNode *root, AVLTreeNode *reference);
};

#endif // AVLTree_H
