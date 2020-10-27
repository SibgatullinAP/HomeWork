#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "RedBlackTreeNode.h"

class RedBlackTree
{
    private:
        RedBlackTreeNode * Root = nullptr;
	RedBlackTreeNode * NILL = new RedBlackTreeNode;

    public:
        RedBlackTree();
	~RedBlackTree();

	RedBlackTreeNode *getRoot();

	int read(FILE *inFile);
	void print(RedBlackTreeNode *root, int level = 0, int maxPrint = 0);
	void deleteRedBlackTree(RedBlackTreeNode *tmp);

	void rotateLeft(RedBlackTreeNode *& root, RedBlackTreeNode *& tmp);
	void rotateRight(RedBlackTreeNode *& root, RedBlackTreeNode *& tmp);
	RedBlackTreeNode * minValue(RedBlackTreeNode *root);
	RedBlackTreeNode * search(RedBlackTreeNode * reference);

	void insert(char *Name, int Phone, int Group);
	RedBlackTreeNode * binaryInsertion(RedBlackTreeNode *root, RedBlackTreeNode *source);
	void balanceInsert(RedBlackTreeNode *&root, RedBlackTreeNode *& tmp);

	void deleteValue(char *Name, int Phone, int Group);
	RedBlackTreeNode * binaryDeletion(RedBlackTreeNode *root, RedBlackTreeNode*reference);
	RedBlackTreeNode * child(RedBlackTreeNode *tmp);
	void balanceDelete(RedBlackTreeNode *tmp);
};

#endif // RedBlackTree_H
