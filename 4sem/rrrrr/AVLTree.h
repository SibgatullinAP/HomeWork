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

	ListNode * search(Command & command, int flagType, int flag, ListNode *&begin);
	void traverse(Command &command, AVLTreeNode *tmp, ListNode *&begin, int flagType);

	void print(AVLTreeNode *root, int level = 0, int maxPrint = 0);
	void deleteAVLTree(AVLTreeNode *tmp);

	AVLTreeNode * rotateLeft(AVLTreeNode * center);
	AVLTreeNode * rotateRight(AVLTreeNode * center);
	AVLTreeNode * minValue(AVLTreeNode *root);
	AVLTreeNode * maxValue(AVLTreeNode *root);
	AVLTreeNode * balance(AVLTreeNode * tmp);

	void insert(ListNode * data);
	AVLTreeNode * binaryInsertion(AVLTreeNode *root, AVLTreeNode *source);

	void deleteValue(ListNode *tmp);
	AVLTreeNode * deleteMinValue(AVLTreeNode *min);
	AVLTreeNode * binaryDeletion(AVLTreeNode *root, ListNode *reference);
};

#endif // AVLTree_H
